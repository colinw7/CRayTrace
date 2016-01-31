#ifndef CRAY_DYNAMIC_SPHERE_SHAPE_H
#define CRAY_DYNAMIC_SPHERE_SHAPE_H

#include <CRayDynamicShape.h>
#include <CRaySphere.h>

class CRayDynamicSphere : public CRayDynamicShape, public CRaySphere {
 public:
  CRayDynamicSphere(const CPoint3D &center, double radius,
                    const CRGBA &color, double min_t, double max_t) :
   CRayDynamicShape(min_t, max_t), CRaySphere(center, radius, color) {
  }

  CBBox3D getBBox() const {
    return CRaySphere3D::getBBox();
  }

  bool hitAt(const CRay &ray, double tmin, double tmax,
             double t, CRayHitData *hit_data) const;

  CPoint3D getCenterAt(double t) const;
};

#endif
