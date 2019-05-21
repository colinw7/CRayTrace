#ifndef Matrix4D_H
#define Matrix4D_H

#include <Matrix3D.h>
#include <Tuple.h>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>

#undef minor

namespace RayTrace {

/* / m00 m01 m02 m03 \ */
/* | m10 m11 m12 m13 | */
/* | m20 m21 m22 m23 | */
/* \ m30 m31 m32 m33 / */

class Matrix4D {
 public:
  enum class AxisType {
    X,
    Y,
    Z
  };

 public:
  Matrix4D() { }

  Matrix4D(double m00, double m01, double m02, double m03,
           double m10, double m11, double m12, double m13,
           double m20, double m21, double m22, double m23,
           double m30, double m31, double m32, double m33) :
   m00_(m00), m01_(m01), m02_(m02), m03_(m03),
   m10_(m10), m11_(m11), m12_(m12), m13_(m13),
   m20_(m20), m21_(m21), m22_(m22), m23_(m23),
   m30_(m30), m31_(m31), m32_(m32), m33_(m33) {
  }

  Matrix4D(const Matrix4D &a) {
    memcpy(&m00_, &a.m00_, 16*sizeof(double));
  }

  ~Matrix4D() { delete inverse_; }

  //---

  static Matrix4D identity() {
    Matrix4D m;

    m.setIdentity();

    return m;
  }

  void setIdentity() {
    m00_ = 1.0; m01_ = 0.0; m02_ = 0.0; m03_ = 0.0;
    m10_ = 0.0; m11_ = 1.0; m12_ = 0.0; m13_ = 0.0;
    m20_ = 0.0; m21_ = 0.0; m22_ = 1.0; m23_ = 0.0;
    m30_ = 0.0; m31_ = 0.0; m32_ = 0.0; m33_ = 1.0;

    inverseValid_ = false;
  }

  //---

  static Matrix4D translation(double tx, double ty, double tz) {
    Matrix4D m;

    m.setTranslation(tx, ty, tz);

    return m;
  }

  void setTranslation(double tx, double ty, double tz) {
    m00_ = 1.0; m01_ = 0.0; m02_ = 0.0; m03_ = tx ;
    m10_ = 0.0; m11_ = 1.0; m12_ = 0.0; m13_ = ty ;
    m20_ = 0.0; m21_ = 0.0; m22_ = 1.0; m23_ = tz ;
    m30_ = 0.0; m31_ = 0.0; m32_ = 0.0; m33_ = 1.0;

    inverseValid_ = false;
  }

  //---

  static Matrix4D scale(double sx, double sy, double sz) {
    Matrix4D m;

    m.setScale(sx, sy, sz);

    return m;
  }

  void setScale(double sx, double sy, double sz) {
    m00_ = sx ; m01_ = 0.0; m02_ = 0.0; m03_ = 0.0;
    m10_ = 0.0; m11_ = sy ; m12_ = 0.0; m13_ = 0.0;
    m20_ = 0.0; m21_ = 0.0; m22_ = sz ; m23_ = 0.0;
    m30_ = 0.0; m31_ = 0.0; m32_ = 0.0; m33_ = 1.0;

    inverseValid_ = false;
  }

  //---

  static Matrix4D rotation(AxisType axis, double angle) {
    Matrix4D m;

    m.setRotation(axis, angle);

    return m;
  }

  void setRotation(AxisType axis, double angle) {
    double c = std::cos(angle);
    double s = std::sin(angle);

    if      (axis == AxisType::X) {
      m00_ = 1.0; m01_ = 0.0; m02_ = 0.0;
      m10_ = 0.0; m11_ =   c; m12_ =  -s;
      m20_ = 0.0; m21_ =   s; m22_ =   c;
    }
    else if (axis == AxisType::Y) {
      m00_ =   c; m01_ = 0.0; m02_ =   s;
      m10_ = 0.0; m11_ = 1.0; m12_ = 0.0;
      m20_ =  -s; m21_ = 0.0; m22_ =   c;
    }
    else if (axis == AxisType::Z) {
      m00_ =   c; m01_ =  -s; m02_ = 0.0;
      m10_ =   s; m11_ =   c; m12_ = 0.0;
      m20_ = 0.0; m21_ = 0.0; m22_ = 1.0;
    }
    else {
      assert(false);
    }

    m03_ = 0.0; m13_ = 0.0; m23_ = 0.0;
    m30_ = 0.0; m31_ = 0.0; m32_ = 0.0; m33_ = 1.0;

    inverseValid_ = false;
  }

