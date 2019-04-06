#ifndef Sphere_H
#define Sphere_H

#include <Object.h>

namespace RayTrace {

class Sphere : public Object {
 public:
  Sphere() { }

 protected:
  Intersections intersectInternal(const Ray &ray) const override;

  Vector pointNormalInternal(const Point &point) const override;
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
