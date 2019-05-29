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

  Object *parent() const { return parent_; }
  void setParent(Object *parent) { parent_ = parent; }

  const Matrix4D &transform() const { return transform_; }
  void setTransform(const Matrix4D &v) { transform_ = v; }

  Material &material() { return material_; }
  const Material &material() const { return material_; }
  void setMaterial(const Material &v) { material_ = v; }

  void transform(const Matrix4D &t) {
    transform_ *= t;
  }

  void preTransform(const Matrix4D &t) {
    transform_ = t*transform_;
  }

  Intersections intersect(const Ray &ray) const {
    Ray localRay = ray.transform(transform().inverted());

    return intersectInternal(localRay);
  }

  Vector pointNormal(const Point &point) const {
    Point localPoint = transformPoint(point);

    Vector localNormal = pointNormalInternal(localPoint);

    return transformNormal(localNormal);
  }

  Vector pointNormal(const Point &point, const Intersection &intersection) const {
    Point localPoint = transformPoint(point);

    Vector localNormal = pointNormalInternal(localPoint, intersection);

    return transformNormal(localNormal);
  }

  Point transformPoint(const Point &point) const {
    Point point1 = (parent_ ? parent_->transformPoint(point) : point);

    return transform_.inverted()*point1;
  }

  Vector transformNormal(const Vector &normal) const {
    Tuple tuple = transform_.inverted().transposed()*normal;

    Vector normal1 = Vector(tuple.x(), tuple.y(), tuple.z()).normalized();

    return (parent_ ? parent_->transformNormal(normal1) : normal1);
  }

  virtual bool hasObject(const Object *object) const {
    return (object == this);
  }

 protected:
  virtual Intersections intersectInternal(const Ray &ray) const = 0;

  virtual Vector pointNormalInternal(const Point &point) const = 0;

  virtual Vector pointNormalInternal(const Point &point, const Intersection &) const {
    return pointNormalInternal(point);
  }

 protected:
  Object*  parent_ { nullptr };
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
