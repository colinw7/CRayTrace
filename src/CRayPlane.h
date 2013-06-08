#ifndef CRAY_PLANE_H
#define CRAY_PLANE_H

#include <CRayShape.h>
#include <CSquare3D.h>

class CRayPlane : public CRayShape, public CSquare3D {
 public:
  CRayPlane(const CPoint3D &p1, const CPoint3D &p2, const CPoint3D &p3) :
   CSquare3D(p1, p2, p3) {
  }

  CBBox3D getBBox() const {
    return CSquare3D::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const;

  CVector3D pointNormal(const CPoint3D &point) const {
    return CSquare3D::pointNormal(point);
  }

  CVector2D pointToSurfaceVector(const CPoint3D &p) const {
    return CSquare3D::pointToSurfaceVector(p);
  }

  void translate(const CPoint3D &dist) {
    CSquare3D::translate(dist);
  }

  void scale(const CPoint3D &size) {
    CSquare3D::scale(size);
  }

  void rotate(const CPoint3D &angles) {
    CSquare3D::rotate(angles);
  }
};

#endif
