#include <CSG.h>

namespace RayTrace {

Intersections
CSG::
intersectInternal(const Ray &ray) const
{
  Intersections i = lhs_->intersect(ray).add(rhs_->intersect(ray));

  return filterIntersections(i);
}

Vector
CSG::
pointNormalInternal(const Point &) const
{
  assert(false);

  return Vector();
}

Intersections
CSG::
filterIntersections(Intersections &intersectons) const
{
  bool inl = false;
  bool inr = false;

  Intersections intersectons1;

  for (const auto &intersection : intersectons) {
    bool lhit = lhs_->hasObject(intersection.object());

    if (intersectionAllowed(op_, lhit, inl, inr))
      intersectons1.push_back(intersection);

    if (lhit)
      inl = ! inl;
    else
      inr = ! inr;
  }

  return intersectons1;
}

bool
CSG::
intersectionAllowed(const Op &op, bool lhit, bool inl, bool inr)
{
  switch (op) {
    case Op::UNION:
      return (lhit && ! inr) || (! lhit && ! inl);
    case Op::INTERSECTION:
      return (lhit && inr) || (! lhit && inl);
    case Op::DIFFERENCE:
      return (lhit && ! inr) || (! lhit && inl);
    default:
      return false;
  }
}

}