  //---

  static Matrix4D shear(double xy, double xz, double yx, double yz, double zx, double zy) {
    Matrix4D m;

    m.setShear(xy, xz, yx, yz, zx, zy);

    return m;
  }

  void setShear(double xy, double xz, double yx, double yz, double zx, double zy) {
    m00_ = 1.0; m01_ = xy ; m02_ = xz ; m03_ = 0.0;
    m10_ = yx ; m11_ = 1.0; m12_ = yz ; m13_ = 0.0;
    m20_ = zx ; m21_ = zy ; m22_ = 1.0; m23_ = 0.0;
    m30_ = 0.0; m31_ = 0.0; m32_ = 0.0; m33_ = 1.0;

    inverseValid_ = false;
  }

  //---

  void values(double *m00, double *m01, double *m02, double *m03,
              double *m10, double *m11, double *m12, double *m13,
              double *m20, double *m21, double *m22, double *m23,
              double *m30, double *m31, double *m32, double *m33) const {
    if (m00) { *m00 = m00_; } if (m01) { *m01 = m01_; }
    if (m01) { *m02 = m02_; } if (m03) { *m03 = m03_; }
    if (m10) { *m10 = m10_; } if (m11) { *m11 = m11_; }
    if (m01) { *m12 = m12_; } if (m13) { *m13 = m13_; }
    if (m20) { *m20 = m20_; } if (m21) { *m21 = m21_; }
    if (m01) { *m22 = m22_; } if (m23) { *m23 = m23_; }
    if (m30) { *m30 = m30_; } if (m31) { *m31 = m31_; }
    if (m01) { *m32 = m32_; } if (m33) { *m33 = m33_; }
  }

  void setValues(double m00, double m01, double m02, double m03,
                 double m10, double m11, double m12, double m13,
                 double m20, double m21, double m22, double m23,
                 double m30, double m31, double m32, double m33) {
    m00_ = m00; m01_ = m01; m02_ = m02; m03_ = m03;
    m10_ = m10; m11_ = m11; m12_ = m12; m13_ = m13;
    m20_ = m20; m21_ = m21; m22_ = m22; m23_ = m23;
    m30_ = m30; m31_ = m31; m32_ = m32; m33_ = m33;

    inverseValid_ = false;
  }

  //---

  double value(unsigned int i) const {
    return (&m00_)[i];
  }

  double value(unsigned int r, unsigned int c) const {
    assert(r < 4 && c < 4);

    const double &m = (&m00_)[4*r + c];

    return m;
  }

  void setValue(unsigned int i, double value) {
    (&m00_)[i] = value;

    inverseValid_ = false;
  }

  void setValue(unsigned int r, unsigned int c, double value) {
    assert(r < 4 && c < 4);

    double &m = (&m00_)[4*r + c];

    m = value;

    inverseValid_ = false;
  }

  //---

  void setRow(int r, double x, double y, double z, double w) {
    assert(r < 4);

    double *m = &(&m00_)[r*4];

    m[0] = x; m[1] = y; m[2] = z; m[3] = w;

    inverseValid_ = false;
  }

  void getRow(int r, double *x, double *y, double *z, double *w) {
    assert(r < 4);

    double *m = &(&m00_)[r*4];

    if (x) *x = m[0];
    if (y) *y = m[1];
    if (z) *z = m[2];
    if (w) *w = m[3];
  }

  //---

  void setColumn(int c, double x, double y, double z, double w) {
    assert(c < 4);

    double *m = &(&m00_)[c];

    m[0] = x; m[4] = y; m[8] = z; m[12] = w;

    inverseValid_ = false;
  }

