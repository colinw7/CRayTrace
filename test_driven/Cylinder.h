#ifndef Cylinder_H
#define Cylinder_H

#include <Object.h>
#include <RayTrace.h>

namespace RayTrace {

class Cylinder : public Object {
 public:
  Cylinder() { }

  double minimum() const { return minimum_; }
  void setMinimum(double r) { minimum_ = r; }

  double maximum() const { return maximum_; }
  void setMaximum(double r) { maximum_ = r; }

  bool isClosed() const { return closed_; }
  void setClosed(bool b) { closed_ = b; }

 protected:
  Intersections intersectInternal(const Ray &ray) const override;

  Vector pointNormalInternal(const Point &point) const override;

 private:
  void intersectCaps(const Ray &ray, Intersections &intersections) const;

  bool checkCap(const Ray &ray, double t) const;

 private:
  double minimum_ { -RayTrace::INFINITY() };
  double maximum_ {  RayTrace::INFINITY() };
  bool   closed_  { false };
};

using CylinderP = std::shared_ptr<Cylinder>;

}

#endif
