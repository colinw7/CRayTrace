#include <Cube.h>
#include <RayTrace.h>

#ifdef INFINITY
#undef INFINITY
#endif

namespace RayTrace {

Intersections
Cube::
intersectInternal(const Ray &ray) const
{
  DoublePair xtminmax = checkAxis(ray.origin().x(), ray.direction().x());
  DoublePair ytminmax = checkAxis(ray.origin().y(), ray.direction().y());
  DoublePair ztminmax = checkAxis(ray.origin().z(), ray.direction().z());

  double tmin = std::max(std::max(xtminmax.first , ytminmax.first ), ztminmax.first );
  double tmax = std::min(std::min(xtminmax.second, ytminmax.second), ztminmax.second);

  Intersections intersections;

  if (tmin <= tmax) {
    intersections.push_back(Intersection(tmin, this));
    intersections.push_back(Intersection(tmax, this));
  }

  return intersections;
}

Vector
Cube::
pointNormalInternal(const Point &point) const
{
  double maxc = std::max(std::max(std::abs(point.x()), std::abs(point.y())), std::abs(point.z()));

  if      (maxc == abs(point.x()))
    return Vector(point.x(), 0, 0);
  else if (maxc == abs(point.y()))
    return Vector(0, point.y(), 0);
  else
    return Vector(0, 0, point.z());
}

Cube::DoublePair
Cube::
checkAxis(double origin, double direction) const
{
  double tmin_numerator = (-1 - origin);
  double tmax_numerator = ( 1 - origin);

  double tmin, tmax;

  if (std::abs(direction) >= EPSILON()) {
    tmin = tmin_numerator/direction;
    tmax = tmax_numerator/direction;
  }
  else {
    tmin = tmin_numerator*INFINITY();
    tmax = tmax_numerator*INFINITY();
  }

  if (tmin > tmax)
    std::swap(tmin, tmax);

  return DoublePair(tmin, tmax);
}

}
