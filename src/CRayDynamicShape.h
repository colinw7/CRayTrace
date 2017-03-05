#ifndef CRAY_DYNAMIC_SHAPE_H
#define CRAY_DYNAMIC_SHAPE_H

#include <CRayShape.h>

class CRayDynamicShape : public CRayShape {
 public:
  CRayDynamicShape(double min_t, double max_t) :
   min_t_(min_t), max_t_(max_t) {
  }

  virtual ~CRayDynamicShape() { }

  CBBox3D getBBox() const {
    return CRayShape::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData &hit_data) const {
    return hitAt(ray, tmin, tmax, 0, &hit_data);
  }

  bool hit(const CRay &ray, double tmin, double tmax) const {
    return hitAt(ray, tmin, tmax, 0, NULL);
  }

  virtual bool hitAt(const CRay &ray, double tmin, double tmax,
                     double t, CRayHitData &hit_data) const {
    return hitAt(ray, tmin, tmax, t, &hit_data);
  }

  virtual bool hitAt(const CRay &ray, double tmin, double tmax,
                     double t) const {
    return hitAt(ray, tmin, tmax, t, NULL);
  }

  virtual bool hitAt(const CRay &ray, double tmin, double tmax,
                     double t, CRayHitData *hit_data) const = 0;

 protected:
  double min_t_ { 0.0 };
  double max_t_ { 0.0 };
};

#endif