  void getColumn(int c, double *x, double *y, double *z, double *w) {
    assert(c < 4);

    double *m = &(&m00_)[c];

    if (x) *x = m[0];
    if (y) *y = m[4];
    if (z) *z = m[8];
    if (w) *w = m[12];
  }

  //---

  Matrix3D submatrix(int r, int c) const {
    double m[9];

    int i  = 0;
    int i1 = 0;

    for (int ir = 0; ir < 4; ++ir) {
      if (ir == r) { i += 4; continue; }

      for (int ic = 0; ic < 4; ++ic, ++i) {
        if (ic == c) continue;

        m[i1++] = (&m00_)[i];
      }
    }

    assert(i1 == 9);

    return Matrix3D(m[0], m[1], m[2],
                    m[3], m[4], m[5],
                    m[6], m[7], m[8]);
  }

  double minor(int r, int c) const {
    return submatrix(r, c).determinant();
  }

  double cofactor(int r, int c) const {
    int sign = ((r + c) & 1 ? -1 : 1);

    return sign*minor(r, c);
  }

  //---

  bool canInvert() const {
    return (std::abs(determinant()) != 0.0);
  }

  bool invert(Matrix4D &imatrix) const {
    calcInverse();

    imatrix = *inverse_;

    return inverseValid_;
  }

  Matrix4D inverted() const {
    calcInverse();

    assert(inverseValid_);

    return *inverse_;
  }

  //---

  double determinant() const {
    return (m00_*calcDeterminant(m11_, m12_, m13_, m21_, m22_, m23_, m31_, m32_, m33_) -
            m01_*calcDeterminant(m10_, m12_, m13_, m20_, m22_, m23_, m30_, m32_, m33_) +
            m02_*calcDeterminant(m10_, m11_, m13_, m20_, m21_, m23_, m30_, m31_, m33_) -
            m03_*calcDeterminant(m10_, m11_, m12_, m20_, m21_, m22_, m30_, m31_, m32_));
  }

  //---

  void transpose() {
    std::swap(m10_, m01_);
    std::swap(m20_, m02_);
    std::swap(m21_, m12_);
    std::swap(m30_, m03_);
    std::swap(m31_, m13_);
    std::swap(m32_, m23_);

    inverseValid_ = false;
  }

  Matrix4D transposed() const {
    Matrix4D m = *this;

    m.transpose();

    return m;
  }

  //---

  void multiplyTuple(double  xi, double  yi, double  zi, double wi,
                     double *xo, double *yo, double *zo, double *wo) const {
    *xo = m00_*xi + m01_*yi + m02_*zi + m03_*wi;
    *yo = m10_*xi + m11_*yi + m12_*zi + m13_*wi;
    *zo = m20_*xi + m21_*yi + m22_*zi + m23_*wi;
    *wo = m30_*xi + m31_*yi + m32_*zi + m33_*wi;
  }

  void multiplyTuple(const Tuple &p1, Tuple &p2) const {
    p2 = multiplyTuple(p1);
  }

  //--

  Tuple multiplyTuple(const Tuple &t1) const {
    return Tuple(m00_*t1.x() + m01_*t1.y() + m02_*t1.z() + m03_*t1.w(),
                 m10_*t1.x() + m11_*t1.y() + m12_*t1.z() + m13_*t1.w(),
                 m20_*t1.x() + m21_*t1.y() + m22_*t1.z() + m23_*t1.w(),
                 m30_*t1.x() + m31_*t1.y() + m32_*t1.z() + m33_*t1.w());
  }

  Tuple operator*(const Tuple &t1) const {
    return multiplyTuple(t1);
  }

  //--

  void zero() {
    memset(&m00_, 0, 16*sizeof(double));

    inverseValid_ = false;
  }

  //---

  Matrix4D &operator=(const Matrix4D &a) {
    memcpy(&m00_, &a.m00_, 16*sizeof(double));

    inverseValid_ = false;

    return *this;
  }

