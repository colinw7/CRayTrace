#ifndef Vector_H
#define Vector_H

namespace RayTrace {

class Vector : public Tuple {
 public:
  Vector(double x, double y, double z) :
   Tuple(x, y, z, 0.0) {
  }

  Vector(const Tuple &t) :
   Tuple(t.x(), t.y(), t.z(), 0.0) {
    assert(t.w() == 0.0);
  }

  void print(std::ostream &os) const {
    os << "(" << x_ << "," << y_ << "," << z_ << ")";
  }

 private:
  double w() const { return Tuple::w(); }
};

}

#endif
