#include <ObjFile.h>
#include <Point.h>
#include <Vector.h>
#include <Group.h>
#include <Triangle.h>

#include <vector>
#include <iostream>
#include <cstdio>
#include <cassert>

namespace {
  static std::string line;
  static int         line_num { 0 };

  bool readLine(FILE *fp, std::string &line) {
    line = "";

    if (feof(fp))
      return false;

    int c;

    while ((c = fgetc(fp)) != EOF) {
      if (c == '\n')
        break;

      line += char(c);
    }

    return true;
  }

  std::string stripSpaces(const std::string &str) {
    int len = str.size();

    int i1 = 0;
    int i2 = len - 1;

    while (i1 < len && isspace(str[i1]))
      ++i1;

    while (i2 >= 0 && isspace(str[i2]))
      --i2;

    if (i1 == 0 && i2 == len - 1)
      return str;

    return str.substr(i1, i2 - i1 + 1);
  }

  void addWords(const std::string &str, std::vector<std::string> &words) {
    int i   = 0;
    int len = str.size();

    while (i < len) {
      while (i < len && isspace(str[i]))
        ++i;

      int j = i;

      while (i < len && ! isspace(str[i]))
        ++i;

      if (i > j) {
        std::string word = str.substr(j, i - j);

        words.push_back(word);
      }
    }
  }

  void addFields(const std::string &str, std::vector<std::string> &words, char sep) {
    int i   = 0;
    int len = str.size();

    while (i < len) {
      int j = i;

      while (i < len && str[i] != sep)
        ++i;

      std::string word = str.substr(j, i - j);

      words.push_back(word);

      if (str[i] == sep)
        ++i;
    }
  }

  bool isReal(const std::string &str) {
    int len = str.size();
    if (len == 0) return false;

    int i = 0;

    if (i < len && (str[i] == '-' || str[i] == '+'))
      ++i;

    if (i < len && str[i] == '.')
      ++i;

    if (i < len && isdigit(str[i]))
      return true;

    return false;
  }

  double toReal(const std::string &str) {
    return std::stod(str);
  }

  bool isInteger(const std::string &str) {
    int len = str.size();
    if (len == 0) return false;

    if (isdigit(str[0]))
      return true;

    return false;
  }

  int toInteger(const std::string &str) {
    return std::stoi(str);
  }
}

//---

