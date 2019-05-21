#ifndef Intersection_H
#define Intersection_H

#include <Types.h>
#include <RayTrace.h>
#include <vector>
#include <algorithm>
#include <memory>

namespace RayTrace {

class Intersection {
 public:
  Intersection(double t=0.0, const Object *object=nullptr) :
   t_(t), object_(object) {
  }

  Intersection(double t, const Object *object, double u, double v) :
   t_(t), object_(object), u_(u), v_(v) {
  }

  double t() const { return t_; }

  double u() const { return u_; }
  double v() const { return v_; }

  const Object *object() const { return object_; }

  bool operator==(const Intersection &rhs) const {
    auto realEq = [](double r1, double r2) { return std::abs(r1 - r2) < EPSILON(); };

    return (object_ == rhs.object_ && realEq(t_, rhs.t_));
  }

 private:
  double        t_      { 0.0 };
  const Object *object_ { nullptr };
  double        u_      { -1.0 };
  double        v_      { -1.0 };
};

//---

class Intersections {
 public:
  Intersections() { }

  Intersections(std::initializer_list<Intersection> intersections) :
   intersections_(intersections) {
  }

  void push_back(const Intersection &intersection) { intersections_.push_back(intersection); }

  Intersections &add(const Intersections &intersections) {
    for (auto const &intersection : intersections.intersections_)
      intersections_.push_back(intersection);

    sorted_ = false;

    return *this;
  }

  int count() const { return intersections_.size(); }

  const Intersection &operator[](int i) { updateOrder(); return intersections_[i]; }

  Intersection at(int i) {
    updateOrder();

    if (i < 0 || i >= int(intersections_.size()))
      return Intersection();

    return intersections_[i];
  }

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

  auto begin() const { updateOrder(); return intersections_.begin(); }
  auto end  () const { updateOrder(); return intersections_.end  (); }

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
