#ifndef RayTrace_H
#define RayTrace_H

#include <Types.h>

namespace RayTrace {

Matrix4D viewTransform(const Point &from, const Point &to, const Vector &up);

void render(Canvas &canvas, const Camera &camera, World &world);

Color lighting(const Object *object, const Material &material, const PointLight &light,
               const Point &point, const Vector &eye, const Vector &normal, bool inShadow);

}

#endif
