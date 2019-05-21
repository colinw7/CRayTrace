#ifndef Types_H
#define Types_H

#include <memory>

namespace RayTrace {

class Object;
class Group;
class Pattern;
class Light;
class Matrix4D;
class World;
class Vector;
class Point;
class Canvas;
class Camera;
class Color;
class Material;
class PointLight;
class Ray;
class Intersection;
class Intersections;

using ObjectP  = std::shared_ptr<Object>;
using GroupP   = std::shared_ptr<Group>;
using PatternP = std::shared_ptr<Pattern>;
using LightP   = std::shared_ptr<Light>;

}

#endif
