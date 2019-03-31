#include <Tuple.h>
#include <Point.h>
#include <Vector.h>
#include <Color.h>
#include <Matrix4D.h>
#include <Matrix3D.h>
#include <Matrix2D.h>
#include <Ray.h>
#include <Sphere.h>
#include <Plane.h>
#include <PointLight.h>
#include <Material.h>
#include <Pattern.h>
#include <Canvas.h>
#include <World.h>
#include <Camera.h>
#include <RayTrace.h>
#include <IntersectionData.h>

// Point, Vector
using RayTrace::Tuple;
using RayTrace::Point;
using RayTrace::Vector;

// matrices
using RayTrace::Matrix4D;
using RayTrace::Matrix3D;
using RayTrace::Matrix2D;

using RayTrace::Color;

using RayTrace::Ray;

using RayTrace::Intersection;
using RayTrace::Intersections;
using RayTrace::IntersectionData;

// objects
using RayTrace::Object;
using RayTrace::ObjectP;
using RayTrace::TestObject;
using RayTrace::TestObjectP;
using RayTrace::Sphere;
using RayTrace::SphereP;
using RayTrace::GlassSphere;
using RayTrace::GlassSphereP;
using RayTrace::Plane;
using RayTrace::PlaneP;

// lights
using RayTrace::Light;
using RayTrace::PointLight;

using RayTrace::Material;

// pattern
using RayTrace::Pattern;
using RayTrace::TestPattern;
using RayTrace::StripedPattern;
using RayTrace::GradientPattern;
using RayTrace::RingPattern;
using RayTrace::CheckerPattern;

using RayTrace::Canvas;
using RayTrace::Camera;

// world
using RayTrace::World;
using RayTrace::DefaultWorld;

//---

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
