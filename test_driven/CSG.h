#ifndef CSG_H
#define CSG_H

#include <Object.h>
#include <RayTrace.h>

namespace RayTrace {

class CSG : public Object {
 public:
  using Children = std::vector<ObjectP>;

 public:
  enum class Op {
    NONE,
    UNION,
    INTERSECTION,
    DIFFERENCE
  };

 public:
  CSG(const Op &op, const ObjectP &lhs, const ObjectP &rhs) :
   op_(op), lhs_(lhs), rhs_(rhs) {
    lhs_->setParent(this);
    rhs_->setParent(this);
  }

  const Op &op() const { return op_; }

  const ObjectP &lhs() const { return lhs_; }
  const ObjectP &rhs() const { return rhs_; }

  bool hasObject(const Object *object) const override {
    return (lhs_->hasObject(object) && rhs_->hasObject(object));
  }

  Intersections filterIntersections(Intersections &intersectons) const;

  static bool intersectionAllowed(const Op &op, bool lhit, bool inl, bool inr);

 protected:
  Intersections intersectInternal(const Ray &ray) const;

  Vector pointNormalInternal(const Point &) const;

 private:
  Op      op_;
  ObjectP lhs_;
  ObjectP rhs_;
};

using CSGP = std::shared_ptr<CSG>;

}

#endif
