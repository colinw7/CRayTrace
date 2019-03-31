#ifndef Object_H
#define Object_H

#include <Types.h>
#include <Matrix4D.h>
#include <Material.h>
#include <Ray.h>
#include <Intersection.h>
#include <memory>

namespace RayTrace {

class Object {
 public:
  Object() { transform_ = Matrix4D::identity(); }

  virtual ~Object() { }

  const Matrix4D &transform() const { return transform_; }
  void setTransform(const Matrix4D &v) { transform_ = v; }

  Material &material() { return material_; }
  const Material &material() const { return material_; }
  void setMaterial(const Material &v) { material_ = v; }

  void transform(const Matrix4D &t) {
    transform_ *= t;
  }

  Intersections intersect(const Ray &ray) const {
    Ray localRay = ray.transform(transform().inverted());

    return intersectInternal(localRay);
  }

  Vector pointNormal(const Point &point) const {
    Point localPoint = transform_.inverted()*point;

    Vector localNormal = pointNormalInternal(localPoint);

    Tuple tuple = transform_.inverted().transposed()*localNormal;

    Vector normal(tuple.x(), tuple.y(), tuple.z());

    return normal.normalized();
  }

 protected:
  virtual Intersections intersectInternal(const Ray &ray) const = 0;

  virtual Vector pointNormalInternal(const Point &point) const = 0;

 protected:
  Matrix4D transform_;
  Material material_;
};

//---

class TestObject : public Object {
 public:
  TestObject() { }

  const Ray &saveRay() const { return saveRay_; }

  const Point &savePoint() const { return savePoint_; }

 private:
  Intersections intersectInternal(const Ray &ray) const override {
    saveRay_ = ray;

    return Intersections();
  }

  Vector pointNormalInternal(const Point &point) const override {
    savePoint_ = point;

    return Vector(point.x(), point.y(), point.z());
  }

 private:
  mutable Ray   saveRay_;
  mutable Point savePoint_;
};

using TestObjectP = std::shared_ptr<TestObject>;

}

#endif
