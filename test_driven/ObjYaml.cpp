#include <ObjYaml.h>
#include <Camera.h>
#include <PointLight.h>
#include <Cube.h>
#include <Sphere.h>
#include <Plane.h>
#include <World.h>
#include <Canvas.h>
#include <CYaml.h>
#include <fstream>

namespace RayTrace {

ObjYaml::
ObjYaml(const std::string &filename) :
 filename_(filename)
{
}

bool
ObjYaml::
read()
{
  CYaml yaml;

  if (! yaml.parse(filename_))
    return false;

  //---

  struct Visitor : public CYaml::Visitor {
    Visitor(World &world, Camera &camera) :
     world(world), camera(camera) {
    }

    bool valueToTuple(const CYaml::Scalar &value, double &x, double &y, double &z) const {
      if (value.type() != CYaml::Scalar::Type::DATA)
        return false;

      CYaml::ScalarData *data = value.data();

      if (data->type() != CYaml::ScalarData::Type::SEQUENCE)
        return false;

      if (data->sequence().size() != 3)
        return false;

      x = std::stod(data->sequence()[0].str());
      y = std::stod(data->sequence()[1].str());
      z = std::stod(data->sequence()[2].str());

      return true;
    }

    bool valueToPoint(const CYaml::Scalar &value, Point &point) const {
      double x, y, z;

      if (! valueToTuple(value, x, y, z))
        return false;

      point = Point(x, y, z);

      return true;
    }

    bool valueToVector(const CYaml::Scalar &value, Vector &vector) const {
      double x, y, z;

      if (! valueToTuple(value, x, y, z))
        return false;

      vector = Vector(x, y, z);

      return true;
    }

    bool valueToColor(const CYaml::Scalar &value, Color &color) const {
      double x, y, z;

      if (! valueToTuple(value, x, y, z))
        return false;

      color = Color(x, y, z);

      return true;
    }

    //---

    void visitStartSequence(CYaml::Scope *) override {
      //printDepth(); std::cerr << "[" << "\n";

      ++depth;
    }

    void visitSequence(CYaml::Scope *, const CYaml::Scalar &value) override {
      std::string valueStr = value.str();

      if      (in_transform) {
        if (value.type() == CYaml::Scalar::Type::DATA) {
          CYaml::ScalarData *data = value.data();

          if (data->type() != CYaml::ScalarData::Type::SEQUENCE) {
            std::cerr << "Invalid transform data\n";
            return;
          }

          if (data->sequence().size() < 1) {
            std::cerr << "Invalid transform data\n";
            return;
          }

          std::string type = data->sequence()[0].str();

          if      (type == "translate") {
            if (data->sequence().size() != 4) {
              std::cerr << "Invalid translate data\n";
              return;
            }

            double x = std::stod(data->sequence()[1].str());
            double y = std::stod(data->sequence()[2].str());
            double z = std::stod(data->sequence()[3].str());
std::cerr << "translate: " << x << " " << y << " " << z << "\n";

            Matrix4D m = Matrix4D::translation(x, y, z);

            object->preTransform(m);
          }
          else if (type == "scale") {
            if (data->sequence().size() != 4) {
              std::cerr << "Invalid scale data\n";
              return;
            }

            double x = std::stod(data->sequence()[1].str());
            double y = std::stod(data->sequence()[2].str());
            double z = std::stod(data->sequence()[3].str());
std::cerr << "scale: " << x << " " << y << " " << z << "\n";

            Matrix4D m = Matrix4D::scale(x, y, z);

            object->preTransform(m);
          }
          else if (type == "rotate-x") {
            if (data->sequence().size() != 2) {
              std::cerr << "Invalid rotate-x data\n";
              return;
            }

            double a = std::stod(data->sequence()[1].str());
std::cerr << "rotate-x: " << a << "\n";

            Matrix4D m = Matrix4D::rotation(Matrix4D::AxisType::X, a);

            object->preTransform(m);
          }
          else if (type == "rotate-y") {
            if (data->sequence().size() != 2) {
              std::cerr << "Invalid rotate-y data\n";
              return;
            }

            double a = std::stod(data->sequence()[1].str());
std::cerr << "rotate-y: " << a << "\n";

            Matrix4D m = Matrix4D::rotation(Matrix4D::AxisType::Y, a);

            object->preTransform(m);
          }
          else if (type == "rotate-z") {
            if (data->sequence().size() != 2) {
              std::cerr << "Invalid rotate-z data\n";
              return;
            }

            double a = std::stod(data->sequence()[1].str());
std::cerr << "rotate-z: " << a << "\n";

            Matrix4D m = Matrix4D::rotation(Matrix4D::AxisType::Z, a);

            object->preTransform(m);
          }
          else {
            printDepth(); std::cerr << valueStr << "\n";
          }
        }
        else {
          Define *define = getDefine(valueStr);

          processDefine(define);
        }
      }
      else if (in_value) {
        Define *define = getDefine(defName);

        if (value.type() == CYaml::Scalar::Type::DATA)
          define->addValue(value);
        else {
          Define *extDefine = getDefine(valueStr);

          for (const auto &nv : extDefine->nameValues)
            define->addNameValue(nv.first, nv.second);

          for (const auto &v : extDefine->values)
            define->addValue(v);
        }
      }
      else {
        printDepth(); std::cerr << valueStr << "\n";
      }
    }

    void visitEndSequence(CYaml::Scope *) override {
      --depth;

      //printDepth(); std::cerr << "]" << "\n";

      cmd = "";
    }

    void visitStartMapping(CYaml::Scope *) override {
      //printDepth(); std::cerr << "{" << "\n";

      ++depth;
    }

    void visitMapping(CYaml::Scope *, const CYaml::Scalar &name,
                      const CYaml::Scalar &value) override {
      std::string nameStr  = name .str();
      std::string valueStr = value.str();

      if      (depth == 2) {
        if (cmd == "") {
          cmd    = name .str();
          detail = value.str();

          //std::cerr << "Command: " << cmd << " : " << detail << "\n";

          if      (cmd == "add" && detail == "camera") {
          }
          else if (cmd == "add" && detail == "light") {
            light = std::make_shared<PointLight>();

            world.addLight(light);
          }
          else if (cmd == "add" && detail == "plane") {
            auto plane = std::make_shared<Plane>();

            world.addObject(plane);
std::cerr << "add plane\n";

            object = plane;
          }
          else if (cmd == "add" && detail == "sphere") {
            auto sphere = std::make_shared<Sphere>();

            world.addObject(sphere);
std::cerr << "add sphere\n";

            object = sphere;
          }
          else if (cmd == "add" && detail == "cube") {
            auto cube = std::make_shared<Cube>();

            world.addObject(cube);
std::cerr << "add cube\n";

            object = cube;
          }
          else if (cmd == "define") {
            defName = detail;
          }
          else {
            printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
          }
        }
        else {
          if      (cmd == "add" && detail == "camera") {
            if      (nameStr == "width") {
              camera.setHSize(std::stod(valueStr));
            }
            else if (nameStr == "height") {
              camera.setVSize(std::stod(valueStr));
            }
            else if (nameStr == "field-of-view") {
              camera.setFov(std::stod(valueStr));
            }
            else if (nameStr == "from") {
              valueToPoint(value, camera_from);

              camera.setTransform(viewTransform(camera_from, camera_to, camera_up));
            }
            else if (nameStr == "to") {
              valueToPoint(value, camera_to);

              camera.setTransform(viewTransform(camera_from, camera_to, camera_up));
            }
            else if (nameStr == "up") {
              valueToVector(value, camera_up);

              camera.setTransform(viewTransform(camera_from, camera_to, camera_up));
            }
            else {
              printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
            }
          }
          else if (cmd == "add" && detail == "light") {
            if      (nameStr == "at") {
              Point point;

              valueToPoint(value, point);

              light->setPosition(point);
            }
            else if (nameStr == "intensity") {
              Color color;

              valueToColor(value, color);

              light->setIntensity(color);
            }
            else {
              printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
            }
          }
          else if (cmd == "add" && detail == "plane") {
            if      (nameStr == "material") {
              in_material = true;

              if (value.type() != CYaml::Scalar::Type::DATA) {
                Define *define = getDefine(valueStr);

                processDefine(define);
              }
            }
            else if (nameStr == "transform") {
              in_transform = true;
            }
            else {
              printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
            }
          }
          else if (cmd == "add" && detail == "sphere") {
            if      (nameStr == "material") {
              in_material = true;

              if (value.type() != CYaml::Scalar::Type::DATA) {
                Define *define = getDefine(valueStr);

                processDefine(define);
              }
            }
            else if (nameStr == "transform") {
              in_transform = true;
            }
            else {
              printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
            }
          }
          else if (cmd == "add" && detail == "cube") {
            if      (nameStr == "material") {
              in_material = true;

              if (value.type() != CYaml::Scalar::Type::DATA) {
                Define *define = getDefine(valueStr);

                processDefine(define);
              }
            }
            else if (nameStr == "transform") {
              in_transform = true;
            }
            else {
              printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
            }
          }
          else if (cmd == "define") {
            Define *define = getDefine(defName);

            if      (nameStr == "extend") {
              Define *extDefine = getDefine(valueStr);

              for (const auto &nv : extDefine->nameValues)
                define->addNameValue(nv.first, nv.second);

              for (const auto &v : extDefine->values)
                define->addValue(v);
            }
            else if (nameStr == "value") {
              in_value = true;
            }
            else {
              printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
            }
          }
          else {
            printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
          }
        }
      }
      else if (depth == 3) {
        std::string nameStr  = name .str();
        std::string valueStr = value.str();

        if      (in_material) {
          if      (nameStr == "color") {
            Color color;

            valueToColor(value, color);

            object->material().setColor(color);
          }
          else if (nameStr == "diffuse") {
            double diffuse = std::stod(valueStr);

            object->material().setDiffuse(diffuse);
          }
          else if (nameStr == "ambient") {
            double ambient = std::stod(valueStr);

            object->material().setAmbient(ambient);
          }
          else if (nameStr == "specular") {
            double specular = std::stod(valueStr);

            object->material().setSpecular(specular);
          }
          else if (nameStr == "shininess") {
            double shininess = std::stod(valueStr);

            object->material().setShininess(shininess);
          }
          else if (nameStr == "reflective") {
            double reflective = std::stod(valueStr);

            object->material().setReflective(reflective);
          }
          else if (nameStr == "transparency") {
            double transparency = std::stod(valueStr);

            object->material().setTransparency(transparency);
          }
          else if (nameStr == "refractive-index") {
            double refract = std::stod(valueStr);

            object->material().setRefractiveIndex(refract);
          }
          else {
            printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
          }
        }
        else if (in_value) {
          Define *define = getDefine(defName);

          define->addNameValue(name, value);
        }
        else {
          printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
        }
      }
      else {
        printDepth(); std::cerr << nameStr << " = " << valueStr << "\n";
      }
    }

    void visitEndMapping(CYaml::Scope *) override {
      --depth;

      //printDepth(); std::cerr << "}" << "\n";

      if (depth == 1)
        cmd = "";

      if (depth == 2) {
        in_material  = false;
        in_transform = false;
        in_value     = false;
      }
    }

    void printDepth() {
      for (int i = 0; i < depth; ++i)
        std::cerr << " ";
    }

    using NameValues = CYaml::Mapping;
    using Values     = std::vector<CYaml::Scalar>;

    struct Define {
      Define(const std::string &name) :
       name(name) {
      }

      void addNameValue(const CYaml::Scalar &name, const CYaml::Scalar &value) {
        nameValues.addNameValue(name, value);
      }

      void addValue(const CYaml::Scalar &value) {
        values.push_back(value);
      }

      std::string name;
      NameValues  nameValues;
      Values      values;
    };

    using Defines = std::map<std::string,Define *>;

    Define *getDefine(const std::string &name) {
      auto p = defines.find(name);

      if (p == defines.end())
        p = defines.insert(p, Defines::value_type(name, new Define(name)));

      return (*p).second;
    }

    void processDefine(Define *define) {
      ++depth;

      for (const auto &nv : define->nameValues)
        visitMapping(nullptr, nv.first, nv.second);

      --depth;

      ++depth;

      for (const auto &v : define->values)
        visitSequence(nullptr, v);

      --depth;
    }

    void printDefines() const {
      for (auto &nd : defines) {
        Define *define = nd.second;

        std::cerr << define->name << "\n";

        for (const auto &nv : define->nameValues)
          std::cerr << " " << nv.first.str() << " : " << nv.second.str() << "\n";

        for (const auto &v : define->values)
          std::cerr << " " << v.str() << "\n";
      }
    }

    World&      world;
    Camera&     camera;
    int         depth       { 0 };
    std::string cmd;
    std::string detail;
    std::string defName;
    Point       camera_from  { 0, 0, -1 };
    Point       camera_to    { 0, 0,  0 };
    Vector      camera_up    { 0, 1,  0 };
    ObjectP     object;
    PointLightP light;
    bool        in_material  { false };
    bool        in_transform { false };
    bool        in_value     { false };
    Defines     defines;
  };

  World  world;
  Camera camera;

  Visitor visitor(world, camera);

  yaml.visit(visitor);

  visitor.printDefines();

  Canvas canvas;

  render(canvas, camera, world);

  auto fs = std::ofstream("images/yaml.ppm", std::ofstream::out);

  canvas.writePPM(fs);

  return true;
}

}
