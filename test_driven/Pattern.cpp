#include <Pattern.h>
#include <Object.h>

namespace RayTrace {

Color
Pattern::
objectPointColor(const Object *object, const Point &point) const
{
  Point point2;

  if (object) {
    Point point1 = object->transform().inverted()*point;

    point2 = transform().inverted()*point1;
  }
  else
    point2 = transform().inverted()*point;

  return pointColor(point2);
}

}
