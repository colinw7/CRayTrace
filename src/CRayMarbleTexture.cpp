#include <CRayMarbleTexture.h>

CRGBA
CRayMarbleTexture::
value(const CPoint3D &p) const
{
  double t1 = scale_*solid_noise_.turbulence(freq_*p, octaves_);

  double t = 2*fabs(sin(freq_*p.getX() + t1));

  if (t < 1)
    return t*c1_ + (1 - t)*c2_;
  else {
    t -= 1;

    return t*c0_ + (1 - t)*c1_;
  }
}
