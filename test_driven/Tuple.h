#ifndef Tuple_H
#define Tuple_H

#include <iostream>
#include <cmath>
#include <cassert>

namespace RayTrace {

class Tuple {
 public:
  static Tuple point(double x, double y, double z) {
    return Tuple(x, y, z, 1.0);
  }

  static Tuple vector(double x, double y, double z) {
    return Tuple(x, y, z, 0.0);
  }

 public:
  // constructor/destructor
  Tuple() { }

  Tuple(double x, double y, double z, double w=1.0) :
   x_(x), y_(y), z_(z), w_(w), normalized_(false) {
  }

 ~Tuple() { }

  //------

  // copy operations
  Tuple(const Tuple &t) :
    x_(t.x_), y_(t.y_), z_(t.z_), w_(t.w_), normalized_(t.normalized_) {
  }

  Tuple &operator=(const Tuple &t) {
    x_ = t.x_; y_ = t.y_; z_ = t.z_; w_ = t.w_;

    normalized_ = t.normalized_;

    return *this;
  }

  //------

  // accessors

  // get
  double x() const { return x_; }
  double y() const { return y_; }
  double z() const { return z_; }
  double w() const { return w_; }

  double operator[](uint i) const {
    assert(i < 4);

    return (&x_)[i];
  }

  // set
  void setX(double x) { x_ = x; normalized_ = false; }
  void setY(double y) { y_ = y; normalized_ = false; }
  void setZ(double z) { z_ = z; normalized_ = false; }
  void setW(double w) { w_ = w; normalized_ = false; }

  void setXYZ(double x, double y, double z) {
    x_ = x; y_ = y; z_ = z; w_ = 1.0; normalized_ = false;
  }

  void setXYZW(double x, double y, double z, double w) {
    x_ = x; y_ = y; z_ = z; w_ = w; normalized_ = false;
  }

  // more get accessors
  bool isNormalized() const { return normalized_; }

  double length() const {
    if (normalized_)
      return 1.0;

    return ::sqrt(x_*x_ + y_*y_ + z_*z_ + w_*w_);
  }

  double magnitude() const {
    return length();
  }

  double lengthSqr() const {
    if (normalized_)
      return 1.0;

    return (x_*x_ + y_*y_ + z_*z_ + w_*w_);
  }

  //------

  bool isPoint () const { return w_ >  0.0; }
  bool isVector() const { return w_ == 0.0; }

  //------

  // comparison
  int cmp(const Tuple &rhs) const {
    auto realCmp = [](double r1, double r2) {
      return std::abs(r1 - r2) < 1E-6;
    };

    if (realCmp(x_, rhs.x_) && realCmp(y_, rhs.y_) && realCmp(z_, rhs.z_) && realCmp(w_, rhs.w_))
      return 0;

    if      (x_ < rhs.x_) return -1;
    else if (x_ > rhs.x_) return  1;
    else if (y_ < rhs.y_) return -1;
    else if (y_ > rhs.y_) return  1;
    else if (z_ < rhs.z_) return -1;
    else if (z_ > rhs.z_) return  1;
    else if (w_ < rhs.w_) return -1;
    else if (w_ > rhs.w_) return  1;
    else                  return  0;
  }

  friend bool operator==(const Tuple &lhs, const Tuple &rhs) {
    return lhs.cmp(rhs) == 0;
  }

  friend bool operator!=(const Tuple &lhs, const Tuple &rhs) {
    return lhs.cmp(rhs) != 0;
  }

  friend bool operator< (const Tuple &lhs, const Tuple &rhs) {
    return lhs.cmp(rhs) <  0;
  }

  friend bool operator<=(const Tuple &lhs, const Tuple &rhs) {
    return lhs.cmp(rhs) <= 0;
  }

  friend bool operator> (const Tuple &lhs, const Tuple &rhs) {
    return lhs.cmp(rhs) >  0;
  }

  friend bool operator>=(const Tuple &lhs, const Tuple &rhs) {
    return lhs.cmp(rhs) >= 0;
  }

  //------

  Tuple point() const {
    assert(w_ > 0.0);

    double w1 = 1.0/w_;

    return Tuple(x_*w1, y_*w1, z_*w1, 1.0);
  }

  //------

  Tuple &zero() {
    x_ = 0.0; y_ = 0.0; z_ = 0.0; w_ = 0.0;

    normalized_ = false;

    return *this;
  }

  //------

  Tuple &normalize() {
    if (normalized_)
      return *this;

    double len = length();

    double factor = (len > 0 ? 1.0/len : 1.0);

    x_ *= factor;
    y_ *= factor;
    z_ *= factor;
    w_ *= factor;

    normalized_ = true;

    return *this;
  }

  Tuple normalized() const {
    if (normalized_)
      return *this;

    double len = length();

    double factor = (len > 0 ? 1.0/len : 1.0);

    return Tuple(x_*factor, y_*factor, z_*factor, w_*factor, true);
  }

  Tuple unit() const {
    return normalized();
  }

  //------

  Tuple &setMagnitude(double magnitude) {
    double factor = 0.0;

    if (normalized_)
      factor = magnitude;
    else {
      double len = length();

      if (len > 0.0)
        factor = magnitude/len;
    }

    x_ *= factor; y_ *= factor; z_ *= factor; w_ *= factor;

    normalized_ = false;

    return *this;
  }

  //------

