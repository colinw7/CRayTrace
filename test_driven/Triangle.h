#ifndef Triangle_H
#define Triangle_H

#include <Object.h>

namespace RayTrace {

class Triangle : public Object {
 public:
  Triangle(const Point &p1, const Point &p2, const Point &p3) :
   p1_(p1), p2_(p2), p3_(p3) {
    initDep();
  }

  const Point &p1() const { return p1_; }
  void setP1(const Point &p) { p1_ = p; initDep(); }

  const Point &p2() const { return p2_; }
  void setP2(const Point &p) { p2_ = p; initDep(); }

  const Point &p3() const { return p3_; }
  void setP3(const Point &p) { p3_ = p; initDep(); }

  const Vector &e1() const { return e1_; }
  const Vector &e2() const { return e2_; }

  const Vector &normal() const { return normal_; }

 protected:
  Intersections intersectInternal(const Ray &) const override {
    Intersections intersections;

    return intersections;
  }

  Vector pointNormalInternal(const Point & /*point*/) const override {
    return normal_;
  }

 private:
  void initDep() {
    e1_ = p2_ - p1_;
    e2_ = p3_ - p1_;

    normal_ = e2_.crossProduct(e1_).normalized();
  }

 private:
  Point  p1_;
  Point  p2_;
  Point  p3_;
  Vector e1_;
  Vector e2_;
  Vector normal_;
};

using TriangleP = std::shared_ptr<Triangle>;

}

#endif
