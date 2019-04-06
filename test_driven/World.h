#ifndef World_H
#define World_H

#include <Types.h>
#include <Intersection.h>
#include <IntersectionData.h>
#include <vector>

namespace RayTrace {

class World {
 public:
  using Objects = std::vector<ObjectP>;
  using Lights  = std::vector<LightP>;

 public:
  World() { }

  virtual ~World() { }

  void addObject(const ObjectP &object) { objects_.push_back(object); }

  const Objects &objects() const { return objects_; }

  void addLight(const LightP &light) { lights_.push_back(light); }

  void setLight(int i, const LightP &light) { lights_[i] = light; }

  const Lights &lights() const { return lights_; }

  Intersections intersect(const Ray &ray) const;

  Color shadeHit(const IntersectionData &intersectionData, int remaining=INIT_REMAINING()) const;

  Color colorAt(const Ray &ray, int remaining=4) const;

  bool isShadowed(const Point &point) const;

  Color reflectedColor(const IntersectionData &intersectionData,
                       int remaining=INIT_REMAINING()) const;

  Color refractedColor(const IntersectionData &intersectionData,
                       int remaining=INIT_REMAINING()) const;

  static double EPSILON() { return 1E-6; }

  static int INIT_REMAINING() { return 4; }

 protected:
  Objects objects_;
  Lights  lights_;
};

}

//---

namespace RayTrace {

class DefaultWorld : public World {
 public:
  DefaultWorld();
};

}

#endif
