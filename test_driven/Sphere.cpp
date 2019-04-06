#include <Sphere.h>
#include <RayTrace.h>

namespace RayTrace {

Intersections
Sphere::
intersectInternal(const Ray &ray) const
{
  // solve
  //  x^2 + y^2 + z^2 = r^2 at line (ray.o + t*d)
  //
  // where o = ray.origin, d = ray.direction
  //
  // i.e.
  //  (ox + t*dx)^2 + (oy + t*dy)^2 + (oz + t*dz)^2 = r^2
  //
  // solving for t
  //
  //  ox^2 + 2*t*dx*ox + t^2*dx^2 +
  //  oy^2 + 2*t*dy*oy + t^2*dy^2 +
  //  oz^2 + 2*t*dz*oz + t^2*dz^2 = r^2
  //
  // grouping by t
  //
  //  (dx^2 + dy^2 + dz^2)*t^2 + 2*(dx*ox + dy*oy + dz*oz)*t +
  //  (ox^2 + oy^2 + oz^2 - r^2) = 0
  //
  // solve quadratic
  //
  //  at^2 + bt + c = 0
  //
  // where
  //
  //  a = dx^2 + dy^2 + dz^2
  //  b = 2*(dx*ox + dy*oy + dz*oz)
  //  c = ox^2 + oy^2 + oz^2 - r^2

  Vector ro = ray.origin() - Point(0, 0, 0);

  const Vector &rd = ray.direction();

  double a = rd.dotProduct(rd);
  double b = 2*rd.dotProduct(ro);
  double c = ro.dotProduct(ro) - 1.0;

  double tmin, tmax;

  if (! solveQuadratic(a, b, c, tmin, tmax))
    return Intersections();

  Intersections intersections;

  intersections.push_back(Intersection(tmin, this));
  intersections.push_back(Intersection(tmax, this));

  return intersections;
}

Vector
Sphere::
pointNormalInternal(const Point &point) const
{
  return point - Point(0, 0, 0);
}

//---

GlassSphere::
GlassSphere()
{
  material().setTransparency(1.0);
  material().setRefractiveIndex(1.5);
}

}
