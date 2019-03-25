#include <Tuple.h>
#include <Point.h>
#include <Vector.h>
#include <Color.h>
#include <Matrix4D.h>
#include <Matrix3D.h>
#include <Matrix2D.h>
#include <Ray.h>
#include <Sphere.h>
#include <Canvas.h>

using RayTrace::Tuple;
using RayTrace::Point;
using RayTrace::Vector;
using RayTrace::Color;
using RayTrace::Matrix4D;
using RayTrace::Matrix3D;
using RayTrace::Matrix2D;
using RayTrace::Ray;
using RayTrace::Object;
using RayTrace::Intersection;
using RayTrace::Intersections;
using RayTrace::Sphere;
using RayTrace::Canvas;

struct Projectile {
  Projectile(const Tuple &position, const Tuple &velocity) :
   position(position), velocity(velocity) {
  }

  Tuple position;
  Tuple velocity;
};

struct Environment {
  Environment(const Tuple &gravity, const Tuple &wind) :
   gravity(gravity), wind(wind) {
  }

  Tuple gravity;
  Tuple wind;
};
