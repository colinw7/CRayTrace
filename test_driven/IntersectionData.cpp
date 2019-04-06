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

double
IntersectionData::
schlick() const
{
  double cos = eye().dotProduct(normal());

  if (n1() > n2()) {
    double n = n1()/n2();

    double sin2t = n*n*(1 - cos*cos);

    if (sin2t > 1.0)
      return 1.0;

    double cost = std::sqrt(1 - sin2t);

    cos = cost;
  }

  double n1_n2_f = (n1() - n2())/(n1() + n2());

  double r0 = n1_n2_f*n1_n2_f;

  return r0 + (1 - r0)*std::pow(1 - cos, 5);
}

}
