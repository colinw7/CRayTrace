#ifndef CRAYTRACE_RENDERER_H
#define CRAYTRACE_RENDERER_H

#include <CRayTrace.h>

class CPixelRenderer;

class CRayTracePixelRenderer : public CRayTraceRenderer {
 protected:
  CPixelRenderer *renderer_;

 public:
  CRayTracePixelRenderer(CPixelRenderer *renderer=NULL);

  virtual ~CRayTracePixelRenderer() { }

  void setRenderer(CPixelRenderer *renderer) {
    renderer_ = renderer;
  }

  CPixelRenderer *getRenderer() const { return renderer_; }

  void render();

  void setSize(uint w, uint h);

  void clear(const CRGBA &bg);

  void drawPoint(int x, int y, const CRGBA &rgb);
};

#endif
