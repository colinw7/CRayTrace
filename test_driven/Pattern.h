#ifndef Pattern_H
#define Pattern_H

#include <Types.h>
#include <Color.h>
#include <Matrix4D.h>

namespace RayTrace {

class Pattern {
 public:
  Pattern() { transform_ = Matrix4D::identity(); }

  virtual ~Pattern() { }

  const Matrix4D &transform() const { return transform_; }
  void setTransform(const Matrix4D &v) { transform_ = v; }

  virtual Color pointColor(const Point &point) const = 0;

  Color objectPointColor(const Object *object, const Point &point) const;

 protected:
  Matrix4D transform_;
};

//---

class TestPattern : public Pattern {
 public:
  TestPattern() { }

  Color pointColor(const Point &point) const override {
    return Color(point.x(), point.y(), point.z());
  }
};

using TestPatternP = std::shared_ptr<TestPattern>;

//---

class StripedPattern : public Pattern {
 public:
  StripedPattern(const Color &color1, const Color &color2) :
   color1_(color1), color2_(color2) {
  }

  const Color &color1() const { return color1_; }
  const Color &color2() const { return color2_; }

  Color pointColor(const Point &point) const override {
    return ((int(std::floor(point.x())) % 2) == 0 ? color1_ : color2_);
  }

 private:
  Color color1_;
  Color color2_;
};

using StripedPatternP = std::shared_ptr<StripedPattern>;

//---

class GradientPattern : public Pattern {
 public:
  GradientPattern(const Color &color1, const Color &color2) :
   color1_(color1), color2_(color2) {
  }

  const Color &color1() const { return color1_; }
  const Color &color2() const { return color2_; }

  Color pointColor(const Point &point) const override {
    Color  distance = color2_ - color1_;
    double fraction = point.x() - floor(point.x());

    return color1_ + distance*fraction;
  }

 private:
  Color color1_;
  Color color2_;
};

using GradientPatternP = std::shared_ptr<GradientPattern>;

//---

class RingPattern : public Pattern {
 public:
  RingPattern(const Color &color1, const Color &color2) :
   color1_(color1), color2_(color2) {
  }

  const Color &color1() const { return color1_; }
  const Color &color2() const { return color2_; }

  Color pointColor(const Point &point) const override {
    double d = std::hypot(point.x(), point.z());

    return ((int(std::floor(d)) % 2) == 0 ? color1_ : color2_);
  }

 private:
  Color color1_;
  Color color2_;
};

using RingPatternP = std::shared_ptr<RingPattern>;

//---

class CheckerPattern : public Pattern {
 public:
  CheckerPattern(const Color &color1, const Color &color2) :
   color1_(color1), color2_(color2) {
  }

  const Color &color1() const { return color1_; }
  const Color &color2() const { return color2_; }

  Color pointColor(const Point &point) const override {
    double d = std::floor(point.x()) + std::floor(point.y()) + std::floor(point.z());

    return ((int(std::floor(d)) % 2) == 0 ? color1_ : color2_);
  }

 private:
  Color color1_;
  Color color2_;
};

using CheckerPatternP = std::shared_ptr<CheckerPattern>;

}

#endif
