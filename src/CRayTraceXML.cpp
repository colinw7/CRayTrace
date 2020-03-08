#include <CRayTraceXML.h>
#include <CRayTrace.h>
#include <CRayTraceCamera.h>
#include <CRayTraceLight.h>
#include <CRayShapeLib.h>
#include <CXMLLib.h>
#include <CRGBName.h>
#include <CEnv.h>

using std::string;
using std::vector;

bool
CRayTraceXML::
read(const string &filename)
{
  CXML     xml;
  CXMLTag *tag;

  if (! xml.read(filename, &tag) || tag == NULL)
    return false;

  if (tag->getName() != "raytracer")
    return false;

  double scale = 1.0;

  int width  = raytrace_->getWidth ();
  int height = raytrace_->getHeight();

  // handle raytracer options
  const CXMLTag::OptionArray &options = tag->getOptions();

  int num_options = tag->getNumOptions();

  for (int j = 0; j < num_options; ++j) {
    CXMLTagOption *option = options[j];

    const string &opt_name  = option->getName ();
    const string &opt_value = option->getValue();

    if      (opt_name == "width") {
      width = CStrUtil::toInteger(opt_value);
    }
    else if (opt_name == "height") {
      height = CStrUtil::toInteger(opt_value);
    }
    else if (opt_name == "scale") {
      scale = CStrUtil::toReal(opt_value);
    }
    else if (opt_name == "num_samples") {
      int num_samples = CStrUtil::toInteger(opt_value);

      raytrace_->setNumSamples(num_samples);
    }
    else if (opt_name == "minT") {
      double minT = CStrUtil::toReal(opt_value);

      raytrace_->setMinT(minT);
    }
    else if (opt_name == "maxT") {
      double maxT = CStrUtil::toReal(opt_value);

      raytrace_->setMaxT(maxT);
    }
    else if (opt_name == "bg") {
      double r, g, b, a;

      CRGBName::lookup(opt_value, &r, &g, &b, &a);

      CRGBA bg(r, g, b, a);

      raytrace_->setBg(bg);
    }
    else if (opt_name == "fg") {
      double r, g, b, a;

      CRGBName::lookup(opt_value, &r, &g, &b, &a);

      CRGBA fg(r, g, b, a);

      raytrace_->setFg(fg);
    }
    else if (opt_name == "reflect_depth") {
      int reflect_depth = CStrUtil::toInteger(opt_value);

      raytrace_->setReflectDepth(reflect_depth);
    }
    else if (opt_name == "refract_depth") {
      int refract_depth = CStrUtil::toInteger(opt_value);

      raytrace_->setRefractDepth(refract_depth);
    }
    else if (opt_name == "alpha_depth") {
      int alpha_depth = CStrUtil::toInteger(opt_value);

      raytrace_->setAlphaDepth(alpha_depth);
    }
    else
      std::cerr << "Unrecognised raytracer option '" << opt_name << "'" << std::endl;
  }

  if (width  <= 0) width  = raytrace_->getWidth ();
  if (height <= 0) height = raytrace_->getHeight();

  raytrace_->setSize(width, height);

  //------

  CXMLTag::TokenArray children = tag->getChildren();

  int num_children = tag->getNumChildren();

  for (int i = 0; i < num_children; ++i) {
    const CXMLToken *token = children[i];

    if (! token->isTag()) continue;

    CXMLTag *tag1 = token->getTag();

    const string &name = tag1->getName();

    int num_options1 = tag1->getNumOptions();

    const CXMLTag::OptionArray &options1 = tag1->getOptions();

    CRayTraceShapeData shape_data;

    shape_data.id = name;

    // handle sphere
    if      (name == "sphere") {
      double radius (1.0);
      double zmin   (-1000);
      double zmax   ( 1000);
      double phi_max(360.0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "radius") {
          parseReal(opt_name, opt_value, &radius);
        }
        else if (opt_name == "zmin") {
          parseReal(opt_name, opt_value, &zmin);
        }
        else if (opt_name == "zmax") {
          parseReal(opt_name, opt_value, &zmax);
        }
        else if (opt_name == "phi_max") {
          parseReal(opt_name, opt_value, &phi_max);
        }
        else if (opt_name == "center") {
          parsePoint(opt_name, opt_value, shape_data.translate);
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised sphere option '" << opt_name << "'" << std::endl;
        }
      }

      CRaySphere *sphere = raytrace_->addSphere(radius, shape_data);

      sphere->setPhiLimit(phi_max);

      sphere->setZLimit(zmin, zmax);
    }
    // handle cone
    else if (name == "cone") {
      double radius (1.0);
      double cheight (1.0);
      double phi_max(360.0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "radius") {
          parseReal(opt_name, opt_value, &radius);
        }
        else if (opt_name == "height") {
          parseReal(opt_name, opt_value, &cheight);
        }
        else if (opt_name == "phi_max") {
          parseReal(opt_name, opt_value, &phi_max);
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised cone option '" << opt_name << "'" << std::endl;
        }
      }

      CRayCone *cone = raytrace_->addCone(radius, cheight, shape_data);

      cone->setPhiLimit(phi_max);
    }
    // handle cylinder
    else if (name == "cylinder") {
      double radius  (1.0);
      double cheight (1.0);
      double zmin    (-1000);
      double zmax    ( 1000);
      double phi_max (360.0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "radius") {
          parseReal(opt_name, opt_value, &radius);
        }
        else if (opt_name == "height") {
          parseReal(opt_name, opt_value, &cheight);
        }
        else if (opt_name == "zmin") {
          parseReal(opt_name, opt_value, &zmin);
        }
        else if (opt_name == "zmax") {
          parseReal(opt_name, opt_value, &zmax);
        }
        else if (opt_name == "phi_max") {
          parseReal(opt_name, opt_value, &phi_max);
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised cylinder option '" << opt_name << "'" << std::endl;
        }
      }

      CRayCylinder *cylinder = raytrace_->addCylinder(radius, cheight, shape_data);

      cylinder->setPhiLimit(phi_max);

      cylinder->setZLimit(zmin, zmax);
    }
    // handle hyperboloid
    else if (name == "hyperboloid") {
      CPoint3D point1 (0,0,0);
      CPoint3D point2 (1,1,1);
      double   phi_max(360.0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "point1") {
          parsePoint(opt_name, opt_value, point1);
        }
        else if (opt_name == "point2") {
          parsePoint(opt_name, opt_value, point2);
        }
        else if (opt_name == "phi_max") {
          parseReal(opt_name, opt_value, &phi_max);
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised hyperboloid option '" <<
                  opt_name << "'" << std::endl;
        }
      }

      CRayHyperboloid *hyperboloid = raytrace_->addHyperboloid(point1, point2, shape_data);

      hyperboloid->setPhiLimit(phi_max);
    }
    // handle paraboloid
    else if (name == "paraboloid") {
      double radius (1.0);
      double zmin   (0.0);
      double zmax   (1.0);
      double phi_max(360.0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "radius") {
          parseReal(opt_name, opt_value, &radius);
        }
        else if (opt_name == "zmin") {
          parseReal(opt_name, opt_value, &zmin);
        }
        else if (opt_name == "zmax") {
          parseReal(opt_name, opt_value, &zmax);
        }
        else if (opt_name == "phi_max") {
          parseReal(opt_name, opt_value, &phi_max);
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised paraboloid option '" << opt_name << "'" << std::endl;
        }
      }

      CRayParaboloid *paraboloid = raytrace_->addParaboloid(radius, zmin, zmax, shape_data);

      paraboloid->setPhiLimit(phi_max);
    }
    // handle disk
    else if (name == "disk") {
      double radius      (1.0);
      double dheight     (1.0);
      double inner_radius(0.0);
      double phi_max     (360.0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "radius") {
          parseReal(opt_name, opt_value, &radius);
        }
        else if (opt_name == "height") {
          parseReal(opt_name, opt_value, &dheight);
        }
        else if (opt_name == "inner_radius") {
          parseReal(opt_name, opt_value, &inner_radius);
        }
        else if (opt_name == "phi_max") {
          parseReal(opt_name, opt_value, &phi_max);
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised disk option '" << opt_name << "'" << std::endl;
        }
      }

      CRayDisk *disk = raytrace_->addDisk(radius, dheight, inner_radius, shape_data);

      disk->setPhiLimit(phi_max);
    }
    // handle cube
    else if (name == "cube") {
      double size(1.0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "size") {
          parseReal(opt_name, opt_value, &size);
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised cube option '" << opt_name << "'" << std::endl;
        }
      }

      //CRayCube *cube =
      raytrace_->addCube(size, shape_data);
    }
    // handle box
    else if (name == "box") {
      double xsize(1.0);
      double ysize(1.0);
      double zsize(1.0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "xsize") {
          parseReal(opt_name, opt_value, &xsize);
        }
        else if (opt_name == "ysize") {
          parseReal(opt_name, opt_value, &ysize);
        }
        else if (opt_name == "zsize") {
          parseReal(opt_name, opt_value, &zsize);
        }
        else if (opt_name == "size") {
          CPoint3D size(1,1,1);

          parsePoint(opt_name, opt_value, size);

          xsize = size.x;
          ysize = size.y;
          zsize = size.z;
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised box option '" << opt_name << "'" << std::endl;
        }
      }

      //CRayBox *box =
      shape_data.translate.x *= scale;
      shape_data.translate.y *= scale;
      shape_data.translate.z *= scale;

      raytrace_->addBox(xsize*scale, ysize*scale, zsize*scale, shape_data);
    }
    // handle triangle
    else if (name == "triangle") {
      CPoint3D point1(0,0,0);
      CPoint3D point2(1,0,0);
      CPoint3D point3(0,1,0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "point1") {
          parsePoint(opt_name, opt_value, point1);
        }
        else if (opt_name == "point2") {
          parsePoint(opt_name, opt_value, point2);
        }
        else if (opt_name == "point3") {
          parsePoint(opt_name, opt_value, point3);
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised triangle option '" << opt_name << "'" << std::endl;
        }
      }

      // CRayTriangle *triangle =
      raytrace_->addTriangle(point1, point2, point3, shape_data);
    }
    // handle plane
    else if (name == "plane") {
      CPoint3D point1(0,0,0);
      CPoint3D point2(1,0,0);
      CPoint3D point3(1,1,0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "point1") {
          parsePoint(opt_name, opt_value, point1);
        }
        else if (opt_name == "point2") {
          parsePoint(opt_name, opt_value, point2);
        }
        else if (opt_name == "point3") {
          parsePoint(opt_name, opt_value, point3);
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised plane option '" << opt_name << "'" << std::endl;
        }
      }

      //CRayPlane *plane =
      raytrace_->addPlane(point1, point2, point3, shape_data);
    }
    // handle model
    else if (name == "model") {
      string   modelName      = "";
      double   modelScale     = 1.0;
      bool     auto_scale     = false;
      CPoint3D translate      = CPoint3D(0,0,0);
      bool     auto_translate = false;
      CPoint3D rotate         = CPoint3D(0,0,0);

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "name") {
          modelName = opt_value;

          if (modelName[0] == '$')
            modelName = CEnvInst.get(modelName.substr(1));
        }
        else if (opt_name == "scale") {
          if (opt_value == "auto")
            auto_scale = true;
          else
            parseReal(opt_name, opt_value, &modelScale);
        }
        else if (opt_name == "translate") {
          if      (opt_value == "auto")
            auto_translate = true;
          else
            parsePoint(opt_name, opt_value, translate);
        }
        else if (opt_name == "rotate") {
          parsePoint(opt_name, opt_value, rotate);
        }
        else if (! shapeOption(shape_data, opt_name, opt_value)) {
          std::cerr << "Unrecognised model option '" << opt_name << "'" << std::endl;
        }
      }

      if (modelName != "")
        raytrace_->addModel(modelName, modelScale, auto_scale, translate, auto_translate,
                            rotate, shape_data);
    }
    // handle light
    else if (name == "light") {
      string   id       = "light";
      CPoint3D position = CPoint3D(0,0,0);
      string   color    = "";

      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "id") {
          id = opt_value;
        }
        else if (opt_name == "position") {
          parsePoint(opt_name, opt_value, position);
        }
        else if (opt_name == "color") {
          color = opt_value;
        }
        else
          std::cerr << "Unrecognised light option '" << opt_name << "'" << std::endl;
      }

      CRayTraceLight *light = raytrace_->addLight(position);

      if (color != "") {
        double r, g, b, a;

        CRGBName::lookup(color, &r, &g, &b, &a);

        light->setAmbient(CRGBA(r, g, b, a));
      }

      light->setName(id);
    }
    // handle camera
    else if (name == "camera") {
      for (int j = 0; j < num_options1; ++j) {
        CXMLTagOption *option = options1[j];

        const string &opt_name  = option->getName ();
        const string &opt_value = option->getValue();

        if      (opt_name == "z1") {
          double z1;

          if (parseReal(opt_name, opt_value, &z1))
            raytrace_->getCamera()->setZ1(z1);
        }
        else if (opt_name == "z2") {
          double z2;

          if (parseReal(opt_name, opt_value, &z2))
            raytrace_->getCamera()->setZ2(z2);
        }
        else if (opt_name == "perspective") {
          bool perspective = CStrUtil::toBool(opt_value);

          raytrace_->getCamera()->setPerspective(perspective);
        }
        else if (opt_name == "position") {
          CPoint3D position;

          if (parsePoint(opt_name, opt_value, position))
            raytrace_->getCamera()->setPosition(position);
        }
        else if (opt_name == "lookat") {
          CPoint3D lookat;

          if (parsePoint(opt_name, opt_value, lookat))
            raytrace_->getCamera()->setLookAt(lookat);
        }
        else if (opt_name == "up") {
          CPoint3D up;

          if (parsePoint(opt_name, opt_value, up))
            raytrace_->getCamera()->setUp(CVector3D(up));
        }
        else if (opt_name == "fov") {
          double fov;

          if (parseReal(opt_name, opt_value, &fov))
            raytrace_->getCamera()->setFieldOfView(fov);
        }
        else
          std::cerr << "Unrecognised light option '" << opt_name << "'" << std::endl;
      }
    }
    else
      std::cerr << "Unrecognised tag '" << name << "'" << std::endl;
  }

  return true;
}

