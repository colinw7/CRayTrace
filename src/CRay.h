#ifndef CRAY_H
#define CRAY_H

#include <accessor.h>
#include <CLine3D.h>
#include <CNormal3D.h>

template<typename T>
class CRayT : public CLine3DT<T> {
 private:
  typedef CPoint3DT<T>  Point;
  typedef CVector3DT<T> Vector;
  typedef CNormal3DT<T> Normal;

  T min_t_, max_t_;
  T time_;

 public:
  CRayT() :
   CLine3DT<T>() {
  }

  CRayT(const Point &origin, const Vector &direction,
        T min_t = 1E-6, T max_t = 1E50, T time = 0.0) :
   CLine3DT<T>(origin, direction), min_t_(min_t), max_t_(max_t), time_(time) {
  }

  CRayT(const Point &from, const Point &to, T min_t = 1E-6, T max_t = 1E50, T time = 0.0) :
   CLine3DT<T>(from, to), min_t_(min_t), max_t_(max_t), time_(time) {
  }

  CRayT(const CRayT &ray) :
   CLine3DT<T>(ray), min_t_(ray.min_t_), max_t_(ray.max_t_), time_(ray.time_) {
  }

  const Point  &getOrigin   () const { return CLine3DT<T>::start (); }
  const Vector &getDirection() const { return CLine3DT<T>::vector(); }

  void setOrigin(const Point &origin) { setStart(origin); }
  void setOrigin(T x, T y, T z) { setStart(Point(x, y, z)); }

  void setDirection(const Vector &direction) { setVector(direction); }

  ACCESSOR(minT, T, min_t)
  ACCESSOR(maxT, T, max_t)

  Point operator()(T t) const {
    return CLine3DT<T>::point(t);
  }

  Point pointAt(T t) const {
    return CLine3DT<T>::point(t);
  }

  CRayT reflect(const Point &origin, const Normal &normal) const {
    // using unit direction results in tolerance problems (vector too small)
    T cos_theta1 = getDirection().dotProduct(normal);

    Vector direction = getDirection() - 2*cos_theta1*normal;

    return CRayT(origin, direction);
  }

  CRayT reflect(const Point &origin, const Vector &normal) const {
    // using unit direction results in tolerance problems (vector too small)
    T cos_theta1 = getDirection().dotProduct(normal);

    Vector direction = getDirection() - 2*cos_theta1*normal;

    return CRayT(origin, direction);
  }

  CRayT refract(const Point &origin, const Vector &normal, T n1, T n2) const {
    T cos_theta1 = getDirection().unit().dotProduct(normal);

    T n12 = n1/n2;

    T x = 1.0 - (n12*n12)*(1.0 - cos_theta1*cos_theta1);

    if (x < 0)
      return reflect(origin, normal);

    T cos_theta2 = sqrt(x);

    Vector direction;

    if (cos_theta1 > 0) {
      T a = n12*cos_theta1 - cos_theta2;

      direction = (n12*getDirection() + a*normal).unit();
    }
    else {
      T a = cos_theta2 + n12*cos_theta1;

      direction = (n12*getDirection() - a*normal).unit();
    }

    return CRayT(origin, direction);
  }

  void print(std::ostream &os=std::cout) const {
    os << "(" << getOrigin() << ") + t(" << getDirection() << ")";
  }

  friend std::ostream &operator<<(std::ostream &os, const CRayT &ray) {
    ray.print(os);

    return os;
  }
};

typedef CRayT<double> CRay;

#endif
