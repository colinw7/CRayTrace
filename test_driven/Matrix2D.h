#ifndef Matrix2D_H
#define Matrix2D_H

#include <cmath>
#include <cstring>
#include <cassert>
#include <iostream>
#include <iomanip>

namespace RayTrace {

/* / m00 m01 \ */
/* \ m10 m11 / */

class Matrix2D {
 public:
  Matrix2D() { }

  Matrix2D(double a, double b, double c, double d) :
    m00_(a), m01_(b), m10_(c), m11_(d) {
  }

  Matrix2D(const Matrix2D &a) {
    memcpy(&m00_, &a.m00_, 4*sizeof(double));
  }

 ~Matrix2D() { }

  //---

  void setIdentity() {
    m00_ = 1.0, m01_ = 0.0;
    m10_ = 0.0, m11_ = 1.0;
  }

  //---

  void setScale(double sx, double sy) {
    m00_ = sx , m01_ = 0.0;
    m10_ = 0.0, m11_ = sy ;
  }

  //---

  void setRotation(double a) {
    double c = ::cos(a);
    double s = ::sin(s);

    m00_ =  c , m01_ =  s;
    m10_ = -s , m11_ =  c;
  }

  //---

  void values(double *a, double *b, double *c, double *d) const {
    if (a) *a = m00_;
    if (b) *b = m01_;
    if (c) *c = m10_;
    if (d) *d = m11_;
  }

  void setValues(double a, double b, double c, double d) {
    m00_ = a, m01_ = b;
    m10_ = c, m11_ = d;
  }

  //---

  double value(unsigned int i) { return (&m00_)[i]; }

  double value(unsigned int r, unsigned int c) const {
    assert(r < 2 && c < 2);

    const double &m = (&m00_)[2*r + c];

    return m;
  }

  //---

  void setValue(unsigned int i, double value) {
    (&m00_)[i] = value;
  }

  void setValue(unsigned int r, unsigned int c, double value) {
    assert(r < 2 && c < 2);

    double &m = (&m00_)[2*r + c];

    m = value;
  }

  //---

  void setRow(int r, double x, double y) {
    assert(r < 2);

    double *m = &(&m00_)[r*2];

    m[0] = x, m[1] = y;
  }

  void getRow(int r, double *x, double *y) {
    assert(r < 2);

    double *m = &(&m00_)[r*2];

    if (x) *x = m[0];
    if (y) *y = m[1];
  }

  //---

  void setColumn(int c, double x, double y) {
    assert(c < 2);

    double *m = &(&m00_)[c];

    m[0] = x, m[2] = y;
  }

  void getColumn(int c, double *x, double *y) {
    assert(c < 2);

    double *m = &(&m00_)[c];

    if (x) *x = m[0];
    if (y) *y = m[2];
  }

  //---

  bool invert(Matrix2D &imatrix) const {
    double det = determinant();

    if (::fabs(det) < 1E-6)
      return false;

    double id = 1.0/det;

    imatrix.m00_ =  m11_*id;
    imatrix.m01_ = -m01_*id;
    imatrix.m10_ = -m10_*id;
    imatrix.m11_ =  m00_*id;

    return true;
  }

  Matrix2D inverted() const {
    Matrix2D imatrix;

    if (! invert(imatrix))
      assert(false && "Divide by zero");

    return imatrix;
  }

  //---

  double determinant() const {
    return (m00_*m11_ - m01_*m10_);
  }

  //---

  void transpose() {
    std::swap(m10_, m01_);
  }

  Matrix2D transposed() const {
    return Matrix2D(m00_, m10_, m01_, m11_);
  }

  //---

  void normalize() {
    double det = determinant();

    double id = 1.0/det;

    for (int i = 0; i < 4; ++i)
      (&m00_)[i] *= id;
  }

  //---

  void multiplyPoint(double xi, double yi, double *xo, double *yo) const {
    *xo = m00_*xi + m01_*yi;
    *yo = m10_*xi + m11_*yi;
  }

  void preMultiplyPoint(double xi, double yi, double *xo, double *yo) const {
    *xo = m00_*xi + m10_*yi;
    *yo = m01_*xi + m11_*yi;
  }

  //---

  void zero() { memset(&m00_, 0, 4*sizeof(double)); }

  //---

  Matrix2D &operator=(const Matrix2D &a) {
    memcpy(&m00_, &a.m00_, 4*sizeof(double));

    return *this;
  }