  Matrix4D &operator+=(const Matrix4D &b) {
    m00_ += b.m00_; m01_ += b.m01_; m02_ += b.m02_; m03_ += b.m03_;
    m10_ += b.m10_; m11_ += b.m11_; m12_ += b.m12_; m13_ += b.m13_;
    m20_ += b.m20_; m21_ += b.m21_; m22_ += b.m22_; m23_ += b.m23_;
    m30_ += b.m30_; m31_ += b.m31_; m32_ += b.m32_; m33_ += b.m33_;

    inverseValid_ = false;

    return *this;
  }

  Matrix4D operator+(const Matrix4D &b) const {
    return Matrix4D(
      m00_ + b.m00_, m01_ + b.m01_, m02_ + b.m02_, m03_ + b.m03_,
      m10_ + b.m10_, m11_ + b.m11_, m12_ + b.m12_, m13_ + b.m13_,
      m20_ + b.m20_, m21_ + b.m21_, m22_ + b.m22_, m23_ + b.m23_,
      m30_ + b.m30_, m31_ + b.m31_, m32_ + b.m32_, m33_ + b.m33_);
  }

  Matrix4D &operator-=(const Matrix4D &b) {
    m00_ -= b.m00_; m01_ -= b.m01_; m02_ -= b.m02_; m03_ -= b.m03_;
    m10_ -= b.m10_; m11_ -= b.m11_; m12_ -= b.m12_; m13_ -= b.m13_;
    m20_ -= b.m20_; m21_ -= b.m21_; m22_ -= b.m22_; m23_ -= b.m23_;
    m30_ -= b.m30_; m31_ -= b.m31_; m32_ -= b.m32_; m33_ -= b.m33_;

    inverseValid_ = false;

    return *this;
  }

  Matrix4D operator-(const Matrix4D &b) const {
    return Matrix4D(
      m00_ - b.m00_, m01_ - b.m01_, m02_ - b.m02_, m03_ - b.m03_,
      m10_ - b.m10_, m11_ - b.m11_, m12_ - b.m12_, m13_ - b.m13_,
      m20_ - b.m20_, m21_ - b.m21_, m22_ - b.m22_, m23_ - b.m23_,
      m30_ - b.m30_, m31_ - b.m31_, m32_ - b.m32_, m33_ - b.m33_);
  }

  Matrix4D &operator*=(const Matrix4D &b) {
    Matrix4D a;

    memcpy(&a.m00_, &m00_, 16*sizeof(double));

    m00_ = a.m00_*b.m00_ + a.m01_*b.m10_ + a.m02_*b.m20_ + a.m03_*b.m30_;
    m01_ = a.m00_*b.m01_ + a.m01_*b.m11_ + a.m02_*b.m21_ + a.m03_*b.m31_;
    m02_ = a.m00_*b.m02_ + a.m01_*b.m12_ + a.m02_*b.m22_ + a.m03_*b.m32_;
    m03_ = a.m00_*b.m03_ + a.m01_*b.m13_ + a.m02_*b.m23_ + a.m03_*b.m33_;

    m10_ = a.m10_*b.m00_ + a.m11_*b.m10_ + a.m12_*b.m20_ + a.m13_*b.m30_;
    m11_ = a.m10_*b.m01_ + a.m11_*b.m11_ + a.m12_*b.m21_ + a.m13_*b.m31_;
    m12_ = a.m10_*b.m02_ + a.m11_*b.m12_ + a.m12_*b.m22_ + a.m13_*b.m32_;
    m13_ = a.m10_*b.m03_ + a.m11_*b.m13_ + a.m12_*b.m23_ + a.m13_*b.m33_;

    m20_ = a.m20_*b.m00_ + a.m21_*b.m10_ + a.m22_*b.m20_ + a.m23_*b.m30_;
    m21_ = a.m20_*b.m01_ + a.m21_*b.m11_ + a.m22_*b.m21_ + a.m23_*b.m31_;
    m22_ = a.m20_*b.m02_ + a.m21_*b.m12_ + a.m22_*b.m22_ + a.m23_*b.m32_;
    m23_ = a.m20_*b.m03_ + a.m21_*b.m13_ + a.m22_*b.m23_ + a.m23_*b.m33_;

    m30_ = a.m30_*b.m00_ + a.m31_*b.m10_ + a.m32_*b.m20_ + a.m33_*b.m30_;
    m31_ = a.m30_*b.m01_ + a.m31_*b.m11_ + a.m32_*b.m21_ + a.m33_*b.m31_;
    m32_ = a.m30_*b.m02_ + a.m31_*b.m12_ + a.m32_*b.m22_ + a.m33_*b.m32_;
    m33_ = a.m30_*b.m03_ + a.m31_*b.m13_ + a.m32_*b.m23_ + a.m33_*b.m33_;

    inverseValid_ = false;

    return *this;
  }

