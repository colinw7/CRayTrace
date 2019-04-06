#include <Cone.h>
#include <RayTrace.h>

namespace RayTrace {

Intersections
Cone::
intersectInternal(const Ray &ray) const
{
  Intersections intersections;

  double a = ray.direction().x()*ray.direction().x() -
             ray.direction().y()*ray.direction().y() +
             ray.direction().z()*ray.direction().z();

  double b = 2*ray.origin().x()*ray.direction().x() -
             2*ray.origin().y()*ray.direction().y() +
             2*ray.origin().z()*ray.direction().z();

  double c = ray.origin().x()*ray.origin().x() -
             ray.origin().y()*ray.origin().y() +
             ray.origin().z()*ray.origin().z();

  if (std::abs(a) < EPSILON()) {
    if (std::abs(b) >= EPSILON()) {
      double t = -c/(2.0*b);

      double y = ray.origin().y() + t*ray.direction().y();

      if (y > minimum_ && y < maximum_)
        intersections.push_back(Intersection(t, this));
    }
  }
  else {
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
Cone::
intersectCaps(const Ray &ray, Intersections &intersections) const
{
  if (std::abs(ray.direction().y()) < EPSILON())
    return;

  double tmin = (minimum_ - ray.origin().y())/ray.direction().y();

  if (checkCap(ray, tmin, minimum_))
    intersections.push_back(Intersection(tmin, this));

  double tmax = (maximum_ - ray.origin().y())/ray.direction().y();

  if (checkCap(ray, tmax, maximum_))
    intersections.push_back(Intersection(tmax, this));
}

bool
Cone::
checkCap(const Ray &ray, double t, double r) const
{
  double x = ray.origin().x() + t*ray.direction().x();
  double z = ray.origin().z() + t*ray.direction().z();

  return (x*x + z*z) <= r*r;
}

Vector
Cone::
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

  double y = sqrt(point.x()*point.x() + point.z()*point.z());

  if (point.y() > 0)
    y = -y;

  return Vector(point.x(), y, point.z());
}

}
