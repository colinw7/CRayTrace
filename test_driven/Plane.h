#ifndef Plane_H
#define Plane_H

#include <Object.h>

namespace RayTrace {

class Plane : public Object {
 public:
  Plane() { }

 protected:
  Intersections intersectInternal(const Ray &ray) const override {
    Intersections intersections;

    if (std::abs(ray.direction().y()) < EPSILON())
      return intersections;

    double t = -ray.origin().y()/ray.direction().y();

    intersections.push_back(Intersection(t, this));

    return intersections;
  }

  Vector pointNormalInternal(const Point & /*point*/) const override {
    return Vector(0, 1, 0);
  }

 private:
  static double EPSILON() { return 1E-6; }

 private:
  double radius_ { 1.0 };
};

using PlaneP = std::shared_ptr<Plane>;

}

#endif
