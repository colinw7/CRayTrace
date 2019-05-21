#ifndef Material_H
#define Material_H

#include <Color.h>
#include <Pattern.h>
#include <iostream>

namespace RayTrace {

class Material {
 public:
  Material() { }

  const Color &color() const { return color_; }
  void setColor(const Color &v) { color_ = v; }

  const PatternP &pattern() const { return pattern_; }
  void setPattern(const PatternP &p) { pattern_ = p; }

  double ambient() const { return ambient_; }
  void setAmbient(double r) { ambient_ = r; }

  double diffuse() const { return diffuse_; }
  void setDiffuse(double r) { diffuse_ = r; }

  double specular() const { return specular_; }
  void setSpecular(double r) { specular_ = r; }

  double shininess() const { return shininess_; }
  void setShininess(double r) { shininess_ = r; }

  double reflective() const { return reflective_; }
  void setReflective(double r) { reflective_ = r; }

  double transparency() const { return transparency_; }
  void setTransparency(double r) { transparency_ = r; }

  double refractiveIndex() const { return refractiveIndex_; }
  void setRefractiveIndex(double r) { refractiveIndex_ = r; }

  const std::string &imageName() const { return imageName_; }
  void setImageName(const std::string &v) { imageName_ = v; }

  //---

  // comparison
  int cmp(const Material &rhs) const {
    auto realCmp = [](double r1, double r2) {
      return std::abs(r1 - r2) < EPSILON();
    };

    if      (color_ < rhs.color_) return -1;
    else if (color_ > rhs.color_) return  1;

    if (! realCmp(ambient_, rhs.ambient_)) {
      if      (ambient_ < rhs.ambient_) return -1;
      else if (ambient_ > rhs.ambient_) return  1;
    }

    if (! realCmp(diffuse_, rhs.diffuse_)) {
      if      (diffuse_ < rhs.diffuse_) return -1;
      else if (diffuse_ > rhs.diffuse_) return  1;
    }

    if (! realCmp(specular_, rhs.specular_)) {
      if      (specular_  < rhs.specular_ ) return -1;
      else if (specular_  > rhs.specular_ ) return  1;
    }

    if (! realCmp(shininess_, rhs.shininess_)) {
      if      (shininess_ < rhs.shininess_) return -1;
      else if (shininess_ > rhs.shininess_) return  1;
    }

    return 0;
  }

  friend bool operator==(const Material &lhs, const Material &rhs) {
    return lhs.cmp(rhs) == 0;
  }

  friend bool operator!=(const Material &lhs, const Material &rhs) {
    return lhs.cmp(rhs) != 0;
  }

  friend bool operator< (const Material &lhs, const Material &rhs) {
    return lhs.cmp(rhs) <  0;
  }

  friend bool operator<=(const Material &lhs, const Material &rhs) {
    return lhs.cmp(rhs) <= 0;
  }

  friend bool operator> (const Material &lhs, const Material &rhs) {
    return lhs.cmp(rhs) >  0;
  }

  friend bool operator>=(const Material &lhs, const Material &rhs) {
    return lhs.cmp(rhs) >= 0;
  }

  //---

  void print(std::ostream &os) const {
    os << color_ << " " << ambient_ << " " << diffuse_ << " " << specular_ << " " << shininess_;
  }

  friend std::ostream &operator<<(std::ostream &os, const Material &m) {
    m.print(os);

    return os;
  }

 protected:
  Color       color_           { 1, 1, 1 };
  PatternP    pattern_;
  double      ambient_         { 0.1 };
  double      diffuse_         { 0.9 };
  double      specular_        { 0.9 };
  double      shininess_       { 200.0 };
  double      reflective_      { 0.0 };
  double      transparency_    { 0.0 };
  double      refractiveIndex_ { 1.0 };
  std::string imageName_;
};

}

#endif
