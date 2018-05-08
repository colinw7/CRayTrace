#include <CCeilL.h>
#include <CRayTrace.h>
#include <CRayTraceLight.h>
#include <CRayTraceCamera.h>
#include <CRayShapeLib.h>
#include <CCeilRayTrace.h>
#include <CGeomLight3D.h>
#include <CConv.h>
#include <CRGBName.h>
#include <COptVal.h>

#define MODULE_NAME "raytrace"

#define LOUT(a) ClLanguageMgrInst->output(a)

static bool CCeilRayTraceInit
             (ClModuleInitType, void *data);
static bool CCeilRayTraceHelp
             (const char *args, void *data);
static void CCeilRayTraceAddSphereCmd
             (ClLanguageCommand *, ClLanguageArgs *, void *);
static void CCeilRayTraceAddCubeCmd
             (ClLanguageCommand *, ClLanguageArgs *, void *);
static void CCeilRayTraceAddPlaneCmd
             (ClLanguageCommand *, ClLanguageArgs *, void *);
static void CCeilRayTraceAddModelCmd
             (ClLanguageCommand *, ClLanguageArgs *, void *);
static void CCeilRayTraceAddLightCmd
             (ClLanguageCommand *, ClLanguageArgs *, void *);
static void CCeilRayTraceTranslateShapeCmd
             (ClLanguageCommand *, ClLanguageArgs *, void *);
static void CCeilRayTraceRotateShapeCmd
             (ClLanguageCommand *, ClLanguageArgs *, void *);
static void CCeilRayTraceMoveLightCmd
             (ClLanguageCommand *, ClLanguageArgs *, void *);
static void CCeilRayTraceMoveCameraCmd
             (ClLanguageCommand *, ClLanguageArgs *, void *);
static void CCeilRayTraceRenderCmd
             (ClLanguageCommand *, ClLanguageArgs *, void *);
static void CCeilRayTraceParseShapeArgs
             (ClLanguageArgs *, CRayTraceShapeData &);
static bool CCeilRayTraceIsShapeArg
             (const std::string &, int *);

// Add the RayTrace Module.

CCeilRayTrace::
CCeilRayTrace(CRayTrace *raytrace) :
 raytrace_(raytrace)
{
  ClModuleMgrInst->defineModule(MODULE_NAME);

  ClModuleMgrInst->setInitProc(MODULE_NAME, CCeilRayTraceInit, this);
  ClModuleMgrInst->setHelpProc(MODULE_NAME, CCeilRayTraceHelp, this);
}

// Initialise/Re-Initialise the RayTrace Module.

static bool
CCeilRayTraceInit(ClModuleInitType flag, void *data)
{
  if (flag == CL_MODULE_INIT_TYPE_REINIT)
    return true;

  //---

  ClLanguageMgr *lmgr = ClLanguageMgrInst;

  ClParserScopePtr scope = ClParserInst->getScope(MODULE_NAME);

  lmgr->defineCommand(scope, "add_sphere"     , CCeilRayTraceAddSphereCmd     , data);
  lmgr->defineCommand(scope, "add_cube"       , CCeilRayTraceAddCubeCmd       , data);
  lmgr->defineCommand(scope, "add_plane"      , CCeilRayTraceAddPlaneCmd      , data);
  lmgr->defineCommand(scope, "add_model"      , CCeilRayTraceAddModelCmd      , data);
  lmgr->defineCommand(scope, "add_light"      , CCeilRayTraceAddLightCmd      , data);
  lmgr->defineCommand(scope, "translate_shape", CCeilRayTraceTranslateShapeCmd, data);
  lmgr->defineCommand(scope, "rotate_shape"   , CCeilRayTraceRotateShapeCmd   , data);
  lmgr->defineCommand(scope, "move_light"     , CCeilRayTraceMoveLightCmd     , data);
  lmgr->defineCommand(scope, "move_camera"    , CCeilRayTraceMoveCameraCmd    , data);
  lmgr->defineCommand(scope, "render"         , CCeilRayTraceRenderCmd        , data);

  //---

  return true;
}

// Provide Help for the RayTrace Module.

