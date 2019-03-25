#ifndef Point_H
#define Point_H

namespace RayTrace {

class Point : public Tuple {
 public:
  Point(double x, double y, double z) :
   Tuple(x, y, z, 1.0) {
  }

  Point(const Tuple &t) :
   Tuple(t.x(), t.y(), t.z(), 1.0) {
    assert(t.w() == 1.0);
  }

  void print(std::ostream &os) const {
    os << "(" << x_ << "," << y_ << "," << z_ << ")";
  }

 private:
  double w() const { return Tuple::w(); }
};

}

#endif
