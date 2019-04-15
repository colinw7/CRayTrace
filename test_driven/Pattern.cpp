#include <Pattern.h>
#include <Object.h>

namespace RayTrace {

Color
Pattern::
objectPointColor(const Object *object, const Point &point) const
{
  Point point2;

  Point point1 = (object ? object->transformPoint(point) : point);

  point2 = transform().inverted()*point1;

  return pointColor(point2);
}

}
