#ifndef CRAY_MANDELBROT_TEXTURE_H
#define CRAY_MANDELBROT_TEXTURE_H

#include <CRayTexture.h>
#include <CMandelbrot.h>
#include <CColorRange.h>

class CRayMandelbrotTexture : public CRayTexture {
 private:
  CMandelbrot mandelbrot_;
  CColorRange colors_;
  double      xmin_, ymin_, xmax_, ymax_;

 public:
  CRayMandelbrotTexture();

  virtual ~CRayMandelbrotTexture() { }

  virtual CRGBA value(const CVector2D &uv) const;

  virtual bool isPointTexture() const { return false; }
};

#endif
