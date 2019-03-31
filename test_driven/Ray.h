#ifndef Ray_H
#define Ray_H

#include <Point.h>
#include <Vector.h>
#include <Matrix4D.h>

namespace RayTrace {

class Ray {
 public:
  Ray() { }

  Ray(const Point &origin, const Vector &direction) :
   origin_(origin), direction_(direction) {
  }

  const Point &origin() const { return origin_; }

  const Vector &direction() const { return direction_; }

  Point position(double t) const {
    return origin_ + t*direction_;
  }

  Ray transform(const Matrix4D &m) const {
    Point  origin1    = m*origin   ();
    Vector direction1 = m*direction();

    return Ray(origin1, direction1);
  }

  void print(std::ostream &os) const {
    os << origin_ << " : " << direction_;
  }

 private:
  Point  origin_    { 0, 0, 0 };
  Vector direction_ { 0, 0, 1 };
};

}

#endif
