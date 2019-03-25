#ifndef Color_H
#define Color_H

namespace RayTrace {

class Color {
 public:
  Color() { }

  Color(double r, double g, double b, double a=1.0) :
   r_(r), g_(g), b_(b), a_(a) {
  }

  //---

  double red  () const { return r_; }
  double green() const { return g_; }
  double blue () const { return b_; }
  double alpha() const { return a_; }

  int redI  () const { return clampI(ivalue(r_)); }
  int greenI() const { return clampI(ivalue(g_)); }
  int blueI () const { return clampI(ivalue(b_)); }
  int alphaI() const { return clampI(ivalue(a_)); }

  //---

  // unary plus
  Color operator+() const {
    return *this;
  }

  // unary minus
  Color operator-() const {
    return Color(-r_, -g_, -b_, a_);
  }

  //---

  // plus
  Color &operator+=(const Color &rhs) {
    r_ = r_*a_ + rhs.r_*rhs.a_;
    g_ = g_*a_ + rhs.g_*rhs.a_;
    b_ = b_*a_ + rhs.b_*rhs.a_;
    a_ = 1.0;

    return *this;
  }

  Color operator+(const Color &rhs) const {
    Color t = *this;

    t += rhs;

    return t;
  }

  //---

  // minus
  Color &operator-=(const Color &rhs) {
    r_ = r_*a_ - rhs.r_*rhs.a_;
    g_ = g_*a_ - rhs.g_*rhs.a_;
    b_ = b_*a_ - rhs.b_*rhs.a_;
    a_ = 1.0;

    return *this;
  }

  Color operator-(const Color &rhs) const {
    Color t = *this;

    t -= rhs;

    return t;
  }

  //---

  // times
  Color &operator*=(double rhs) {
    r_ = rhs*r_*a_;
    g_ = rhs*g_*a_;
    b_ = rhs*b_*a_;
    a_ = 1.0;

    return *this;
  }

  Color &operator*=(const Color &rhs) {
    r_ = rhs.r_*rhs.a_*r_*a_;
    g_ = rhs.g_*rhs.a_*g_*a_;
    b_ = rhs.b_*rhs.a_*b_*a_;
    a_ = 1.0;

    return *this;
  }

  Color operator*(double rhs) const {
    Color t = *this;

    t *= rhs;

    return t;
  }

  Color operator*(const Color &rhs) const {
    Color t = *this;

    t *= rhs;

    return t;
  }

  //---

  // divide
  Color &operator/=(double rhs) {
    double irhs = (rhs != 0.0 ? 1.0/rhs : 0.0);

    return operator*=(irhs);
  }

  Color &operator/=(const Color &rhs) {
    r_ = rhs.r_*rhs.a_/r_*a_;
    g_ = rhs.g_*rhs.a_/g_*a_;
    b_ = rhs.b_*rhs.a_/b_*a_;
    a_ = 1.0;

    return *this;
  }

  Color operator/(double rhs) const {
    Color t = *this;

    t /= rhs;

    return t;
  }

  Color operator/(const Color &rhs) const {
    Color t = *this;

    t /= rhs;

    return t;
  }

  //---

  // comparison
  int cmp(const Color &rhs) const {
    auto realCmp = [](double r1, double r2) {
      return std::abs(r1 - r2) < 1E-6;
    };

    if (realCmp(r_, rhs.r_) && realCmp(g_, rhs.g_) && realCmp(b_, rhs.b_) && realCmp(a_, rhs.a_))
      return 0;

    if      (r_ < rhs.r_) return -1;
    else if (r_ > rhs.r_) return  1;
    else if (g_ < rhs.g_) return -1;
    else if (g_ > rhs.g_) return  1;
    else if (b_ < rhs.b_) return -1;
    else if (b_ > rhs.b_) return  1;
    else if (a_ < rhs.a_) return -1;
    else if (a_ > rhs.a_) return  1;
    else                  return  0;
  }

  friend bool operator==(const Color &lhs, const Color &rhs) {
    return lhs.cmp(rhs) == 0;
  }

  friend bool operator!=(const Color &lhs, const Color &rhs) {
    return lhs.cmp(rhs) != 0;
  }

  friend bool operator< (const Color &lhs, const Color &rhs) {
    return lhs.cmp(rhs) <  0;
  }

  friend bool operator<=(const Color &lhs, const Color &rhs) {
    return lhs.cmp(rhs) <= 0;
  }

  friend bool operator> (const Color &lhs, const Color &rhs) {
    return lhs.cmp(rhs) >  0;
  }

  friend bool operator>=(const Color &lhs, const Color &rhs) {
    return lhs.cmp(rhs) >= 0;
  }

  //---

  void print(std::ostream &os) const {
    os << r_ << " " << g_ << " " << b_ << " " << a_;
  }

  friend std::ostream &operator<<(std::ostream &os, const Color &c) {
    c.print(os);

    return os;
  }

 private:
  static int iround(double r) {
    if (r < 0)
      return int(r - 0.5);
    else
      return int(r + 0.5);
  }

  static int ivalue(double r) {
    return iround(r*255.0);
  }

  static double rvalue(int i) {
    return i/255.0;
  }

  static uint clampI(int v) {
    return (v >= 0 ? (v <= 255 ? v : 255) : 0);
  }

 private:
  double r_ { 0.0 };
  double g_ { 0.0 };
  double b_ { 0.0 };
  double a_ { 1.0 };
};

}

#endif
