#ifndef ObjFile_H
#define ObjFile_H

#include <Types.h>
#include <Point.h>
#include <Vector.h>
#include <string>
#include <vector>
#include <map>

namespace RayTrace {

class ObjFile {
 public:
  using Points  = std::vector<Point>;
  using Vectors = std::vector<Vector>;
  using Indices = std::vector<int>;

  class Face {
   public:
    Face(ObjFile *file, const Indices &vertices) :
     file_(file), vertices_(vertices) {
    }

    const Indices &vertices() const { return vertices_; }

    const Indices &texturePoints() const { return texturePoints_; }
    void setTexturePoints(const Indices &inds) { texturePoints_ = inds; }

    const Indices &normals() const { return normals_; }
    void setNormals(const Indices &inds) { normals_ = inds; }

    const std::string &material() const { return material_; }
    void setMaterial(const std::string &v) { material_ = v; }

    Point point(int i) const;

    Point texturePoint(int i) const;

    Vector normal(int i) const;

   private:
    ObjFile*    file_ { nullptr };
    Indices     vertices_;
    Indices     texturePoints_;
    Indices     normals_;
    std::string material_;
  };

  using Faces = std::vector<Face>;

  class ObjGroup {
   public:
    ObjGroup(const std::string &name="") :
     name_(name) {
    }

    const std::string &name() const { return name_; }
    void setName(const std::string &v) { name_ = v; }

    const Faces &faces() const { return faces_; }

    void addFace(const Face &face) {
      faces_.push_back(face);
    }

    const Face &face(int i) const {
      assert(i >= 0 && i < int(faces_.size()));

      return faces_[i];
    }

   private:
    std::string name_;
    Faces       faces_;
  };

  using Groups = std::map<std::string,ObjGroup>;

 public:
  ObjFile(const std::string &filename) :
   filename_(filename) {
  }

  void setDebug(bool debug=true) { debug_ = debug; }

  bool read();

  const Points &points() const { return points_; }

  const Point &point(int i) const {
    assert(i >= 0 && i < int(points_.size()));

    return points_[i];
  }

  const Points &texturePoints() const { return texturePoints_; }

  const Point &texturePoint(int i) const {
    assert(i >= 0 && i < int(texturePoints_.size()));

    return texturePoints_[i];
  }

  const Vectors &normals() const { return normals_; }

  const Vector &normal(int i) const {
    assert(i >= 0 && i < int(normals_.size()));

    return normals_[i];
  }

  const Groups &groups() const { return groups_; }

  ObjGroup &group(const std::string &name="") {
    return groups_[name];
  }

  GroupP createGroup() const;
  GroupP createGroup(const ObjGroup &group) const;

  int numErrors() const { return numErrors_; }

 private:
  bool readVertex(const std::string &line);
  bool readTextureVertex(const std::string &line);
  bool readVertexNormal(const std::string &line);
  bool readParameterVertex(const std::string &line);
  bool readGroupName(const std::string &line);
  bool readMaterial(const std::string &line);
  bool readFace(const std::string &line);

  void error(const std::string &msg);

 private:
  std::string filename_;
  Points      points_;
  Points      texturePoints_;
  Vectors     normals_;
  Groups      groups_;
  int         vnum_      { 0 };
  int         vnnum_     { 0 };
  int         vtnum_     { 0 };
  bool        debug_     { false };
  std::string groupName_;
  std::string material_;
  int         numErrors_ { 0 };
};

}

#endif
