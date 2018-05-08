#include <std_c++.h>
#include <CRayTrace/CRayTrace.h>
#include <CRayTrace/CRayTraceLight.h>
#include <CRayTrace/CRayTraceCamera.h>
#include <CXLib/CXMachine.h>
#include <CXLib/CXWindow.h>
#include <CTimer/CTimer.h>
#include <CRayShape/CRayShape.h>
#include <CGeometry3D/CGeomLight3D.h>
#include <CGeometry3D/CGeomVertex3D.h>

class CXRayTrace;

class CXRayTraceTimer : public CTimer {
 private:
  CXRayTrace *raytrace_;

 public:
  CXRayTraceTimer(CXRayTrace *raytrace);

  void timeOut();
};

class CXRayTrace : public CXWindow, public CRayTrace {
 private:
  CXRayTraceTimer *timer_;
  bool             move_shape_;
  bool             spin_shape_;
  bool             move_light_;
  bool             move_camera_;
  string           shape_name_;

 public:
  CXRayTrace(int w, int h);

  ACCESSOR(MoveShape , bool  , move_shape )
  ACCESSOR(SpinShape , bool  , spin_shape )
  ACCESSOR(MoveLight , bool  , move_light )
  ACCESSOR(MoveCamera, bool  , move_camera)
  ACCESSOR(ShapeName , string, shape_name )

  void addFile(const string &fileName);

  void setNumSamples(int num_samples);

  void step();
  void draw();

  bool exposeEvent();
  bool resizeEvent();

  void clear(const CRGBA &bg);

  void drawPoint(int x, int y, const CRGBA &rgb);
};

//----------

int
main(int argc, char **argv)
{
  uint   num_samples = 0;
  bool   trace       = false;
  bool   move_shape  = false;
  bool   spin_shape  = false;
  bool   move_light  = false;
  bool   move_camera = false;
  string shape_name  = "sphere";

  vector<string> filenames;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (strcmp(&argv[i][1], "sample") == 0)
        num_samples = 16;
      else if (strcmp(&argv[i][1], "trace") == 0)
        trace = true;
      else if (strcmp(&argv[i][1], "move_shape") == 0)
        move_shape  = true;
      else if (strcmp(&argv[i][1], "spin_shape") == 0)
        spin_shape  = true;
      else if (strcmp(&argv[i][1], "move_light") == 0)
        move_light  = true;
      else if (strcmp(&argv[i][1], "move_camera") == 0)
        move_camera = true;
      else if (strcmp(&argv[i][1], "shape_name") == 0)
        shape_name = argv[++i];
      else
        cerr << "Unknown option " << argv[i] << endl;
    }
    else
      filenames.push_back(argv[i]);
  }

  CXRayTrace window(500, 500);

  window.setMoveShape (move_shape );
  window.setSpinShape (spin_shape );
  window.setMoveLight (move_light );
  window.setMoveCamera(move_camera);
  window.setShapeName (shape_name);

  window.selectAllEvents();

  vector<string>::const_iterator p1 = filenames.begin();
  vector<string>::const_iterator p2 = filenames.end  ();

  for ( ; p1 != p2; ++p1)
    window.addFile(*p1);

  window.setNumSamples(num_samples);

  window.map();

  CXMachineInst->mainLoop();

  exit(0);
}

//--------------

CXRayTrace::
CXRayTrace(int w, int h) :
 CXWindow(w, h), CRayTrace()
{
  timer_ = new CXRayTraceTimer(this);
}

void
CXRayTrace::
addFile(const string &fileName)
{
  CRayTrace::addFile(fileName);

  resize(CRayTrace::getWidth(), CRayTrace::getHeight());
}

void
CXRayTrace::
setNumSamples(int num_samples)
{
  CRayTrace::setNumSamples(num_samples);
}

void
CXRayTrace::
step()
{
  if (move_shape_) {
    CRayShape *shape = CRayTrace::getShape(shape_name_);

    if (shape)
      shape->setPosition(shape->getPosition() + CPoint3D(0.01,0,0));
  }

  if (spin_shape_) {
    CRayShape *shape = CRayTrace::getShape(shape_name_);

    if (shape)
      shape->rotate(CPoint3D(0.02, 0.02, 0.02));
  }

  if (move_light_) {
    CRayTraceLight *light = CRayTrace::getLight("light");

    if (light) {
      CGeomPoint3D vertex = light->getPosition();

      light->setPosition(vertex.getModel() + CPoint3D(0.05,0.05,0));
    }
  }

  if (move_camera_) {
    CRayTraceCamera *camera = CRayTrace::getCamera();

    if (camera)
      camera->setPosition(camera->getPosition() + CPoint3D(0.05,0,0));
  }

  draw();
}

bool
CXRayTrace::
exposeEvent()
{
  //copyDoubleBuffer();

  return true;
}

bool
CXRayTrace::
resizeEvent()
{
  draw();

  return true;
}

void
CXRayTrace::
draw()
{
  startDoubleBuffer();

  CRayTrace::render();

  endDoubleBuffer();
}

void
CXRayTrace::
clear(const CRGBA &bg)
{
  CXWindow::setBackground(bg);

  CXWindow::clear();
}

void
CXRayTrace::
drawPoint(int x, int y, const CRGBA &fg)
{
  CXWindow::setForeground(fg);

  CXWindow::drawPoint(x, y);
}

//--------------

CXRayTraceTimer::
CXRayTraceTimer(CXRayTrace *raytrace) :
 CTimer(1000, CTIMER_FLAGS_REPEAT), raytrace_(raytrace)
{
}

void
CXRayTraceTimer::
timeOut()
{
  raytrace_->step();
}