static bool
CCeilRayTraceHelp(const char *, void *)
{
  LOUT("\n");
  LOUT("Commands\n");
  LOUT("--------\n");
  LOUT("\n");
  LOUT("add_sphere -radius <r> -zmin <r> -zmax <r> -phi_max<r> ...\n");
  LOUT("add_cube -size <r> ...\n");
  LOUT("add_plane -p1 <p> -p2 <p> -p3 <p> ...\n");
  LOUT("add_model -filename <f> -scale <s> -auto_scale -translate <p> "
       "-auto_translate -rotate <p>\n");
  LOUT("add_light -id <id> -position <p> -color <c>\n");
  LOUT("translate_shape -id <id> -delta <p>\n");
  LOUT("rotate_shape -id <id> -delta <p>\n");
  LOUT("move_light -id <id> -delta <p>\n");
  LOUT("move_camera -delta <p>\n");
  LOUT("render\n");
  LOUT("\n");

  return true;
}

static void
CCeilRayTraceAddSphereCmd(ClLanguageCommand *command, ClLanguageArgs *args, void *data)
{
  args->setSpaceSeparated(true);

  args->setArgs(command);

  double radius = 1.0;

  CRayTraceShapeData shape_data;

  CCeilRayTraceParseShapeArgs(args, shape_data);

  uint num_args = args->getNumArgs();

  int error_code, skip;

  for (uint i = 0; i < num_args; ++i) {
    std::string arg = args->getArg(i + 1, &error_code);

    if (arg[0] == '-') {
      if      (arg == "-radius") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        radius = args->getRealArg(i + 1, &error_code);
      }
      else if (CCeilRayTraceIsShapeArg(arg, &skip)) {
        i += skip;
      }
      else
        ClParserInst->error("Invalid option '%s'", arg.c_str());
    }
    else
      ClParserInst->error("Invalid argument '%s'", arg.c_str());
  }

  CCeilRayTrace *raytrace = static_cast<CCeilRayTrace *>(data);

  raytrace->getRayTrace()->addSphere(radius, shape_data);
}

static void
CCeilRayTraceAddCubeCmd(ClLanguageCommand *command, ClLanguageArgs *args, void *data)
{
  args->setSpaceSeparated(true);

  args->setArgs(command);

  double size = 1.0;

  CRayTraceShapeData shape_data;

  CCeilRayTraceParseShapeArgs(args, shape_data);

  uint num_args = args->getNumArgs();

  int error_code, skip;

  for (uint i = 0; i < num_args; ++i) {
    std::string arg = args->getArg(i + 1, &error_code);

    if (arg[0] == '-') {
      if      (arg == "-size") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        size = args->getRealArg(i + 1, &error_code);
      }
      else if (CCeilRayTraceIsShapeArg(arg, &skip)) {
        i += skip;
      }
      else
        ClParserInst->error("Invalid option '%s'", arg.c_str());
    }
    else
      ClParserInst->error("Invalid argument '%s'", arg.c_str());
  }

  CCeilRayTrace *raytrace = static_cast<CCeilRayTrace *>(data);

  raytrace->getRayTrace()->addCube(size, shape_data);
}

static void
CCeilRayTraceAddPlaneCmd(ClLanguageCommand *command, ClLanguageArgs *args, void *data)
{
  args->setSpaceSeparated(true);

  args->setArgs(command);

  CPoint3D p1(0,0,0);
  CPoint3D p2(1,0,0);
  CPoint3D p3(1,1,0);

  CRayTraceShapeData shape_data;

  CCeilRayTraceParseShapeArgs(args, shape_data);

  uint num_args = args->getNumArgs();

  int error_code, skip;

  for (uint i = 0; i < num_args; ++i) {
    std::string arg = args->getArg(i + 1, &error_code);

    if (arg[0] == '-') {
      if      (arg == "-p1") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        double *reals;
        uint    num_reals;

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          p1 = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else if (arg == "-p2") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        double *reals;
        uint    num_reals;

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          p2 = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else if (arg == "-p3") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        double *reals;
        uint    num_reals;

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          p3 = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else if (CCeilRayTraceIsShapeArg(arg, &skip)) {
        i += skip;
      }
      else
        ClParserInst->error("Invalid option '%s'", arg.c_str());
    }
    else
      ClParserInst->error("Invalid argument '%s'", arg.c_str());
  }

  CCeilRayTrace *raytrace = static_cast<CCeilRayTrace *>(data);

  raytrace->getRayTrace()->addPlane(p1, p2, p3, shape_data);
}