bool
CRayTraceXML::
shapeOption(CRayTraceShapeData &shape_data, const string &name, const string &value) const
{
  if      (name == "id") {
    shape_data.id = value;
  }
  else if (name == "color") {
    shape_data.color = value;
  }
  else if (name == "translate") {
    parsePoint(name, value, shape_data.translate);
  }
  else if (name == "scale") {
    parsePoint(name, value, shape_data.scale);
 }
  else if (name == "rotate") {
    parsePoint(name, value, shape_data.rotate);
  }
  else if (name == "marble") {
    shape_data.marble = CStrUtil::toBool(value);
  }
  else if (name == "noise") {
    shape_data.noise = CStrUtil::toBool(value);
  }
  else if (name == "mandelbrot") {
    shape_data.mandelbrot = CStrUtil::toBool(value);
  }
  else if (name == "image") {
    shape_data.image = value;
  }
  else if (name == "reflect") {
    parseReal(name, value, &shape_data.reflect);
  }
  else if (name == "refract") {
    parseReal(name, value, &shape_data.refract);
  }
  else if (name == "refract_index") {
    parseReal(name, value, &shape_data.refract_index);
  }
  else if (name == "ignore_light") {
    shape_data.ignore_light = CStrUtil::toBool(value);
  }
  else
    return false;

  return true;
}

bool
CRayTraceXML::
parseReal(const string &name, const string &value, double *real) const
{
  double real1;

  if (! CStrUtil::toReal(value, &real1)) {
    std::cerr << "Illegal real value for '" << name << "'" << std::endl;
    return false;
  }

  *real = real1;

  return true;
}

bool
CRayTraceXML::
parsePoint(const string &name, const string &value, CPoint3D &point) const
{
  vector<string> words;

  CStrUtil::addWords(value, words, " ,");

  int num_words = words.size();

  if (num_words != 3) {
    std::cerr << "Illegal number of values for '" << name << "'" << std::endl;
    return false;
  }

  double x, y, z;

  if (! parseReal("x", words[0], &x)) return false;
  if (! parseReal("y", words[1], &y)) return false;
  if (! parseReal("z", words[2], &z)) return false;

  point.setXYZ(x, y, z);

  return true;
}
