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

  Triangle(const Point &p1, const Point &p2, const Point &p3,
           const Vector &n1, const Vector &n2, const Vector &n3) :
   p1_(p1), p2_(p2), p3_(p3), n1_(n1), n2_(n2), n3_(n3), normalsSet_(true) {
    initDep();
  }

  const Point &point1() const { return p1_; }
  void setPoint1(const Point &p) { p1_ = p; initDep(); }

  const Point &point2() const { return p2_; }
  void setPoint2(const Point &p) { p2_ = p; initDep(); }

  const Point &point3() const { return p3_; }
  void setPoint3(const Point &p) { p3_ = p; initDep(); }

  const Point &texturePoint1() const { return tp1_; }
  void setTexturePoint1(const Point &p) { tp1_ = p; }

  const Point &texturePoint2() const { return tp2_; }
  void setTexturePoint2(const Point &p) { tp2_ = p; }

  const Point &texturePoint3() const { return tp3_; }
  void setTexturePoint3(const Point &p) { tp3_ = p; }

  const Vector &normal1() const { return n1_; }
  void setNormal1(const Vector &n) { n1_ = n; }

  const Vector &normal2() const { return n1_; }
  void setNormal2(const Vector &n) { n2_ = n; }

  const Vector &normal3() const { return n3_; }
  void setNormal3(const Vector &n) { n3_ = n; }

  //---

  // calculdated
  const Vector &e1() const { return e1_; }
  const Vector &e2() const { return e2_; }

  const Vector &normal() const { return normal_; }

 protected:
  Intersections intersectInternal(const Ray &ray) const override {
    Intersections intersections;

    // compute first barycentric coordinate
    Vector dir_cross_e2 = ray.direction().crossProduct(e2_);

    double det = e1_.dotProduct(dir_cross_e2);

    if (std::abs(det) < EPSILON())
      return intersections;

    double f = 1.0/det;

    Vector p1_to_origin = ray.origin() - p1_;

    double u = f*p1_to_origin.dotProduct(dir_cross_e2);

    if (u < 0 || u > 1)
      return intersections;

    // Compute second barycentric coordinate
    Vector origin_cross_e1 = p1_to_origin.crossProduct(e1_);

    double v = f*ray.direction().dotProduct(origin_cross_e1);

    if (v < 0 || (u + v) > 1)
      return intersections;

    double t = f*e2_.dotProduct(origin_cross_e1);

    intersections.push_back(Intersection(t, this, u, v));

    return intersections;
  }

  Vector pointNormalInternal(const Point &) const override {
    return normal_;
  }

  Vector pointNormalInternal(const Point &, const Intersection &intersection) const override {
    if (! normalsSet_)
      return normal_;
    else
      return n2_*intersection.u() +
             n3_*intersection.v() +
             n1_*(1 - intersection.u() - intersection.v());
  }

 private:
  void initDep() {
    e1_ = p2_ - p1_;
    e2_ = p3_ - p1_;

    normal_ = e2_.crossProduct(e1_).normalized();
  }

 private:
  Point  p1_, p2_, p3_;
  Vector n1_, n2_, n3_;
  bool   normalsSet_ { false };
  Vector e1_, e2_;
  Point  tp1_ { 0, 0, 0 };
  Point  tp2_ { 1, 0, 0 };
  Point  tp3_ { 0, 1, 0 };
  Vector normal_;
};

using TriangleP = std::shared_ptr<Triangle>;

}

#endif
