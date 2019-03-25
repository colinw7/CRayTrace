#ifndef Matrix3D_H
#define Matrix3D_H

#include <Matrix2D.h>
#include <cstring>
#include <iostream>
#include <iomanip>

#undef minor

namespace RayTrace {

/* / m00 m01 m02 \ */
/* | m10 m11 m12 | */
/* \ m20 m21 m22 / */

class Matrix3D {
 public:
  Matrix3D() { }

  Matrix3D(double m00, double m01, double m02,
           double m10, double m11, double m12,
           double m20, double m21, double m22) :
    m00_(m00), m01_(m01), m02_(m02),
    m10_(m10), m11_(m11), m12_(m12),
    m20_(m20), m21_(m21), m22_(m22) {
  }

  Matrix3D(const Matrix3D &a) {
    memcpy(&m00_, &a.m00_, 9*sizeof(double));
  }

 ~Matrix3D() { }

  //---

  void setIdentity() {
    m00_ = 1.0, m01_ = 0.0, m02_ = 0.0;
    m10_ = 0.0, m11_ = 1.0, m12_ = 0.0;
    m20_ = 0.0, m21_ = 0.0, m22_ = 1.0;
  }

  //---

  void setTranslation(double tx, double ty, double tz) {
    setIdentity();

    m02_ = tx;
    m10_ = ty;
    m20_ = tz;
  }

  //---

  void setScale(double s) {
    m00_ = s  , m01_ = 0.0, m02_ = 0.0;
    m10_ = 0.0, m11_ = s  , m12_ = 0.0;
    m20_ = 0.0, m21_ = 0.0, m22_ = s  ;
  }

  void setScale(double sx, double sy, double sz) {
    m00_ = sx , m01_ = 0.0, m02_ = 0.0;
    m10_ = 0.0, m11_ = sy , m12_ = 0.0;
    m20_ = 0.0, m21_ = 0.0, m22_ = sz ;
  }

  //---

  void values(double *a, double *b, double *c,
              double *d, double *e, double *f,
              double *g, double *h, double *i) const {
    if (a) { *a = m00_; } if (b) { *b = m01_; } if (c) { *c = m02_; }
    if (d) { *d = m10_; } if (e) { *e = m11_; } if (f) { *f = m12_; }
    if (g) { *g = m20_; } if (h) { *h = m21_; } if (i) { *i = m22_; }
  }

  void setValues(double a, double b, double c,
                 double d, double e, double f,
                 double g, double h, double i) {
    m00_ = a; m01_ = b; m02_ = c;
    m10_ = d; m11_ = e; m12_ = f;
    m20_ = g; m21_ = h; m22_ = i;
  }

  //---

  double value(unsigned int i) const { return (&m00_)[i]; }

  double value(unsigned int r, unsigned int c) const {
    assert(r < 3 && c < 3);

    const double &m = (&m00_)[3*r + c];

    return m;
  }

  //---

  void setValue(unsigned int i, double value) {
    (&m00_)[i] = value;
  }

  void setValue(unsigned int r, unsigned int c, double value) {
    assert(r < 3 && c < 3);

    double &m = (&m00_)[3*r + c];

    m = value;
  }

  //---

  void setRow(int r, double x, double y, double z) {
    assert(r < 3);

    double *m = &(&m00_)[r*3];

    m[0] = x, m[1] = y; m[2] = z;
  }

  void getRow(int r, double *x, double *y, double *z) {
    assert(r < 3);

    double *m = &(&m00_)[r*3];

    if (x) *x = m[0];
    if (y) *y = m[1];
    if (z) *z = m[2];
  }

  //---

  void setColumn(int c, double x, double y, double z) {
    assert(c < 3);

    double *m = &(&m00_)[c];

    m[0] = x, m[3] = y; m[6] = z;
  }

  void getColumn(int c, double *x, double *y, double *z) {
    assert(c < 3);

    double *m = &(&m00_)[c];

    if (x) *x = m[0];
    if (y) *y = m[3];
    if (z) *z = m[6];
  }

  //---

  Matrix2D submatrix(int r, int c) const {
    double m[4];

    int i  = 0;
    int i1 = 0;

    for (int ir = 0; ir < 3; ++ir) {
      if (ir == r) { i += 3; continue; }

      for (int ic = 0; ic < 3; ++ic, ++i) {
        if (ic == c) continue;

        m[i1++] = (&m00_)[i];
      }
    }

    assert(i1 == 4);

    return Matrix2D(m[0], m[1],
                    m[2], m[3]);
  }

  double minor(int r, int c) const {
    return submatrix(r, c).determinant();
  }

  double cofactor(int r, int c) const {
    int sign = ((r + c) & 1 ? -1 : 1);

    return sign*minor(r, c);
  }

  //---

