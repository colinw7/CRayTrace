#ifndef Intersection_H
#define Intersection_H

#include <Types.h>
#include <vector>
#include <algorithm>
#include <memory>

namespace RayTrace {

class Intersection {
 public:
  Intersection(double t=0.0, const Object *object=nullptr) :
   t_(t), object_(object) {
  }

  double t() const { return t_; }

  const Object *object() const { return object_; }

  bool operator==(const Intersection &rhs) const {
    auto realEq = [](double r1, double r2) { return std::abs(r1 - r2) < 1E-6; };

    return (object_ == rhs.object_ && realEq(t_, rhs.t_));
  }

 private:
  double        t_      { 0.0 };
  const Object *object_ { nullptr };
};

//---

class Intersections {
 public:
  Intersections() { }

  Intersections(std::initializer_list<Intersection> intersections) :
   intersections_(intersections) {
  }

  void push_back(const Intersection &intersection) { intersections_.push_back(intersection); }

  int count() const { return intersections_.size(); }

  const Intersection &operator[](int i) { updateOrder(); return intersections_[i]; }

  Intersections &operator+=(const Intersections &intersections) {
    for (const auto &intersection : intersections.intersections_)
      intersections_.push_back(intersection);

    return *this;
  }

  Intersection hit() const {
    updateOrder();

    static Intersection no_intersection;

    Intersection intersection = no_intersection;

    for (auto const &intersection1 : intersections_) {
      double t1 = intersection1.t();

      if (t1 >= 0.0) {
        if (! intersection.object() || t1 < intersection.t())
          intersection = intersection1;
      }
    }

    return intersection;
  }

  auto begin() const { return intersections_.begin(); }
  auto end  () const { return intersections_.end  (); }

 private:
  void updateOrder() const {
    if (! sorted_)
      const_cast<Intersections *>(this)->sort();
  }

  void sort() {
    std::sort(intersections_.begin(), intersections_.end(),
     [](const Intersection &i1, const Intersection &i2) -> bool {
       return i1.t() < i2.t();
     });

    sorted_ = true;
  }

 private:
  using IntersectionArray = std::vector<Intersection>;

  IntersectionArray intersections_;
  bool              sorted_ { false };
};

}

#endif
