#ifndef RayTrace_H
#define RayTrace_H

#undef INFINITY

#include <Types.h>

namespace RayTrace {

Matrix4D viewTransform(const Point &from, const Point &to, const Vector &up);

void render(Canvas &canvas, const Camera &camera, World &world);

Color lighting(const Object *object, const Material &material, const PointLight &light,
               const Point &point, const Vector &eye, const Vector &normal, bool inShadow);

bool solveQuadratic(double a, double b, double c, double &r1, double &r2);

inline double EPSILON () { return 1E-6; }
inline double INFINITY() { return 1E55; }

}

#endif