static void
CCeilRayTraceAddModelCmd(ClLanguageCommand *command, ClLanguageArgs *args, void *data)
{
  args->setSpaceSeparated(true);

  args->setArgs(command);

  std::string filename;
  double      scale(1.0);
  bool        auto_scale(false);
  CPoint3D    translate(0,0,0);
  bool        auto_translate(false);
  CPoint3D    rotate(0,0,0);

  CRayTraceShapeData shape_data;

  CCeilRayTraceParseShapeArgs(args, shape_data);

  uint num_args = args->getNumArgs();

  int error_code, skip;

  for (uint i = 0; i < num_args; ++i) {
    std::string arg = args->getArg(i + 1, &error_code);

    if (arg[0] == '-') {
      if      (arg == "-filename") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        filename = args->getStringArg(i + 1, &error_code);
      }
      else if (arg == "-scale") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        scale = args->getRealArg(i + 1, &error_code);
      }
      else if (arg == "-auto_scale") {
        auto_scale = true;
      }
      else if (arg == "-translate") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        double *reals;
        uint    num_reals;

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          translate = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else if (arg == "-auto_translate") {
        auto_translate = true;
      }
      else if (arg == "-rotate") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        double *reals;
        uint    num_reals;

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          rotate = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else if (CCeilRayTraceIsShapeArg(arg, &skip)) {
        i += skip;
      }
      else
        ClParserInst->error("Invalid option '%s'", arg.c_str());
    }
    else
      ClParserInst->error("Invalid argument '%s'", arg.c_str());
  }

  CCeilRayTrace *raytrace = static_cast<CCeilRayTrace *>(data);

  raytrace->getRayTrace()->addModel(filename, scale, auto_scale, translate,
                                    auto_translate, rotate, shape_data);
}

static void
CCeilRayTraceAddLightCmd(ClLanguageCommand *command, ClLanguageArgs *args, void *data)
{
  args->setSpaceSeparated(true);

  args->setArgs(command);

  std::string id       = "light";
  CPoint3D    position = CPoint3D(0,0,0);
  std::string color    = "";

  uint num_args = args->getNumArgs();

  int error_code;

  for (uint i = 0; i < num_args; ++i) {
    std::string arg = args->getArg(i + 1, &error_code);

    if (arg[0] == '-') {
      if      (arg == "-id") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        id = args->getStringArg(i + 1, &error_code);
      }
      else if (arg == "-position") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        double *reals;
        uint    num_reals;

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          position = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else if (arg == "-color") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        color = args->getStringArg(i + 1, &error_code);
      }
      else
        ClParserInst->error("Invalid option '%s'", arg.c_str());
    }
    else
      ClParserInst->error("Invalid argument '%s'", arg.c_str());
  }

  CCeilRayTrace *raytrace = static_cast<CCeilRayTrace *>(data);

  CRayTraceLight *light = raytrace->getRayTrace()->addLight(position);

  if (color != "")
    light->setAmbient(CRGBName::toRGBA(color));

  light->setName(id);
}

static void
CCeilRayTraceTranslateShapeCmd(ClLanguageCommand *command, ClLanguageArgs *args, void *data)
{
  args->setSpaceSeparated(true);

  args->setArgs(command);

  std::string id    = "shape";
  CPoint3D    delta = CPoint3D(0,0,0);

  uint num_args = args->getNumArgs();

  int error_code;

  for (uint i = 0; i < num_args; ++i) {
    std::string arg = args->getArg(i + 1, &error_code);

    if (arg[0] == '-') {
      if      (arg == "-id") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        id = args->getStringArg(i + 1, &error_code);
      }
      else if (arg == "-delta") {
        double *reals;
        uint    num_reals;

        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          delta = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else
        ClParserInst->error("Invalid option '%s'", arg.c_str());
    }
    else
      ClParserInst->error("Invalid argument '%s'", arg.c_str());
  }

  CCeilRayTrace *raytrace = static_cast<CCeilRayTrace *>(data);

  CRayShape *shape = raytrace->getRayTrace()->getShape(id);

  if (shape == NULL) {
    ClParserInst->error("Invalid shape '%s'", id.c_str());
    return;
  }

  shape->translate(delta);
}

