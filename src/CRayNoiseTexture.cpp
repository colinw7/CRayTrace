#include <CRayNoiseTexture.h>

CRGBA
CRayNoiseTexture::
value(const CPoint3D &p) const
{
  double t = (1 + solid_noise_.noise(p*scale_))/2;

  return t*c0_ + (1 - t)*c1_;
}
