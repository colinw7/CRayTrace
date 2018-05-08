#include <std_c++.h>
#include <CFuncs/CFuncs.h>
#include <CStrUtil/CStrUtil.h>
#include <CXML/CXMLLib.h>
#include <CMath/CTransform2D.h>
#include <CRayShape/CRayShapeLib.h>
#include <CRayTracer/CRayTracer.h>
#include <CRayCamera/CRayCamera.h>
#include <CSample/CSample.h>

CRayTracer::
CRayTracer() :
 renderer_(NULL), num_samples_(16)
{
}

CRayTracer::
~CRayTracer()
{
  for_each(shapes_.begin(), shapes_.end(), CDeletePointer());
}

bool
CRayTracer::
addFile(const string &filename)
{
  CXML     xml;
  CXMLTag *tag;

  if (! xml.read(filename, &tag))
    return false;

  if (tag->getName() != "raytracer")
    return false;

  CXMLTag::TokenArray children = tag->getChildren();

  int num_children = tag->getNumChildren();

  for (int i = 0; i < num_children; ++i) {
    const CXMLToken *token = children[i];

    if (! token->isTag())
      continue;

    CXMLTag *tag1 = token->getTag();

    const string &name = tag1->getName();

    int num_options = tag1->getNumOptions();

    const CXMLTag::OptionArray &options = tag1->getOptions();

    if      (name == "sphere") {
      CPoint3D center(0,0,0);
      double   radius(1.0);
      string   color ("white");

      for (int j = 0; j < num_options; ++j) {
        CXMLTagOption *option = options[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "center") {
          parsePoint(opt_value, center);
        }
        else if (opt_name == "radius") {
          if (! CStrUtil::toReal(opt_value, &radius))
            cerr << "Illegal real value for '" << opt_name << "'" << endl;
        }
        else if (opt_name == "color") {
          color = opt_value;
        }
        else
          cerr << "Unrecognised sphere option '" << opt_name << "'" << endl;
      }

      addSphere(center, radius, color);
    }
    else if (name == "triangle") {
      CPoint3D point1(0,0,0);
      CPoint3D point2(1,0,0);
      CPoint3D point3(0,1,0);
      string   color ("white");

      for (int j = 0; j < num_options; ++j) {
        CXMLTagOption *option = options[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "point1") {
          parsePoint(opt_value, point1);
        }
        else if (opt_name == "point2") {
          parsePoint(opt_value, point2);
        }
        else if (opt_name == "point3") {
          parsePoint(opt_value, point3);
        }
        else if (opt_name == "color") {
          color = opt_value;
        }
        else
          cerr << "Unrecognised triangle option '" << opt_name << "'" << endl;
      }

      addTriangle(point1, point2, point3, color);
    }
    else
      cerr << "Unrecognised tag '" << name << "'" << endl;
  }

  return true;
}

bool
CRayTracer::
parsePoint(const string &str, CPoint3D &point)
{
  vector<string> words;

  CStrUtil::addWords(str, words, " ,");

  int num_words = words.size();

  if (num_words != 3)
    return false;

  double x, y, z;

  if (! CStrUtil::toReal(CStrUtil::stripSpaces(words[0]), &x))
    return false;

  if (! CStrUtil::toReal(CStrUtil::stripSpaces(words[1]), &y))
    return false;

  if (! CStrUtil::toReal(CStrUtil::stripSpaces(words[2]), &z))
    return false;

  point.setXYZ(x, y, z);

  return true;
}

void
CRayTracer::
addSphere(const CPoint3D &, double radius, const string &color)
{
  CRaySphere *sphere = new CRaySphere(radius);

  sphere->setColor(CRGBA(color));

  shapes_.push_back(sphere);
}

void
CRayTracer::
addTriangle(const CPoint3D &point1, const CPoint3D &point2,
            const CPoint3D &point3, const string &color)
{
  CRayTriangle *triangle = new CRayTriangle(point1, point2, point3);

  triangle->setColor(CRGBA(color));

  shapes_.push_back(triangle);
}

bool
CRayTracer::
render(int width, int height)
{
  if (renderer_ == NULL)
    return false;

  CSampleMultiJitter samples(num_samples_);

  samples.init();

  ShapeListCI pshape1 = shapes_.begin();
  ShapeListCI pshape2 = shapes_.end();

  ShapeListCI pshape;

  camera_ = new CRayCamera(CPoint3D(width/2, height/2, 500),
                           CVector3D(0, 0, -1),
                           CVector3D(0, 1, 0),
                           500,
                           -width/2, -height/2, width/2, height/2,
                           sqrt(2));

  CRayHitData hit_data;

  double tmax;
  CRGBA  fg, cmax;

  CRGBA bg = CRGBA(0,0,0);

  for (int y = 0; y < height; ++y) {
    double yy = double(height - y - 1)/(height - 1);

    for (int x = 0; x < width; ++x) {
      double xx = double(x)/(width - 1);

      bool is_hit = false;

      fg = CRGBA(0,0,0);

      for (uint i = 0; i < num_samples_; ++i) {
        bool is_hit1 = false;

        CRay ray = camera_->getRay(xx, yy, samples.getX(i), samples.getY(i));

        tmax = 1E50;

        for (pshape = pshape1; pshape != pshape2; ++pshape) {
          if ((*pshape)->hit(ray, 1E-6, tmax, hit_data)) {
            tmax = hit_data.t;
            cmax = (*pshape)->getColor(CPoint3D(0,0,0));

            is_hit1 = true;
          }
        }

        if (is_hit1) {
          fg += cmax;

          is_hit = true;
        }
      }

      if (is_hit)
        fg /= num_samples_;
      else
        fg = bg;

      renderer_->setForeground(fg);

      renderer_->drawPoint(CIPoint2D(x, y));
    }
  }

  return true;
}