static void
CCeilRayTraceRotateShapeCmd(ClLanguageCommand *command, ClLanguageArgs *args, void *data)
{
  args->setSpaceSeparated(true);

  args->setArgs(command);

  std::string id    = "shape";
  CPoint3D    delta = CPoint3D(0,0,0);

  uint num_args = args->getNumArgs();

  int error_code;

  for (uint i = 0; i < num_args; ++i) {
    std::string arg = args->getArg(i + 1, &error_code);

    if (arg[0] == '-') {
      if      (arg == "-id") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        id = args->getStringArg(i + 1, &error_code);
      }
      else if (arg == "-delta") {
        double *reals;
        uint    num_reals;

        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          delta = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else
        ClParserInst->error("Invalid option '%s'", arg.c_str());
    }
    else
      ClParserInst->error("Invalid argument '%s'", arg.c_str());
  }

  CCeilRayTrace *raytrace = static_cast<CCeilRayTrace *>(data);

  CRayShape *shape = raytrace->getRayTrace()->getShape(id);

  if (shape == NULL) {
    ClParserInst->error("Invalid shape '%s'", id.c_str());
    return;
  }

  shape->rotate(delta);
}

static void
CCeilRayTraceMoveLightCmd(ClLanguageCommand *command, ClLanguageArgs *args, void *data)
{
  args->setSpaceSeparated(true);

  args->setArgs(command);

  std::string id    = "light";
  CPoint3D    delta = CPoint3D(0,0,0);

  uint num_args = args->getNumArgs();

  int error_code;

  for (uint i = 0; i < num_args; ++i) {
    std::string arg = args->getArg(i + 1, &error_code);

    if (arg[0] == '-') {
      if      (arg == "-id") {
        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        id = args->getStringArg(i + 1, &error_code);
      }
      else if (arg == "-delta") {
        double *reals;
        uint    num_reals;

        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          delta = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else
        ClParserInst->error("Invalid option '%s'", arg.c_str());
    }
    else
      ClParserInst->error("Invalid argument '%s'", arg.c_str());
  }

  CCeilRayTrace *raytrace = static_cast<CCeilRayTrace *>(data);

  CRayTraceLight *light = raytrace->getRayTrace()->getLight(id);

  if (light == NULL) {
    ClParserInst->error("Invalid light '%s'", id.c_str());
    return;
  }

  CGeomPoint3D vertex = light->getPosition();

  light->setPosition(vertex.getModel() + delta);
}

static void
CCeilRayTraceMoveCameraCmd(ClLanguageCommand *command, ClLanguageArgs *args, void *data)
{
  args->setSpaceSeparated(true);

  args->setArgs(command);

  COptValT<CPoint3D> delta;
  COptValT<CPoint3D> position;

  uint num_args = args->getNumArgs();

  int error_code;

  for (uint i = 0; i < num_args; ++i) {
    std::string arg = args->getArg(i + 1, &error_code);

    if (arg[0] == '-') {
      if      (arg == "-position") {
        double *reals;
        uint    num_reals;

        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          position = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else if (arg == "-delta") {
        double *reals;
        uint    num_reals;

        ++i;

        if (i >= num_args) {
          ClParserInst->error("Missing value for '%s'", arg.c_str());
          break;
        }

        args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

        if (error_code == 0 && num_reals == 3)
          delta = CPoint3D(reals[0], reals[1], reals[2]);
      }
      else
        ClParserInst->error("Invalid option '%s'", arg.c_str());
    }
    else
      ClParserInst->error("Invalid argument '%s'", arg.c_str());
  }

  CCeilRayTrace *raytrace = static_cast<CCeilRayTrace *>(data);

  CRayTraceCamera *camera = raytrace->getRayTrace()->getCamera();

  if (camera) {
    if      (position.isValid())
      camera->setPosition(position.getValue());
    else if (delta.isValid())
      camera->setPosition(camera->getPosition() + delta.getValue());
  }
}

static void
CCeilRayTraceRenderCmd(ClLanguageCommand *, ClLanguageArgs *, void *data)
{
  CCeilRayTrace *raytrace = static_cast<CCeilRayTrace *>(data);

  raytrace->getRayTrace()->setChanged(true);
}

static void
CCeilRayTraceParseShapeArgs(ClLanguageArgs *args, CRayTraceShapeData &shape_data)
{
  uint num_args = args->getNumArgs();

  int error_code;

  for (uint i = 0; i < num_args; ++i) {
    std::string arg = args->getArg(i + 1, &error_code);

    if (arg[0] != '-')
      continue;

    if      (arg == "-id") {
      ++i;

      if (i >= num_args) {
        ClParserInst->error("Missing value for '%s'", arg.c_str());
        break;
      }

      shape_data.id = args->getStringArg(i + 1, &error_code);
    }
    else if (arg == "-color") {
      ++i;

      if (i >= num_args) {
        ClParserInst->error("Missing value for '%s'", arg.c_str());
        break;
      }

      shape_data.color = args->getStringArg(i + 1, &error_code);
    }
    else if (arg == "-translate") {
      double *reals;
      uint    num_reals;

      ++i;

      if (i >= num_args) {
        ClParserInst->error("Missing value for '%s'", arg.c_str());
        break;
      }

      args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

      if (error_code == 0 && num_reals == 3)
        shape_data.translate = CPoint3D(reals[0], reals[1], reals[2]);
    }
    else if (arg == "-scale") {
      double *reals;
      uint    num_reals;

      ++i;

      if (i >= num_args) {
        ClParserInst->error("Missing value for '%s'", arg.c_str());
        break;
      }

      args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

      if (error_code == 0 && num_reals == 3)
        shape_data.scale = CPoint3D(reals[0], reals[1], reals[2]);
    }
    else if (arg == "-rotate") {
      double *reals;
      uint    num_reals;

      ++i;

      if (i >= num_args) {
        ClParserInst->error("Missing value for '%s'", arg.c_str());
        break;
      }

      args->getRealArrayArg(i + 1, &reals, &num_reals, &error_code);

      if (error_code == 0 && num_reals == 3)
        shape_data.rotate = CPoint3D(reals[0], reals[1], reals[2]);
    }
    else if (arg == "-marble") {
      shape_data.marble = true;
    }
    else if (arg == "-noise") {
      shape_data.noise = true;
    }
    else if (arg == "-mandelbrot") {
      shape_data.mandelbrot = true;
    }
    else if (arg == "-image") {
      ++i;

      if (i >= num_args) {
        ClParserInst->error("Missing value for '%s'", arg.c_str());
        break;
      }

      shape_data.image = args->getStringArg(i + 1, &error_code);
    }
    else if (arg == "-reflect") {
      ++i;

      if (i >= num_args) {
        ClParserInst->error("Missing value for '%s'", arg.c_str());
        break;
      }

      shape_data.reflect = args->getRealArg(i + 1, &error_code);
    }
    else if (arg == "-refract") {
      ++i;

      if (i >= num_args) {
        ClParserInst->error("Missing value for '%s'", arg.c_str());
        break;
      }

      shape_data.refract = args->getRealArg(i + 1, &error_code);
    }
    else if (arg == "-refract_index") {
      ++i;

      if (i >= num_args) {
        ClParserInst->error("Missing value for '%s'", arg.c_str());
        break;
      }

      shape_data.refract_index = args->getRealArg(i + 1, &error_code);
    }
  }
}

static bool
CCeilRayTraceIsShapeArg(const std::string &arg, int *skip)
{
  if      (arg == "-id" ||
           arg == "-color" ||
           arg == "-translate" ||
           arg == "-scale" ||
           arg == "-rotate" ||
           arg == "-image" ||
           arg == "-reflect" ||
           arg == "-refract" ||
           arg == "-refract_index") {
    *skip = 1;
    return true;
  }
  else if (arg == "-marble" ||
           arg == "-noise" ||
           arg == "-mandelbrot") {
    *skip = 0;
    return true;
  }
  else
    return false;
}
