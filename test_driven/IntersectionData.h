#ifndef IntersectionData_H
#define IntersectionData_H

#include <Types.h>
#include <Intersection.h>
#include <Point.h>
#include <Vector.h>

namespace RayTrace {

class IntersectionData {
 public:
  IntersectionData(const Intersection &intersection, const Ray &ray,
                   const Intersections &intersections=Intersections());

  double t() const { return t_; }

  const Object *object() const { return object_; }

  const Point &point() const { return point_; }

  const Point &overPoint() const { return overPoint_; }

  const Point &underPoint() const { return underPoint_; }

  const Vector &eye() const { return eye_; }

  const Vector &normal() const { return normal_; }

  const Vector &reflect() const { return reflect_; }

  double n1() const { return n1_; }
  double n2() const { return n2_; }

  bool inShadow() const { return inShadow_; }

  bool inside() const { return inside_; }

  static double EPSILON() { return 1E-6; }

 private:
  double        t_        { 0.0 };
  const Object *object_   { nullptr };
  Point         point_;
  Point         overPoint_;
  Point         underPoint_;
  Vector        eye_;
  Vector        normal_;
  Vector        reflect_;
  double        n1_       { 0.0 };
  double        n2_       { 0.0 };
  bool          inShadow_ { false };
  bool          inside_   { false };
};

}

#endif
