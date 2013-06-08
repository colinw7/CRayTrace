#include <CRayTriangle.h>

bool
CRayTriangle::
hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const
{
  double t;

  if (! intersect(ray, &t))
    return false;

  if (t < tmin || t > tmax)
    return false;

  if (hit_data != NULL)
    hit_data->t = t;

  return true;
}