namespace RayTrace {

bool
ObjFile::
read()
{
  numErrors_ = 0;

  //---

  FILE *fp = fopen(filename_.c_str(), "r");
  if (! fp) return false;

  //---

  vnum_  = 0;
  vnnum_ = 0;

  while (readLine(fp, line)) {
    ++line_num;

    std::string line1 = stripSpaces(line);

    int len = line1.size();

    if (len <= 0 || line1[0] == '#')
      continue;

    // vertex coord
    if      (len > 2 && line1[0] == 'v' && line1[1] == ' ') {
      line1 = stripSpaces(line1.substr(2));

      if (! readVertex(line1))
        error("Invalid vertex line");

      ++vnum_;
    }
    // vertex texture coord
    else if (len > 2 && line1[0] == 'v' && line1[1] == 't') {
      line1 = stripSpaces(line1.substr(2));

      if (! readTextureVertex(line1))
        error("Invalid texture vertex line");

      ++vtnum_;
    }
    // vertex normal
    else if (len > 2 && line1[0] == 'v' && line1[1] == 'n') {
      line1 = stripSpaces(line1.substr(2));

      if (! readVertexNormal(line1))
        error("Invalid vertex normal line");

      ++vnnum_;
    }
    // parameter space vertex
    else if (len > 2 && line1[0] == 'v' && line1[1] == 'p') {
      line1 = stripSpaces(line1.substr(2));

      if (! readParameterVertex(line1))
        error("Invalid parameter vertex line");
    }
    // group
    else if (len > 2 && line1[0] == 'g' && line1[1] == ' ') {
      line1 = stripSpaces(line1.substr(2));

      if (! readGroupName(line1))
        error("Invalid group name line");
    }
    // group (unnamed)
    else if (len == 1 && line1[0] == 'g') {
      if (! readGroupName(""))
        error("Invalid group name line");
    }
    // face
    else if (len > 2 && line1[0] == 'f' && line1[1] == ' ') {
      line1 = stripSpaces(line1.substr(2));

      if (! readFace(line1))
        error("Invalid face line");
    }
    // object name
    else if (len > 2 && line1[0] == 'o' && line1[1] == ' ') {
      // skip object name
    }
    // smoothing group
    else if (len > 2 && line1[0] == 's' && line1[1] == ' ') {
      // skip smoothing group
    }
    // material library
    else if (len > 6 && line1.substr(0, 6) == "mtllib") {
      // todo
    }
    // use material
    else if (len > 6 && line1.substr(0, 6) == "usemtl" && line1[6] == ' ') {
      // todo
      line1 = stripSpaces(line1.substr(7));

      if (! readMaterial(line1))
        error("Invalid material line");
    }
    else {
      error("Unrecognised line");
    }
  }

  fclose(fp);

  return true;
}

bool
ObjFile::
readVertex(const std::string &line)
{
  std::vector<std::string> words;

  addWords(line, words);

  if (words.size() < 3)
    return false;

  if (! isReal(words[0]) || ! isReal(words[1]) || ! isReal(words[2]))
    return false;

  double x = toReal(words[0]);
  double y = toReal(words[1]);
  double z = toReal(words[2]);

  Point p(x, y, z);

  points_.push_back(p);

  return true;
}

bool
ObjFile::
readTextureVertex(const std::string &line)
{
  std::vector<std::string> words;

  addWords(line, words);

  if      (words.size() == 2) {
    if (! isReal(words[0]) || ! isReal(words[1]))
      return false;

    double u = toReal(words[0]);
    double v = toReal(words[1]);

    Point p(u, v, 0.0);

    texturePoints_.push_back(p);
  }
  else if (words.size() == 3) {
    if (! isReal(words[0]) || ! isReal(words[1]) || ! isReal(words[2]))
      return false;

    double u = toReal(words[0]);
    double v = toReal(words[1]);
    double w = toReal(words[2]);

    Point p(u, v, w);

    texturePoints_.push_back(p);
  }
  else {
    return false;
  }

  return true;
}

bool
ObjFile::
readVertexNormal(const std::string &line)
{
  std::vector<std::string> words;

  addWords(line, words);

  if (words.size() != 3)
    return false;

  if (! isReal(words[0]) || ! isReal(words[1]) || ! isReal(words[2]))
    return false;

  double x = toReal(words[0]);
  double y = toReal(words[1]);
  double z = toReal(words[2]);

  Vector normal(x, y, z);

  normals_.push_back(normal);

  return true;
}

bool
ObjFile::
readParameterVertex(const std::string &)
{
  return true;
}

bool
ObjFile::
readGroupName(const std::string &line)
{
  groupName_ = line;
  material_  = "";

  return true;
}

bool
ObjFile::
readMaterial(const std::string &line)
{
  material_ = line;

  return true;
}

bool
ObjFile::
readFace(const std::string &line)
{
  using Inds = std::vector<int>;

  Inds vertices;
  Inds texturePoints;
  Inds normals;

  std::vector<std::string> words;

  addWords(line, words);

  int num_words = words.size();

  for (int i = 0; i < num_words; i++) {
    std::vector<std::string> fields;

    // vertex ind, texture vertex ind (can be empty), normal vertex ind
    addFields(words[i], fields, '/');

    while (fields.size() < 3)
      fields.push_back("");

    int num1 = -1;
    int num2 = -1;
    int num3 = -1;

    if (isInteger(fields[0]))
      num1 = toInteger(fields[0]);

    if (isInteger(fields[1]))
      num2 = toInteger(fields[1]);

    if (isInteger(fields[2]))
      num3 = toInteger(fields[2]);

    if (num1 > 0)
      vertices.push_back(num1 - 1);

    if (num2 > 0)
      texturePoints.push_back(num2 - 1);
    else
      texturePoints.push_back(-1);

    if (num3 > 0)
      normals.push_back(num3 - 1);
    else
      normals.push_back(-1);
  }

  ObjGroup &group = this->group(groupName_);

  assert(vertices.size() >= 3);

  if (vertices.size() > 3) {
    int nf = vertices.size() - 2;

    for (int i = 0; i < nf; ++i) {
      Inds vertices1;

      vertices1.push_back(vertices[    0]);
      vertices1.push_back(vertices[i + 1]);
      vertices1.push_back(vertices[i + 2]);

      Face face(this, vertices1);

      Inds texturePoints1;

      texturePoints1.push_back(texturePoints[    0]);
      texturePoints1.push_back(texturePoints[i + 1]);
      texturePoints1.push_back(texturePoints[i + 2]);

      face.setTexturePoints(texturePoints1);

      Inds normals1;

      normals1.push_back(normals[    0]);
      normals1.push_back(normals[i + 1]);
      normals1.push_back(normals[i + 2]);

      face.setNormals(normals1);

      if (material_ != "")
        face.setMaterial(material_);

      group.addFace(face);
    }
  }
  else {
    Face face(this, vertices);

    face.setTexturePoints(texturePoints);

    face.setNormals(normals);

    if (material_ != "")
      face.setMaterial(material_);

    group.addFace(face);
  }

  return true;
}

GroupP
ObjFile::
createGroup() const
{
  GroupP rgroup;

  if (groups_.size() == 1) {
    rgroup = createGroup(groups_.begin()->second);
  }
  else {
    rgroup = std::make_shared<Group>();

    for (const auto &group : groups_) {
      GroupP rgroup1 = createGroup(group.second);

      rgroup->addObject(rgroup1);
    }
  }

  return rgroup;
}

GroupP
ObjFile::
createGroup(const ObjGroup &group) const
{
  GroupP rgroup = std::make_shared<Group>(group.name());

  for (const auto &face : group.faces()) {
    assert(face.vertices().size() == 3);

    const Point &p1 = face.point(0);
    const Point &p2 = face.point(1);
    const Point &p3 = face.point(2);

    TriangleP rtriangle = std::make_shared<Triangle>(p1, p2, p3);

    rtriangle->setTexturePoint1(face.texturePoint(0));
    rtriangle->setTexturePoint2(face.texturePoint(1));
    rtriangle->setTexturePoint3(face.texturePoint(2));

    rtriangle->setNormal1(face.normal(0));
    rtriangle->setNormal2(face.normal(1));
    rtriangle->setNormal3(face.normal(2));

    if (face.material() != "") {
      Material material;

      material.setImageName(face.material());

      rtriangle->setMaterial(material);
    }

    rgroup->addObject(rtriangle);
  }

  return rgroup;
}

void
ObjFile::
error(const std::string &msg)
{
  ++numErrors_;

  if (debug_)
    std::cerr << "Error: " << msg << ": '" << line << "'@" << line_num << std::endl;
}

//---

Point
ObjFile::Face::
point(int i) const
{
  assert(i >= 0 && i < int(vertices_.size()));

  int iv = vertices_[i];

  return file_->point(iv);
}

Point
ObjFile::Face::
texturePoint(int i) const
{
  assert(i >= 0 && i < int(vertices_.size()));

  if (i < int(texturePoints_.size())) {
    int iv = texturePoints_[i];

    if (iv >= 0)
      return file_->texturePoint(iv);
  }

  return Point(0, 0, 0);
}

Vector
ObjFile::Face::
normal(int i) const
{
  assert(i >= 0 && i < int(vertices_.size()));

  if (i < int(normals_.size())) {
    int iv = normals_[i];

    if (iv >= 0)
      return file_->normal(iv);
  }

  return Vector(0, 0, 1);
}

}
