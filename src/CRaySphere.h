#ifndef CRAY_SPHERE_H
#define CRAY_SPHERE_H

#include <CRayShape.h>
#include <CSphere3D.h>

class CRaySphere : public CRayShape, public CSphere3D {
 public:
  CRaySphere(double radius) :
   CSphere3D(radius) {
  }

  CBBox3D getBBox() const {
    return CSphere3D::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const;

  CVector3D pointNormal(const CPoint3D &point) const {
    return CSphere3D::pointNormal(point);
  }

  CVector2D pointToSurfaceVector(const CPoint3D &p) const {
    return CSphere3D::pointToSurfaceVector(p);
  }

  void translate(const CPoint3D &dist) {
    CSphere3D::translate(dist);
  }

  void scale(const CPoint3D &size) {
    CSphere3D::scale(size);
  }

  void rotate(const CPoint3D &angles) {
    CSphere3D::rotate(angles);
  }
};

#endif
