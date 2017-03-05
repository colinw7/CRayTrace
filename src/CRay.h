#ifndef CRAY_H
#define CRAY_H

#include <accessor.h>
#include <CLine3D.h>
#include <CNormal3D.h>

class CRay : public CLine3D {
 public:
  CRay() : CLine3D() { }

  CRay(const CPoint3D &origin, const CVector3D &direction,
       double min_t = 1E-6, double max_t = 1E50, double time = 0.0) :
   CLine3D(origin, direction), min_t_(min_t), max_t_(max_t), time_(time) {
  }

  CRay(const CPoint3D &from, const CPoint3D &to,
       double min_t = 1E-6, double max_t = 1E50, double time = 0.0) :
   CLine3D(from, to), min_t_(min_t), max_t_(max_t), time_(time) {
  }

  CRay(const CRay &ray) :
   CLine3D(ray), min_t_(ray.min_t_), max_t_(ray.max_t_), time_(ray.time_) {
  }

  const CPoint3D  &getOrigin   () const { return CLine3D::start (); }
  const CVector3D &getDirection() const { return CLine3D::vector(); }

  void setOrigin(const CPoint3D &origin) { setStart(origin); }
  void setOrigin(double x, double y, double z) { setStart(CPoint3D(x, y, z)); }

  void setDirection(const CVector3D &direction) { setVector(direction); }

  ACCESSOR(minT, double, min_t)
  ACCESSOR(maxT, double, max_t)

  CPoint3D operator()(double t) const {
    return CLine3D::point(t);
  }

  CPoint3D pointAt(double t) const {
    return CLine3D::point(t);
  }

  CRay reflect(const CPoint3D &origin, const CNormal3D &normal) const {
    // using unit direction results in tolerance problems (vector too small)
    double cos_theta1 = CNormal3D::dotProduct(getDirection(), normal);

    CVector3D direction = getDirection() - 2*cos_theta1*normal;

    return CRay(origin, direction);
  }

  CRay reflect(const CPoint3D &origin, const CVector3D &normal) const {
    // using unit direction results in tolerance problems (vector too small)
    double cos_theta1 = getDirection().dotProduct(normal);

    CVector3D direction = getDirection() - 2*cos_theta1*normal;

    return CRay(origin, direction);
  }

  CRay refract(const CPoint3D &origin, const CVector3D &normal, double n1, double n2) const {
    double cos_theta1 = getDirection().unit().dotProduct(normal);

    double n12 = n1/n2;

    double x = 1.0 - (n12*n12)*(1.0 - cos_theta1*cos_theta1);

    if (x < 0)
      return reflect(origin, normal);

    double cos_theta2 = sqrt(x);

    CVector3D direction;

    if (cos_theta1 > 0) {
      double a = n12*cos_theta1 - cos_theta2;

      direction = (n12*getDirection() + a*normal).unit();
    }
    else {
      double a = cos_theta2 + n12*cos_theta1;

      direction = (n12*getDirection() - a*normal).unit();
    }

    return CRay(origin, direction);
  }

  void print(std::ostream &os=std::cout) const {
    os << "(" << getOrigin() << ") + t(" << getDirection() << ")";
  }

  friend std::ostream &operator<<(std::ostream &os, const CRay &ray) {
    ray.print(os);

    return os;
  }

 private:
  double min_t_, max_t_;
  double time_;
};

#endif