  bool invert(Matrix3D &imatrix) const {
    double det = determinant();

    if (::fabs(det) == 0.0)
      return false;

    double id = 1.0/det;

    imatrix.m00_ =  id*calcDeterminant(m11_, m12_, m21_, m22_);
    imatrix.m10_ = -id*calcDeterminant(m10_, m12_, m20_, m22_);
    imatrix.m20_ =  id*calcDeterminant(m10_, m11_, m20_, m21_);

    imatrix.m01_ = -id*calcDeterminant(m01_, m02_, m21_, m22_);
    imatrix.m11_ =  id*calcDeterminant(m00_, m02_, m20_, m22_);
    imatrix.m21_ = -id*calcDeterminant(m00_, m01_, m20_, m21_);

    imatrix.m02_ =  id*calcDeterminant(m01_, m02_, m11_, m12_);
    imatrix.m12_ = -id*calcDeterminant(m00_, m02_, m10_, m12_);
    imatrix.m22_ =  id*calcDeterminant(m00_, m01_, m10_, m11_);

    return true;
  }

  Matrix3D inverse() const {
    Matrix3D imatrix;

    if (! invert(imatrix))
      assert(false && "Divide by 0.0");

    return imatrix;
  }

  //---

  double determinant() const {
    return (m00_*calcDeterminant(m11_, m12_, m21_, m22_) -
            m01_*calcDeterminant(m10_, m12_, m20_, m22_) +
            m02_*calcDeterminant(m10_, m11_, m20_, m21_));
  }

  //---

  void transpose() {
    std::swap(m10_, m01_);
    std::swap(m20_, m02_);
    std::swap(m21_, m12_);
  }

  Matrix3D transposed() const {
    return Matrix3D(m00_, m10_, m20_,
                    m01_, m11_, m21_,
                    m02_, m12_, m22_);
  }

  //---

  void normalize() {
    double det = determinant();

    double id = 1.0/det;

    for (int i = 0; i < 9; ++i)
      (&m00_)[i] *= id;
  }

  //---

  void multiplyPoint(double  xi, double  yi, double  zi,
                     double *xo, double *yo, double *zo) const {
    *xo = m00_*xi + m01_*yi + m02_*zi;
    *yo = m10_*xi + m11_*yi + m12_*zi;
    *zo = m20_*xi + m21_*yi + m22_*zi;
  }

  void preMultiplyPoint(double xi, double yi, double zi,
                        double *xo, double *yo, double *zo) const {
    *xo = m00_*xi + m10_*yi + m20_*zi;
    *yo = m01_*xi + m11_*yi + m21_*zi;
    *zo = m02_*xi + m12_*yi + m22_*zi;
  }

  //---

  void zero() { memset(&m00_, 0, 9*sizeof(double)); }

  //---

  Matrix3D &operator=(const Matrix3D &a) {
    memcpy(&m00_, &a.m00_, 9*sizeof(double));

    return *this;
  }

  Matrix3D &operator+=(const Matrix3D &b) {
    m00_ += b.m00_; m01_ += b.m01_; m02_ += b.m02_;
    m10_ += b.m10_; m11_ += b.m11_; m12_ += b.m12_;
    m20_ += b.m20_; m21_ += b.m21_; m22_ += b.m22_;

    return *this;
  }

  Matrix3D operator+(const Matrix3D &b) const {
    Matrix3D c = *this;

    c += b;

    return c;
  }

  Matrix3D &operator-=(const Matrix3D &b) {
    m00_ -= b.m00_; m01_ -= b.m01_, m02_ -= b.m02_;
    m10_ -= b.m10_; m11_ -= b.m11_; m12_ -= b.m12_;
    m20_ -= b.m20_; m21_ -= b.m21_; m22_ -= b.m22_;

    return *this;
  }

  Matrix3D operator-(const Matrix3D &b) const {
    Matrix3D c = *this;

    c -= b;

    return c;
  }

  Matrix3D &operator*=(const Matrix3D &b) {
    Matrix3D a = *this;

    m00_ = a.m00_*b.m00_ + a.m01_*b.m10_ + a.m02_*b.m20_;
    m01_ = a.m00_*b.m01_ + a.m01_*b.m11_ + a.m02_*b.m21_;
    m02_ = a.m00_*b.m02_ + a.m01_*b.m12_ + a.m02_*b.m22_;

    m10_ = a.m10_*b.m00_ + a.m11_*b.m10_ + a.m12_*b.m20_;
    m11_ = a.m10_*b.m01_ + a.m11_*b.m11_ + a.m12_*b.m21_;
    m12_ = a.m10_*b.m02_ + a.m11_*b.m12_ + a.m12_*b.m22_;

    m20_ = a.m20_*b.m00_ + a.m21_*b.m10_ + a.m22_*b.m20_;
    m21_ = a.m20_*b.m01_ + a.m21_*b.m11_ + a.m22_*b.m21_;
    m22_ = a.m20_*b.m02_ + a.m21_*b.m12_ + a.m22_*b.m22_;

    return *this;
  }