  Matrix4D operator*(const Matrix4D &b) const {
    return Matrix4D(
      m00_*b.m00_ + m01_*b.m10_ + m02_*b.m20_ + m03_*b.m30_,
      m00_*b.m01_ + m01_*b.m11_ + m02_*b.m21_ + m03_*b.m31_,
      m00_*b.m02_ + m01_*b.m12_ + m02_*b.m22_ + m03_*b.m32_,
      m00_*b.m03_ + m01_*b.m13_ + m02_*b.m23_ + m03_*b.m33_,
      m10_*b.m00_ + m11_*b.m10_ + m12_*b.m20_ + m13_*b.m30_,
      m10_*b.m01_ + m11_*b.m11_ + m12_*b.m21_ + m13_*b.m31_,
      m10_*b.m02_ + m11_*b.m12_ + m12_*b.m22_ + m13_*b.m32_,
      m10_*b.m03_ + m11_*b.m13_ + m12_*b.m23_ + m13_*b.m33_,
      m20_*b.m00_ + m21_*b.m10_ + m22_*b.m20_ + m23_*b.m30_,
      m20_*b.m01_ + m21_*b.m11_ + m22_*b.m21_ + m23_*b.m31_,
      m20_*b.m02_ + m21_*b.m12_ + m22_*b.m22_ + m23_*b.m32_,
      m20_*b.m03_ + m21_*b.m13_ + m22_*b.m23_ + m23_*b.m33_,
      m30_*b.m00_ + m31_*b.m10_ + m32_*b.m20_ + m33_*b.m30_,
      m30_*b.m01_ + m31_*b.m11_ + m32_*b.m21_ + m33_*b.m31_,
      m30_*b.m02_ + m31_*b.m12_ + m32_*b.m22_ + m33_*b.m32_,
      m30_*b.m03_ + m31_*b.m13_ + m32_*b.m23_ + m33_*b.m33_);
  }

  Matrix4D &operator*=(double s) {
    m00_ *= s; m01_ *= s; m02_ *= s; m03_ *= s;
    m10_ *= s; m11_ *= s; m12_ *= s; m13_ *= s;
    m20_ *= s; m21_ *= s; m22_ *= s; m23_ *= s;
    m30_ *= s; m31_ *= s; m32_ *= s; m33_ *= s;

    inverseValid_ = false;

    return *this;
  }

  Matrix4D operator*(double s) const {
    return Matrix4D(m00_*s, m01_*s, m02_*s, m03_*s,
                    m10_*s, m11_*s, m12_*s, m13_*s,
                    m20_*s, m21_*s, m22_*s, m23_*s,
                    m30_*s, m31_*s, m32_*s, m33_*s);
  }

  Matrix4D &operator/=(const Matrix4D &b) {
    Matrix4D bi;

    if (! b.invert(bi)) {
      assert(false); throw "Divide by zero";
      return *this;
    }

    return (*this) *= bi;
  }

  Matrix4D operator/(const Matrix4D &b) const {
    Matrix4D bi;

    if (! b.invert(bi))
      throw "Divide by zero";

    return (*this) * bi;
  }

  //---

  double       &operator[](unsigned int i)       { return (&m00_)[i]; }
  const double &operator[](unsigned int i) const { return (&m00_)[i]; }

  //---

