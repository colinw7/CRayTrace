#ifndef PointLight_H
#define PointLight_H

#include <Light.h>

namespace RayTrace {

class PointLight : public Light {
 public:
  PointLight() { }

  PointLight(const Point &position, const Color &intensity) :
   position_(position), intensity_(intensity) {
  }

  const Point &position() const { return position_; }
  void setPosition(const Point &p) { position_ = p; }

  const Color &intensity() const { return intensity_; }
  void setIntensity(const Color &c) { intensity_ = c; }

 protected:
  Point position_  { 0, 0, 0 };
  Color intensity_ { 1, 1, 1 };
};

using PointLightP = std::shared_ptr<PointLight>;

}

#endif
