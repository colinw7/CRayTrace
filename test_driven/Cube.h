#ifndef Cube_H
#define Cube_H

#include <Object.h>

namespace RayTrace {

class Cube : public Object {
 public:
  Cube(double radius=1.0) :
   radius_(radius) {
  }

 protected:
  Intersections intersectInternal(const Ray &ray) const override;

  Vector pointNormalInternal(const Point &point) const override;

 private:
  using DoublePair = std::pair<double,double>;

  DoublePair checkAxis(double origin, double direction) const;

 private:
  double radius_ { 1.0 };
};

using CubeP = std::shared_ptr<Cube>;

}

#endif
