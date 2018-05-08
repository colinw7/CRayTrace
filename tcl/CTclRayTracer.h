class CTclRayTracerCanvasCmd;
class CTclRayTracerCanvas;
class CTclRayTracer;
class CTclCanvasPixelRenderer;
class CTclRayTracerRenderer;
class CRayTracer;

class CTclRayTracerApp : public CTclApp {
 private:
  bool                    debug_;
  CTclRayTracerCanvasCmd *cmd_;
  vector<string>          files_;

 public:
  CTclRayTracerApp(int argc, char **argv);
 ~CTclRayTracerApp();

  bool                  getDebug() const { return debug_; }
  const vector<string> &getFiles() const { return files_; }

 protected:
  void addCommands();

  string getTclStr();
};

class CTclRayTracerCanvasCmd : public CTclAppCanvasCmd {
 private:
  CTclRayTracerCanvas *canvas_;

 public:
  CTclRayTracerCanvasCmd(CTclRayTracerApp *app);
 ~CTclRayTracerCanvasCmd();

  string getCommandName () const { return "CTclRayTracerCanvas"; }
  string getCommandClass() const { return "CTclRayTracerCanvas"; }

  CTclAppCanvas *createInstance(CTclApp *app);

  void initInstance(CTclRayTracerApp *app);
};

class CTclRayTracerCanvas : public CTclCanvas {
 private:
  CTclCanvasPixelRenderer *renderer_;
  CTclRayTracerRenderer   *rrenderer_;
  CRayTracer              *ray_tracer_;

 public:
  CTclRayTracerCanvas(CTclRayTracerApp *app);
 ~CTclRayTracerCanvas();

  bool instanceCommand  (int argc, const char **argv);
  bool instanceConfigure(int argc, const char **argv);

  void draw();
};
