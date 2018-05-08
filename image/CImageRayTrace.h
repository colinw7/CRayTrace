#ifndef CIMAGE_RAYTRACE_H
#define CIMAGE_RAYTRACE_H

#include <CRayTrace.h>
#include <CImageLib.h>

class CImageRayTraceRenderer : public CRayTraceRenderer {
 public:
  CImageRayTraceRenderer();
 ~CImageRayTraceRenderer();

  void setSize(uint w, uint h);

  void begin();

  void clear(const CRGBA &bg);

  void drawPoint(int x, int y, const CRGBA &fg);

  void writeImage(const std::string &name="raytrace.png");

  CImagePtr getImage() const;

 private:
  CImagePtr image_;
};

#endif
