#ifndef Intersection_H
#define Intersection_H

#include <vector>

namespace RayTrace {

class Object;

class Intersection {
 public:
  Intersection(double t=0.0, const Object *object=nullptr) :
   t_(t), object_(object) {
  }

  double t() const { return t_; }

  const Object *object() const { return object_; }

 private:
  double        t_      { 0.0 };
  const Object* object_ { nullptr };
};

class Intersections {
 public:
  Intersections() { }

  Intersections(std::initializer_list<Intersection> intersections) :
   intersections_(intersections) {
  }

  void push_back(const Intersection &intersection) { intersections_.push_back(intersection); }

  int count() const { return intersections_.size(); }

  const Intersection &operator[](int i) { return intersections_[i]; }

  Intersection hit() const {
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

 private:
  using IntersectionArray = std::vector<Intersection>;

  IntersectionArray intersections_;
};

}

#endif
