#include <IntersectionData.h>
#include <Intersection.h>
#include <Ray.h>
#include <Object.h>
#include <set>

namespace RayTrace {

IntersectionData::
IntersectionData(const Intersection &intersection, const Ray &ray,
                 const Intersections &intersections)
{
  assert(intersection.object());

  t_      = intersection.t();
  object_ = intersection.object();

  point_  = ray.position(t_);
  eye_    = -ray.direction();
  normal_ = object_->pointNormal(point_);

  if (normal_.dotProduct(eye_) < 0) {
    inside_ = true;
    normal_ = -normal_;
  }
  else {
    inside_ = false;
  }

  overPoint_  = point_ + normal_*EPSILON();
  underPoint_ = point_ - normal_*EPSILON();

  reflect_ = ray.direction().reflect(normal_);

  //-----

  std::vector<const Object *> containers;

  //---

  auto containersFind = [&](const Object *object) {
    for (const auto &container : containers)
      if (container == object)
        return true;

    return false;
  };

  //---

  auto containersRemove = [&](const Object *object) {
    std::size_t i = 0;

    for ( ; i < containers.size(); ++i) {
      if (containers[i] == object)
        break;
    }

    assert(i < containers.size());

    ++i;

    for ( ; i < containers.size(); ++i)
      containers[i - 1] = containers[i];

    containers.pop_back();
  };

  //---

  for (const auto &intersection1 : intersections) {
    if (intersection1 == intersection) {
      if (containers.empty())
        n1_ = 1.0;
      else
        n1_ = containers.back()->material().refractiveIndex();
    }

    if (containersFind(intersection1.object())) {
      containersRemove(intersection1.object());
    }
    else {
      containers.push_back(intersection1.object());
    }

    if (intersection1 == intersection) {
      if (containers.empty())
        n2_ = 1.0;
      else
        n2_ = containers.back()->material().refractiveIndex();

      break;
    }
  }
}

}
