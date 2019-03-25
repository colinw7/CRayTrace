#ifndef Object_H
#define Object_H

#include <Matrix4D.h>
#include <Intersection.h>

namespace RayTrace {

class Object {
 public:
  Object() { transform_ = Matrix4D::identity(); }

  virtual ~Object() { }

  const Matrix4D &transform() const { return transform_; }
  void setTransform(const Matrix4D &v) { transform_ = v; }

  void transform(const Matrix4D &t) {
    transform_ *= t;
  }

 protected:
  Matrix4D transform_;
};

}

#endif
