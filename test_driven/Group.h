#ifndef Group_H
#define Group_H

#include <Object.h>
#include <RayTrace.h>

namespace RayTrace {

class Group : public Object {
 public:
  using Children = std::vector<ObjectP>;

 public:
  Group() { }

  void addObject(const ObjectP &obj) {
    obj->setParent(this);

    children_.push_back(obj);
  }

  const Children &children() const { return children_; }

 protected:
  Intersections intersectInternal(const Ray &ray) const {
    Intersections intersections;

    for (auto &child : children_)
      intersections += child->intersect(ray);

    return intersections;
  }

  Vector pointNormalInternal(const Point &) const {
    assert(false);
  }

 private:
  Children children_;
};

using GroupP = std::shared_ptr<Group>;

}

#endif
