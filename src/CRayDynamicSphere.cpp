#include <CRayDynamicSphere.h>

bool
CRayDynamicSphere::
hitAt(const CRay &ray, double tmin, double tmax, double t,
      CRayHitData *hit_data) const
{
  CRayDynamicSphere *th = const_cast<CRayDynamicSphere *>(this);

  th->setCenter(getCenterAt(t));

  return CRaySphere::hit(ray, tmin, tmax, hit_data);
}

CPoint3D
CRayDynamicSphere::
getCenterAt(double t) const
{
  double t1 = t*max_t_ + (1 - t)*min_t_;

  return getCenter() + CVector3D(t1, t1, t1);
}