  // comparison
  int cmp(const Matrix4D &rhs) const {
    if (realCmp(m00_, rhs.m00_) && realCmp(m01_, rhs.m01_) &&
        realCmp(m02_, rhs.m02_) && realCmp(m03_, rhs.m03_) &&
        realCmp(m10_, rhs.m10_) && realCmp(m11_, rhs.m11_) &&
        realCmp(m12_, rhs.m12_) && realCmp(m13_, rhs.m13_) &&
        realCmp(m20_, rhs.m20_) && realCmp(m21_, rhs.m21_) &&
        realCmp(m22_, rhs.m22_) && realCmp(m23_, rhs.m23_) &&
        realCmp(m30_, rhs.m30_) && realCmp(m31_, rhs.m31_) &&
        realCmp(m32_, rhs.m32_) && realCmp(m33_, rhs.m33_))
      return 0;

    if      (m00_ < rhs.m00_) return -1; else if (m00_ > rhs.m00_) return 1;
    else if (m01_ < rhs.m01_) return -1; else if (m01_ > rhs.m01_) return 1;
    else if (m02_ < rhs.m02_) return -1; else if (m02_ > rhs.m02_) return 1;
    else if (m03_ < rhs.m03_) return -1; else if (m03_ > rhs.m03_) return 1;
    else if (m10_ < rhs.m10_) return -1; else if (m10_ > rhs.m10_) return 1;
    else if (m11_ < rhs.m11_) return -1; else if (m11_ > rhs.m11_) return 1;
    else if (m12_ < rhs.m12_) return -1; else if (m12_ > rhs.m12_) return 1;
    else if (m13_ < rhs.m13_) return -1; else if (m13_ > rhs.m13_) return 1;
    else if (m20_ < rhs.m20_) return -1; else if (m20_ > rhs.m20_) return 1;
    else if (m21_ < rhs.m21_) return -1; else if (m21_ > rhs.m21_) return 1;
    else if (m22_ < rhs.m22_) return -1; else if (m22_ > rhs.m22_) return 1;
    else if (m23_ < rhs.m23_) return -1; else if (m23_ > rhs.m23_) return 1;
    else if (m30_ < rhs.m30_) return -1; else if (m30_ > rhs.m30_) return 1;
    else if (m31_ < rhs.m31_) return -1; else if (m31_ > rhs.m31_) return 1;
    else if (m32_ < rhs.m32_) return -1; else if (m32_ > rhs.m32_) return 1;
    else if (m33_ < rhs.m33_) return -1; else if (m33_ > rhs.m33_) return 1;
    else                      return  0;
  }

  friend bool operator==(const Matrix4D &lhs, const Matrix4D &rhs) {
    return lhs.cmp(rhs) == 0;
  }

  friend bool operator!=(const Matrix4D &lhs, const Matrix4D &rhs) {
    return lhs.cmp(rhs) != 0;
  }

  friend bool operator< (const Matrix4D &lhs, const Matrix4D &rhs) {
    return lhs.cmp(rhs) <  0;
  }

  friend bool operator<=(const Matrix4D &lhs, const Matrix4D &rhs) {
    return lhs.cmp(rhs) <= 0;
  }

  friend bool operator> (const Matrix4D &lhs, const Matrix4D &rhs) {
    return lhs.cmp(rhs) >  0;
  }

  friend bool operator>=(const Matrix4D &lhs, const Matrix4D &rhs) {
    return lhs.cmp(rhs) >= 0;
  }

  void debugCmp(const Matrix4D &rhs) const {
    for (int i = 0; i < 16; ++i) {
      if (! realCmp((&m00_)[i], (&rhs.m00_)[i])) {
        std::cerr << std::setprecision(7) <<
          (&m00_)[i] << " != " << (&rhs.m00_)[i] << " : " << ((&m00_)[i] - (&rhs.m00_)[i]) << "\n";
      }
    }
  }

  //---

  void print(std::ostream &os) const {
    os << std::setprecision(7) <<
      "((" << m00_ << "," << m01_ << "," << m02_ << "," << m03_ << "),";
    os << std::setprecision(7) <<
       "(" << m10_ << "," << m11_ << "," << m12_ << "," << m13_ << "),";
    os << std::setprecision(7) <<
       "(" << m20_ << "," << m21_ << "," << m22_ << "," << m23_ << "),";
    os << std::setprecision(7) <<
       "(" << m30_ << "," << m31_ << "," << m32_ << "," << m33_ << "))";
  }

