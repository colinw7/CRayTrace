#ifndef CRAY_NOISE_TEXTURE_H
#define CRAY_NOISE_TEXTURE_H

#include <CRayTexture.h>
#include <CSolidNoise.h>

class CRayNoiseTexture : public CRayTexture {
 public:
  CRayNoiseTexture(double scale = 1.0) :
   scale_(scale), c0_(0.8,0.0,0.0), c1_(0.0,0.0,0.8) {
  }

  CRayNoiseTexture(const CRGBA &c0, const CRGBA &c1, double scale = 1.0) :
   scale_(scale), c0_(c0), c1_(c1) {
  }

  virtual ~CRayNoiseTexture() { }

  virtual CRGBA value(const CPoint3D &p) const;

 private:
  double        scale_ { 1.0 };
  CRGBA         c0_;
  CRGBA         c1_;
  CSolidNoise3D solid_noise_;
};

#endif
