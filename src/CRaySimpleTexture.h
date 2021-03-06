#ifndef CRAY_SIMPLE_TEXTURE_H
#define CRAY_SIMPLE_TEXTURE_H

#include <CRayTexture.h>

class CRaySimpleTexture : public CRayTexture {
 public:
  CRaySimpleTexture(const CRGBA &color) :
   color_(color) {
  }

  virtual ~CRaySimpleTexture() { }

  virtual CRGBA value(const CPoint3D &) const { return color_; }

 private:
  CRGBA color_;
};

#endif
