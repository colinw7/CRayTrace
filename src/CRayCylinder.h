#ifndef CRAY_CYLINDER_H
#define CRAY_CYLINDER_H

#include <CRayShape.h>
#include <CCylinder3D.h>

class CRayCylinder : public CRayShape, public CCylinder3D {
 public:
  CRayCylinder(double radius, double height) :
   CCylinder3D(radius, height) {
  }

  CBBox3D getBBox() const {
    return CCylinder3D::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const;

  CVector3D pointNormal(const CPoint3D &point) const {
    return CCylinder3D::pointNormal(point);
  }

  CVector2D pointToSurfaceVector(const CPoint3D &p) const {
    return CCylinder3D::pointToSurfaceVector(p);
  }

  void translate(const CPoint3D &dist) {
    CCylinder3D::translate(dist);
  }

  void scale(const CPoint3D &size) {
    CCylinder3D::scale(size);
  }

  void rotate(const CPoint3D &angles) {
    CCylinder3D::rotate(angles);
  }
};

#endif