  double getDistance(const Tuple &t) {
    Tuple diff = *this - t;

    return diff.length();
  }

   double getDistanceSqr(const Tuple &t) {
    Tuple diff = *this - t;

    return diff.lengthSqr();
  }

  //------

  // operators

  // unary +/-
  Tuple operator+() const {
    return Tuple(x_, y_, z_, w_);
  }

  Tuple operator-() const {
    return Tuple(-x_, -y_, -z_, -w_);
  }

  // addition
  friend Tuple operator+(const Tuple &lhs, const Tuple &rhs) {
    //assert(! (lhs.isPoint() && rhs.isPoint()));

    return Tuple(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_, lhs.w_ + rhs.w_);
  }

  friend Tuple operator+=(Tuple &lhs, const Tuple &rhs) {
    //assert(! (lhs.isPoint() && rhs.isPoint()));

    lhs.x_ += rhs.x_; lhs.y_ += rhs.y_; lhs.z_ += rhs.z_; lhs.w_ += rhs.w_;

    lhs.normalized_ = false;

    return lhs;
  }

  // subtraction
  friend Tuple operator-(const Tuple &lhs, const Tuple &rhs) {
    //assert(lhs.w_ >= rhs.w_);

    return Tuple(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_, lhs.w_ - rhs.w_);
  }

  friend Tuple operator-=(Tuple &lhs, const Tuple &rhs) {
    //assert(lhs.w_ >= rhs.w_);

    lhs.x_ -= rhs.x_; lhs.y_ -= rhs.y_; lhs.z_ -= rhs.z_;

    lhs.normalized_ = false;

    return lhs;
  }

  //------

  // scalar multiplication/division
  Tuple &operator*=(double rhs) {
    x_ *= rhs; y_ *= rhs; z_ *= rhs; w_ *= rhs;

    normalized_ = false;

    return *this;
  }

  friend Tuple operator*(const Tuple &lhs, double rhs) {
    return Tuple(lhs.x_*rhs, lhs.y_*rhs, lhs.z_*rhs, lhs.w_*rhs);
  }

  friend Tuple operator*(double lhs, const Tuple &rhs) {
    return Tuple(lhs*rhs.x_, lhs*rhs.y_, lhs*rhs.z_, lhs*rhs.w_);
  }

  Tuple &operator/=(double rhs) {
    double irhs = 1.0/rhs;

    x_ *= irhs; y_ *= irhs; z_ *= irhs; w_ *= irhs;

    normalized_ = false;

    return *this;
  }

  Tuple operator/(double rhs) const {
    double irhs = 1.0/rhs;

    return Tuple(x_*irhs, y_*irhs, z_*irhs, w_*irhs);
  }

  //------

  // dot product
  double dotProduct(const Tuple &rhs) const {
    return (x_*rhs.x_ + y_*rhs.y_ + z_*rhs.z_ + w_*rhs.w_);
  }

  static double dotProduct(const Tuple &v1, const Tuple &v2) {
    return (v1.x_*v2.x_ + v1.y_*v2.y_ + v1.z_*v2.z_ + v1.w_*v2.w_);
  }

  double dotProductSelf() const {
    return (x_*x_ + y_*y_ + z_*z_ + w_*w_);
  }

  static double absDotProduct(const Tuple &v1, const Tuple &v2) {
    return ::fabs(dotProduct(v1, v2));
  }

  //------

  // cross product
  Tuple crossProduct(const Tuple &rhs) const {
    //assert(w_ == 0.0 && rhs.w_ == 0.0);

    return Tuple(y_*rhs.z_ - z_*rhs.y_,
                 z_*rhs.x_ - x_*rhs.z_,
                 x_*rhs.y_ - y_*rhs.x_,
                 0.0,
                 normalized_ && rhs.normalized_);
  }

  static Tuple crossProduct(const Tuple &v1, const Tuple &v2) {
    //assert(v1.w_ == 0.0 && v2.w_ == 0.0);

    return Tuple(v1.y_*v2.z_ - v1.z_*v2.y_,
                 v1.z_*v2.x_ - v1.x_*v2.z_,
                 v1.x_*v2.y_ - v1.y_*v2.x_,
                 0.0,
                 v1.normalized_ && v2.normalized_);
  }

  Tuple unitCrossProduct(const Tuple &rhs) const {
    return crossProduct(rhs).normalize();
  }

  //------

  Tuple normal(const Tuple &t2) {
    return crossProduct(t2).normalize();
  }

  static Tuple normal(const Tuple &t1, const Tuple &t2) {
    return crossProduct(t1, t2).normalize();
  }

  //------

  // output
  void print(std::ostream &os) const {
    os << "(" << x_ << "," << y_ << "," << z_ << "," << w_ << ")";
  }

  friend std::ostream &operator<<(std::ostream &os, const Tuple &t) {
    t.print(os);

    return os;
  }

  void printType(std::ostream &os) const {
    os << (isPoint() ? "point" : "vector");
  }

  //------

 protected:
  Tuple(double x, double y, double z, double w, bool normalized) :
   x_(x), y_(y), z_(z), w_(w), normalized_(normalized) {
  }

 protected:
  double x_ { 0 }; //! x
  double y_ { 0 }; //! y
  double z_ { 0 }; //! z
  double w_ { 1 }; //! w (1.0 point, 0.0 vector)

  bool normalized_ { false };
};

}

#endif
