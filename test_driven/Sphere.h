#ifndef Sphere_H
#define Sphere_H

#include <Object.h>

namespace RayTrace {

class Sphere : public Object {
 public:
  Sphere(double radius=1.0) :
   radius_(radius) {
  }

 protected:
  Intersections intersectInternal(const Ray &ray) const override;

  Vector pointNormalInternal(const Point &point) const override;

 private:
  bool solveQuadratic(double a, double b, double c, double &r1, double &r2) const;

 private:
  double radius_ { 1.0 };
};

using SphereP = std::shared_ptr<Sphere>;

//---

class GlassSphere : public Sphere {
 public:
  GlassSphere();
};

using GlassSphereP = std::shared_ptr<GlassSphere>;

}

#endif
