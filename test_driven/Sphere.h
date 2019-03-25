#ifndef Sphere_H
#define Sphere_H

#include <Object.h>
#include <Ray.h>

namespace RayTrace {

class Sphere : public Object {
 public:
  Sphere(double radius=1.0) :
   radius_(radius) {
  }

  Intersections intersect(const Ray &ray) const {
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

    Ray ray1 = ray.transform(transform().inverted());

    Vector ro = ray1.origin() - Point(0, 0, 0);

    const Vector &rd = ray1.direction();

    double a = rd.dotProduct(rd);
    double b = 2*rd.dotProduct(ro);
    double c = ro.dotProduct(ro) - radius_*radius_;

    double tmin, tmax;

    if (! solveQuadratic(a, b, c, tmin, tmax))
      return Intersections();

    Intersections intersections;

    intersections.push_back(Intersection(tmin, this));
    intersections.push_back(Intersection(tmax, this));

    return intersections;
  }

 private:
  bool solveQuadratic(double a, double b, double c, double &r1, double &r2) const {
    if (a == 0.0) return false;

    double b2_4ac = b*b - 4.0*a*c;

    if (b2_4ac < 0) return false;

    double sqrt_b2_4ac = std::sqrt(b2_4ac);

    double q;

    if (b < 0.0)
      q = -0.5*(b - sqrt_b2_4ac);
    else
      q = -0.5*(b + sqrt_b2_4ac);

    r1 = q/a;
    r2 = c/q;

    if (r1 > r2) std::swap(r1, r2);

    return true;
  }

 private:
  double radius_ { 1.0 };
};

}

#endif
