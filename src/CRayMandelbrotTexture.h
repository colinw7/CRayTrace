#ifndef CRAY_MANDELBROT_TEXTURE_H
#define CRAY_MANDELBROT_TEXTURE_H

#include <CRayTexture.h>
#include <CMandelbrot.h>
#include <CColorRange.h>

class CRayMandelbrotTexture : public CRayTexture {
 public:
  CRayMandelbrotTexture();

  virtual ~CRayMandelbrotTexture() { }

  virtual CRGBA value(const CVector2D &uv) const;

  virtual bool isPointTexture() const { return false; }

 private:
  CMandelbrot mandelbrot_;
  CColorRange colors_;
  double      xmin_ { 0.0 }, ymin_ { 0.0 }, xmax_ { 0.0 }, ymax_ { 0.0 };
};

#endif
