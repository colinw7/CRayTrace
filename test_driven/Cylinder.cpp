#include <Cylinder.h>
#include <RayTrace.h>

namespace RayTrace {

Intersections
Cylinder::
intersectInternal(const Ray &ray) const
{
  Intersections intersections;

  double a = ray.direction().x()*ray.direction().x() + ray.direction().z()*ray.direction().z();

  if (std::abs(a) >= EPSILON()) {
    double b = 2*ray.origin().x()*ray.direction().x() +
               2*ray.origin().z()*ray.direction().z();

    double c = ray.origin().x()*ray.origin().x() + ray.origin().z()*ray.origin().z() - 1;

    double tmin, tmax;

    if (! solveQuadratic(a, b, c, tmin, tmax))
      return Intersections();

    double ymin = ray.origin().y() + tmin*ray.direction().y();

    if (ymin > minimum_ && ymin < maximum_)
      intersections.push_back(Intersection(tmin, this));

    double ymax = ray.origin().y() + tmax*ray.direction().y();

    if (ymax > minimum_ && ymax < maximum_)
      intersections.push_back(Intersection(tmax, this));
  }

  if (closed_)
    intersectCaps(ray, intersections);

  return intersections;
}

void
Cylinder::
intersectCaps(const Ray &ray, Intersections &intersections) const
{
  if (std::abs(ray.direction().y()) < EPSILON())
    return;

  double tmin = (minimum_ - ray.origin().y())/ray.direction().y();

  if (checkCap(ray, tmin))
    intersections.push_back(Intersection(tmin, this));

  double tmax = (maximum_ - ray.origin().y())/ray.direction().y();

  if (checkCap(ray, tmax))
    intersections.push_back(Intersection(tmax, this));
}

bool
Cylinder::
checkCap(const Ray &ray, double t) const
{
  double x = ray.origin().x() + t*ray.direction().x();
  double z = ray.origin().z() + t*ray.direction().z();

  return (x*x + z*z) <= 1.0;
}

Vector
Cylinder::
pointNormalInternal(const Point &point) const
{
  if (closed_) {
    double dist = point.x()*point.x() + point.z()*point.z();

    if (dist < 1) {
      if      (point.y() >= maximum_ - EPSILON())
        return Vector(0,  1, 0);
      else if (point.y() <= minimum_ + EPSILON())
        return Vector(0, -1, 0);
    }
  }

  return Vector(point.x(), 0, point.z());
}

}