  Matrix3D operator*(const Matrix3D &b) const {
    Matrix3D c = *this;

    c *= b;

    return c;
  }

  Matrix3D &operator*=(double s) {
    Matrix3D a = *this;

    m00_ = a.m00_*s; m01_ = a.m01_*s; m02_ = a.m02_*s;
    m10_ = a.m10_*s; m11_ = a.m11_*s; m12_ = a.m12_*s;
    m20_ = a.m20_*s; m21_ = a.m21_*s; m22_ = a.m22_*s;

    return *this;
  }

  Matrix3D operator*(double s) const {
    Matrix3D c = *this;

    c *= s;

    return c;
  }

  Matrix3D &operator/=(const Matrix3D &b) {
    Matrix3D bi;

    if (! b.invert(bi)) {
      assert(false && "Divide by zero");
      return *this;
    }

    return (*this) *= bi;
  }

  Matrix3D operator/(const Matrix3D &b) const {
    Matrix3D c = *this;

    c /= b;

    return c;
  }

  //---

  double        operator[](unsigned int i)       { return (&m00_)[i]; }
  const double &operator[](unsigned int i) const { return (&m00_)[i]; }

  //---

  // comparison
  int cmp(const Matrix3D &rhs) const {
    auto realCmp = [](double r1, double r2) {
      return std::abs(r1 - r2) < 1E-6;
    };

    if (realCmp(m00_, rhs.m00_) && realCmp(m01_, rhs.m01_) && realCmp(m02_, rhs.m02_) &&
        realCmp(m10_, rhs.m10_) && realCmp(m11_, rhs.m11_) && realCmp(m12_, rhs.m12_) &&
        realCmp(m20_, rhs.m20_) && realCmp(m21_, rhs.m21_) && realCmp(m22_, rhs.m22_))
      return 0;

    if      (m00_ < rhs.m00_) return -1; else if (m00_ > rhs.m00_) return 1;
    else if (m01_ < rhs.m01_) return -1; else if (m01_ > rhs.m01_) return 1;
    else if (m02_ < rhs.m02_) return -1; else if (m02_ > rhs.m02_) return 1;
    else if (m10_ < rhs.m10_) return -1; else if (m10_ > rhs.m10_) return 1;
    else if (m11_ < rhs.m11_) return -1; else if (m11_ > rhs.m11_) return 1;
    else if (m12_ < rhs.m12_) return -1; else if (m12_ > rhs.m12_) return 1;
    else if (m20_ < rhs.m20_) return -1; else if (m20_ > rhs.m20_) return 1;
    else if (m21_ < rhs.m21_) return -1; else if (m21_ > rhs.m21_) return 1;
    else if (m22_ < rhs.m22_) return -1; else if (m22_ > rhs.m22_) return 1;
    else                      return  0;
  }

  friend bool operator==(const Matrix3D &lhs, const Matrix3D &rhs) {
    return lhs.cmp(rhs) == 0;
  }

  friend bool operator!=(const Matrix3D &lhs, const Matrix3D &rhs) {
    return lhs.cmp(rhs) != 0;
  }

  friend bool operator< (const Matrix3D &lhs, const Matrix3D &rhs) {
    return lhs.cmp(rhs) <  0;
  }

  friend bool operator<=(const Matrix3D &lhs, const Matrix3D &rhs) {
    return lhs.cmp(rhs) <= 0;
  }

  friend bool operator> (const Matrix3D &lhs, const Matrix3D &rhs) {
    return lhs.cmp(rhs) >  0;
  }

  friend bool operator>=(const Matrix3D &lhs, const Matrix3D &rhs) {
    return lhs.cmp(rhs) >= 0;
  }

  //---

  void print(std::ostream &os) const {
    os << std::setprecision(7) << "((" << m00_ << "," << m01_ << "," << m02_ << "),";
    os << std::setprecision(7) <<  "(" << m10_ << "," << m11_ << "," << m12_ << "),";
    os << std::setprecision(7) <<  "(" << m20_ << "," << m21_ << "," << m22_ << "))";
  }

  friend std::ostream &operator<<(std::ostream &os, const Matrix3D &matrix) {
    matrix.print(os);

    return os;
  }

  //---

 private:
  static double calcDeterminant(double m00, double m01, double m10, double m11) {
    return m00*m11 - m01*m10;
  }

 private:
  double m00_ { 0.0 }, m01_ { 0.0 }, m02_ { 0.0 };
  double m10_ { 0.0 }, m11_ { 0.0 }, m12_ { 0.0 };
  double m20_ { 0.0 }, m21_ { 0.0 }, m22_ { 0.0 };
};

}

#endif
