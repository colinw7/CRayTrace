#include <CRaySphere.h>
#include <CImageLib.h>

bool
CRaySphere::
hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const
{
  double t1, t2;

  if (! intersect(ray, &t1, &t2))
    return false;

  if (t1 < tmin)
    t1 = t2;

  if (t1 < tmin || t1 > tmax)
    return false;

  if (hit_data != NULL)
    hit_data->t = t1;

  return true;
}
