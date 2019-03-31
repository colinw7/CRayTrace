#ifndef Camera_H
#define Camera_H

#include <Types.h>
#include <Matrix4D.h>

namespace RayTrace {

class Camera {
 public:
  Camera() { transform_.setIdentity(); }

  Camera(int hsize, int vsize, double fov) :
   hsize_(hsize), vsize_(vsize), fov_(fov) {
    transform_.setIdentity();

    needsUpdate_ = true;
  }

  int hsize() const { return hsize_; }
  int vsize() const { return vsize_; }

  double fov() const { return fov_; }

  const Matrix4D &transform() const { return transform_; }
  void setTransform(const Matrix4D &t) { transform_ = t; }

  double pixelSize() const {
    if (needsUpdate_)
      const_cast<Camera *>(this)->doUpdate();

    return pixelSize_;
  }

  Ray rayForPixel(double x, double y) const;

 private:
  void doUpdate();

 protected:
  int      hsize_       { 160 };
  int      vsize_       { 120 };
  double   fov_         { M_PI/2.0 };
  Matrix4D transform_;
  bool     needsUpdate_ { true };
  double   halfWidth_   { 1.0 };
  double   halfHeight_  { 1.0 };
  double   pixelSize_   { 1.0 };
};

}

#endif
