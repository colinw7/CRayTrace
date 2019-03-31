#include <RayTrace.h>
#include <Matrix4D.h>
#include <Canvas.h>
#include <Vector.h>
#include <Camera.h>
#include <PointLight.h>
#include <World.h>
#include <Ray.h>
#include <Material.h>

namespace RayTrace {

Matrix4D
viewTransform(const Point &from, const Point &to, const Vector &up)
{
  Vector forward = (to - from).normalized();
  Vector upn     = up.normalized();

  Vector left   = forward.crossProduct(upn);
  Vector trueUp = left   .crossProduct(forward);

  Matrix4D orientation( left   .x(),  left   .y(),  left   .z(), 0.0,
                        trueUp .x(),  trueUp .y(),  trueUp .z(), 0.0,
                       -forward.x(), -forward.y(), -forward.z(), 0.0,
                                0.0,          0.0,          0.0, 1.0);

  return orientation*Matrix4D::translation(-from.x(), -from.y(), -from.z());
}

//---

void
render(Canvas &canvas, const Camera &camera, World &world)
{
  canvas = Canvas(camera.hsize(), camera.vsize());

  for (int y = 0; y < camera.vsize() - 1; ++y) {
    for (int x = 0; x < camera.hsize() - 1; ++x) {
      Ray ray = camera.rayForPixel(x, y);

      Color color = world.colorAt(ray);

      canvas.setPixel(x, y, color);
    }
  }
}

//---

Color
lighting(const Object *object, const Material &material, const PointLight &light,
         const Point &point, const Vector &eye, const Vector &normal, bool inShadow)
{
  assert(object);

  Color color;

  if (material.pattern())
    color = material.pattern()->objectPointColor(object, point);
  else
    color = material.color();

  Color ambient, diffuse, specular;

  // combine the surface color with the light's color intensity
  Color effectiveColor = color*light.intensity();

  // find the direction to the light source
  Vector lightVector = (light.position() - point).normalized();

  // compute the ambient contribution
  ambient = effectiveColor*material.ambient();

  if (inShadow)
    return ambient;

  // lightDotNormal represents the cosine of the angle between the
  // light vector and the normal vector. A negative number means the
  // light is on the other side of the surface
  double lightDotNormal = lightVector.dotProduct(normal);

  if (lightDotNormal < 0) {
    diffuse  = Color(0, 0, 0);
    specular = Color(0, 0, 0);
  }
  else {
    // compute the diffuse contribution
    diffuse = effectiveColor*material.diffuse()*lightDotNormal;

    // reflectDotEye represents the cosine of the angle bwteen the
    // reflection vector and the eye vector. A negative number means the
    // light reflects away from the eye
    Vector reflectVector = (-lightVector).reflect(normal);

    double reflectDotEye = reflectVector.dotProduct(eye);

    if (reflectDotEye <= 0) {
      specular = Color(0, 0, 0);
    }
    else {
      double factor = std::pow(reflectDotEye, material.shininess());

      specular = light.intensity()*material.specular()*factor;
    }
  }

  return ambient + diffuse + specular;
}

}
