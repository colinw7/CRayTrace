#include "std_c++.h"
#include "CTclApp/CTclApp.h"
#include "CTclApp/CTclAppCanvas.h"
#include "CTclCanvas/CTclCanvas.h"
#include "CTclCanvasPixelRenderer/CTclCanvasPixelRenderer.h"
#include "CRayTracer/CRayTracer.h"
#include "CRayTraceRenderer/CRayTraceRenderer.h"
#include "CTclRayTracer.h"

#include "CTclRayTracer.k"

class CTclRayTracerRenderer : public CRayTracerRenderer {
 public:
  CTclRayTracerRenderer(CTclCanvasPixelRenderer *renderer) :
   renderer_(renderer) {
  }

  void setForeground(const CRGBA &rgba) { renderer_->setForeground(rgba); }

  void drawPoint(const CIPoint2D &p) { renderer_->drawPoint(p); }

 private:
  CTclCanvasPixelRenderer *renderer_;
};

int
main(int argc, char **argv)
{
  CTclRayTracerApp app(argc, argv);
}

CTclRayTracerApp::
CTclRayTracerApp(int argc, char **argv) :
 CTclApp(argc, argv), debug_(false), cmd_(NULL)
{
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strcmp(&argv[i][1], "debug") == 0)
        debug_ = true;
      else
        cerr << "Invalid option: " << argv[i] << endl;
    }
    else
      cerr << "Invalid argument: " << argv[i] << endl;
  }

  init();
}

CTclRayTracerApp::
~CTclRayTracerApp()
{
  delete cmd_;
}

void
CTclRayTracerApp::
addCommands()
{
  cmd_ = new CTclRayTracerCanvasCmd(this);
}

string
CTclRayTracerApp::
getTclStr()
{
  return CTclRayTracer_TK;
}

CTclRayTracerCanvasCmd::
CTclRayTracerCanvasCmd(CTclRayTracerApp *app) :
 CTclAppCanvasCmd(app), canvas_(NULL)
{
  init();
}

CTclRayTracerCanvasCmd::
~CTclRayTracerCanvasCmd()
{
  delete canvas_;
}

CTclAppCanvas *
CTclRayTracerCanvasCmd::
createInstance(CTclApp *app)
{
  CTclRayTracerApp *app1 = dynamic_cast<CTclRayTracerApp *>(app);

  canvas_ = new CTclRayTracerCanvas(app1);

  return (CTclAppCanvas *) canvas_->getCanvasWidget();
}

void
CTclRayTracerCanvasCmd::
initInstance(CTclRayTracerApp *)
{
}

CTclRayTracerCanvas::
CTclRayTracerCanvas(CTclRayTracerApp *app) :
 CTclCanvas(app)
{
  renderer_   = new CTclCanvasPixelRenderer(this);
  rrenderer_  = new CTclRayTracerRenderer(renderer_);
  ray_tracer_ = new CRayTracer();

  ray_tracer_->setRenderer(rrenderer_);
}

CTclRayTracerCanvas::
~CTclRayTracerCanvas()
{
  delete renderer_;
  delete ray_tracer_;
}

bool
CTclRayTracerCanvas::
instanceCommand(int argc, const char **argv)
{
  if (strcmp(argv[0], "loadFile") == 0) {
    if (argc != 2) {
      cerr << "Invalid arguments for loadFile" << endl;
      return false;
    }

    ray_tracer_->addFile(argv[1]);

    return true;
  }

  return false;
}

bool
CTclRayTracerCanvas::
instanceConfigure(int, const char **)
{
  return false;
}

void
CTclRayTracerCanvas::
draw()
{
  ray_tracer_->render(100, 100);
}
