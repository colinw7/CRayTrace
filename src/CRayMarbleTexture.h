#ifndef CRAY_MARBLE_TEXTURE_H
#define CRAY_MARBLE_TEXTURE_H

#include <CRayTexture.h>
#include <CSolidNoise.h>

class CRayMarbleTexture : public CRayTexture {
 public:
  CRayMarbleTexture(double stripes_per_unit, double scale = 5.0, int octaves = 8) :
   scale_(scale), octaves_(octaves) {
    freq_ = M_PI*stripes_per_unit;

    c0_ = CRGBA(0.8 ,0.8 ,0.8 );
    c1_ = CRGBA(0.4 ,0.2 ,0.1 );
    c2_ = CRGBA(0.06,0.04,0.02);
  }

  CRayMarbleTexture(const CRGBA &c0, const CRGBA &c1, const CRGBA &c2,
                    double stripes_per_unit, double scale = 3.0, int octaves = 8) :
   scale_(scale), octaves_(octaves), c0_(c0), c1_(c1), c2_(c2) {
    freq_ = M_PI*stripes_per_unit;
  }

  virtual ~CRayMarbleTexture() { }

  virtual CRGBA value(const CPoint3D &p) const;

 private:
  double        freq_ { 0.0 };
  double        scale_ { 5.0 };
  int           octaves_ { 8 };
  CRGBA         c0_, c1_, c2_;
  CSolidNoise3D solid_noise_;
};

#endif
