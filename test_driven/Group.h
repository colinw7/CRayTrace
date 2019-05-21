#ifndef Group_H
#define Group_H

#include <Object.h>
#include <RayTrace.h>

namespace RayTrace {

class Group : public Object {
 public:
  using Children = std::vector<ObjectP>;

 public:
  Group(const std::string &name="") :
   name_(name) {
  }

  const std::string &name() const { return name_; }
  void setName(const std::string &s) { name_ = s; }

  void addObject(const ObjectP &obj) {
    obj->setParent(this);

    children_.push_back(obj);
  }

  const Children &children() const { return children_; }

  ObjectP &child(int i) { assert(i >= 0 && i < int(children_.size())); return children_[i]; }

  bool hasObject(const Object *object) const override {
    for (const auto &child : children_)
      if (child->hasObject(object))
        return true;

    return false;
  }

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
  std::string name_;
  Children    children_;
};

using GroupP = std::shared_ptr<Group>;

}

#endif