  Matrix2D &operator+=(const Matrix2D &b) {
    m00_ += b.m00_; m01_ += b.m01_,
    m10_ += b.m10_; m11_ += b.m11_;

    return *this;
  }

  Matrix2D operator+(const Matrix2D &b) const {
    Matrix2D c = *this;

    c += b;

    return c;
  }

  Matrix2D &operator-=(const Matrix2D &b) {
    m00_ -= b.m00_; m01_ -= b.m01_,
    m10_ -= b.m10_; m11_ -= b.m11_;

    return *this;
  }

  Matrix2D operator-(const Matrix2D &b) const {
    Matrix2D c = *this;

    c -= b;

    return c;
  }

  Matrix2D &operator*=(const Matrix2D &b) {
    Matrix2D a;

    memcpy(&a.m00_, &m00_, 4*sizeof(double));

    m00_ = a.m00_*b.m00_ + a.m01_*b.m10_;
    m01_ = a.m00_*b.m01_ + a.m01_*b.m11_;

    m10_ = a.m10_*b.m00_ + a.m11_*b.m10_;
    m11_ = a.m10_*b.m01_ + a.m11_*b.m11_;

    return *this;
  }

  Matrix2D operator*(const Matrix2D &b) const {
    Matrix2D c = *this;

    c *= b;

    return c;
  }

  Matrix2D &operator*=(double s) {
    Matrix2D a = *this;

    m00_ = a.m00_*s; m01_ = a.m01_*s;
    m10_ = a.m10_*s; m11_ = a.m11_*s;

    return *this;
  }

  Matrix2D operator*(double s) const {
    Matrix2D c = *this;

    c *= s;

    return c;
  }

  Matrix2D &operator/=(const Matrix2D &b) {
    Matrix2D bi;

    if (! b.invert(bi)) {
      assert(false && "Divide by zero");
      return *this;
    }

    return (*this) *= bi;
  }

  Matrix2D operator/(const Matrix2D &b) const {
    Matrix2D c = *this;

    c /= b;

    return c;
  }

  //---

  double        operator[](unsigned int i)       { return (&m00_)[i]; }
  const double &operator[](unsigned int i) const { return (&m00_)[i]; }

  //---

  //---

  // comparison
  int cmp(const Matrix2D &rhs) const {
    auto realCmp = [](double r1, double r2) {
      return std::abs(r1 - r2) < 1E-6;
    };

    if (realCmp(m00_, rhs.m00_) && realCmp(m01_, rhs.m01_) &&
        realCmp(m10_, rhs.m10_) && realCmp(m11_, rhs.m11_))
      return 0;

    if      (m00_ < rhs.m00_) return -1; else if (m00_ > rhs.m00_) return 1;
    else if (m01_ < rhs.m01_) return -1; else if (m01_ > rhs.m01_) return 1;
    else if (m10_ < rhs.m10_) return -1; else if (m10_ > rhs.m10_) return 1;
    else if (m11_ < rhs.m11_) return -1; else if (m11_ > rhs.m11_) return 1;
    else                      return  0;
  }

  friend bool operator==(const Matrix2D &lhs, const Matrix2D &rhs) {
    return lhs.cmp(rhs) == 0;
  }

  friend bool operator!=(const Matrix2D &lhs, const Matrix2D &rhs) {
    return lhs.cmp(rhs) != 0;
  }

  friend bool operator< (const Matrix2D &lhs, const Matrix2D &rhs) {
    return lhs.cmp(rhs) <  0;
  }

  friend bool operator<=(const Matrix2D &lhs, const Matrix2D &rhs) {
    return lhs.cmp(rhs) <= 0;
  }

  friend bool operator> (const Matrix2D &lhs, const Matrix2D &rhs) {
    return lhs.cmp(rhs) >  0;
  }

  friend bool operator>=(const Matrix2D &lhs, const Matrix2D &rhs) {
    return lhs.cmp(rhs) >= 0;
  }

  //---

  void print(std::ostream &os) const {
    os << std::setprecision(7) << "((" << m00_ << "," << m01_ << "),";
    os << std::setprecision(7) <<  "(" << m10_ << "," << m11_ << "))";
  }

  friend std::ostream &operator<<(std::ostream &os, const Matrix2D &matrix) {
    matrix.print(os);

    return os;
  }

  //---

 private:
  double m00_ { 0.0 }, m01_ { 0.0 };
  double m10_ { 0.0 }, m11_ { 0.0 };
};

}

#endif