  friend std::ostream &operator<<(std::ostream &os, const Matrix4D &matrix) {
    matrix.print(os);

    return os;
  }

 private:
  bool realCmp(double r1, double r2) const {
    return std::abs(r1 - r2) < EPSILON();
  }

  void calcInverse() const {
    if (! inverseValid_) {
      if (! inverse_)
        inverse_ = new Matrix4D;

      inverseValid_ = calcInverse(*inverse_);
    }
  }

  bool calcInverse(Matrix4D &imatrix) const {
    double det = determinant();

    if (std::abs(det) == 0.0)
      return false;

    double idet = 1.0/det;

    imatrix.m00_ =  idet*calcDeterminant(m11_, m12_, m13_,
                                         m21_, m22_, m23_,
                                         m31_, m32_, m33_);
    imatrix.m10_ = -idet*calcDeterminant(m10_, m12_, m13_,
                                         m20_, m22_, m23_,
                                         m30_, m32_, m33_);
    imatrix.m20_ =  idet*calcDeterminant(m10_, m11_, m13_,
                                         m20_, m21_, m23_,
                                         m30_, m31_, m33_);
    imatrix.m30_ = -idet*calcDeterminant(m10_, m11_, m12_,
                                         m20_, m21_, m22_,
                                         m30_, m31_, m32_);

    imatrix.m01_ = -idet*calcDeterminant(m01_, m02_, m03_,
                                         m21_, m22_, m23_,
                                         m31_, m32_, m33_);
    imatrix.m11_ =  idet*calcDeterminant(m00_, m02_, m03_,
                                         m20_, m22_, m23_,
                                         m30_, m32_, m33_);
    imatrix.m21_ = -idet*calcDeterminant(m00_, m01_, m03_,
                                         m20_, m21_, m23_,
                                         m30_, m31_, m33_);
    imatrix.m31_ =  idet*calcDeterminant(m00_, m01_, m02_,
                                         m20_, m21_, m22_,
                                         m30_, m31_, m32_);

    imatrix.m02_ =  idet*calcDeterminant(m01_, m02_, m03_,
                                         m11_, m12_, m13_,
                                         m31_, m32_, m33_);
    imatrix.m12_ = -idet*calcDeterminant(m00_, m02_, m03_,
                                         m10_, m12_, m13_,
                                         m30_, m32_, m33_);
    imatrix.m22_ =  idet*calcDeterminant(m00_, m01_, m03_,
                                         m10_, m11_, m13_,
                                         m30_, m31_, m33_);
    imatrix.m32_ = -idet*calcDeterminant(m00_, m01_, m02_,
                                         m10_, m11_, m12_,
                                         m30_, m31_, m32_);

    imatrix.m03_ = -idet*calcDeterminant(m01_, m02_, m03_,
                                         m11_, m12_, m13_,
                                         m21_, m22_, m23_);
    imatrix.m13_ =  idet*calcDeterminant(m00_, m02_, m03_,
                                         m10_, m12_, m13_,
                                         m20_, m22_, m23_);
    imatrix.m23_ = -idet*calcDeterminant(m00_, m01_, m03_,
                                         m10_, m11_, m13_,
                                         m20_, m21_, m23_);
    imatrix.m33_ =  idet*calcDeterminant(m00_, m01_, m02_,
                                         m10_, m11_, m12_,
                                         m20_, m21_, m22_);

    return true;
  }

  double calcDeterminant(double a, double b, double c,
                         double d, double e, double f,
                         double g, double h, double i) const {
    return a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
  }

 private:
  double m00_ { 0.0 }, m01_ { 0.0 }, m02_ { 0.0 }, m03_ { 0.0 };
  double m10_ { 0.0 }, m11_ { 0.0 }, m12_ { 0.0 }, m13_ { 0.0 };
  double m20_ { 0.0 }, m21_ { 0.0 }, m22_ { 0.0 }, m23_ { 0.0 };
  double m30_ { 0.0 }, m31_ { 0.0 }, m32_ { 0.0 }, m33_ { 0.0 };

  mutable Matrix4D *inverse_      { nullptr };
  mutable bool      inverseValid_ { false };
};

}

#endif
