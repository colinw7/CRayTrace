#include <Camera.h>
#include <Ray.h>

namespace RayTrace {

Ray
Camera::
rayForPixel(double x, double y) const
{
  if (needsUpdate_)
    const_cast<Camera *>(this)->doUpdate();

  double xoffset = (x + 0.5)*pixelSize_;
  double yoffset = (y + 0.5)*pixelSize_;

  double worldx = halfWidth_  - xoffset;
  double worldy = halfHeight_ - yoffset;

  Point pixel  = transform_.inverted()*Point(worldx, worldy, -1);
  Point origin = transform_.inverted()*Point(0, 0, 0);

  Vector direction = (pixel - origin).normalize();

  return Ray(origin, direction);
}

//---

void
Camera::
doUpdate()
{
  needsUpdate_ = false;

  double halfView = std::tan(fov_/2.0);

  double aspect = 1.0*hsize_/vsize_;

  if (aspect >= 1.0) {
    halfWidth_  = halfView;
    halfHeight_ = halfView/aspect;
  }
  else {
    halfWidth_  = halfView*aspect;
    halfHeight_ = halfView;
  }

  pixelSize_ = halfWidth_*2/hsize_;
}

}
