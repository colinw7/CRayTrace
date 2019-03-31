#include <World.h>
#include <RayTrace.h>
#include <Sphere.h>
#include <PointLight.h>
#include <Point.h>

namespace RayTrace {

Intersections
World::
intersect(const Ray &ray) const
{
  Intersections intersections;

  for (const auto &object : objects_)
    intersections += object->intersect(ray);

  return intersections;
}

Color
World::
shadeHit(const IntersectionData &intersectionData, int remaining) const
{
  assert(intersectionData.object());

  bool inShadow = isShadowed(intersectionData.overPoint());

  Color color;

  for (auto &light : lights_) {
    PointLight *pointLight = dynamic_cast<PointLight *>(light.get());

    if (pointLight)
      color += lighting(intersectionData.object(), intersectionData.object()->material(),
                        *pointLight, intersectionData.overPoint(), intersectionData.eye(),
                        intersectionData.normal(), inShadow);

    color += reflectedColor(intersectionData, remaining);
  }

  return color;
}

Color
World::
colorAt(const Ray &ray, int remaining) const
{
  Color color;

  Intersections intersections = intersect(ray);

  if (intersections.count()) {
    Intersection intersection = intersections.hit();

    if (intersection.object()) {
      IntersectionData intersectionData(intersection, ray, intersections);

      color += shadeHit(intersectionData, remaining);
    }
  }

  return color;
}

bool
World::
isShadowed(const Point &point) const
{
  for (auto &light : lights_) {
    PointLight *pointLight = dynamic_cast<PointLight *>(light.get());
    if (! pointLight) continue;

    Vector v = pointLight->position() - point;

    double distance  = v.magnitude ();
    Vector direction = v.normalized();

    Ray ray(point, direction);

    Intersections intersections = intersect(ray);

    if (intersections.count()) {
      Intersection intersection = intersections.hit();

      return (intersection.object() && intersection.t() < distance);
    }
    else
      return false;
  }

  return false;
}

Color
World::
reflectedColor(const IntersectionData &intersectionData, int remaining) const
{
  if (remaining <= 0)
    return Color(0, 0, 0);

  if (intersectionData.object()->material().reflective() == 0.0)
    return Color(0, 0, 0);

  Ray reflectRay(intersectionData.overPoint(), intersectionData.reflect());

  Color color = colorAt(reflectRay, remaining - 1);

  return color*intersectionData.object()->material().reflective();
}

}

//---

namespace RayTrace {

DefaultWorld::
DefaultWorld()
{
  SphereP sphere1 = std::make_shared<Sphere>();

  Material material;

  material.setColor(Color(0.8, 1.0, 0.6));
  material.setDiffuse(0.7);
  material.setSpecular(0.2);

  sphere1->setMaterial(material);

  addObject(sphere1);

  //--

  SphereP sphere2 = std::make_shared<Sphere>();

  sphere2->transform(Matrix4D::scale(0.5, 0.5, 0.5));

  addObject(sphere2);

  //--

  auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

  addLight(light);
}

}
