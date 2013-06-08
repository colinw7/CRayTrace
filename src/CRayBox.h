#ifndef CRAY_BOX_H
#define CRAY_BOX_H

#include <CRayShape.h>
#include <CBox3D.h>

class CRayBox : public CRayShape, public CBox3D {
 public:
  CRayBox(double rx, double ry, double rz) :
   CRayShape(), CBox3D(rx, ry, rz) {
  }

  CBBox3D getBBox() const {
    return CBox3D::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const;

  CVector3D pointNormal(const CPoint3D &point) const {
    return CBox3D::pointNormal(point);
  }

  CVector2D pointToSurfaceVector(const CPoint3D &p) const {
    return CBox3D::pointToSurfaceVector(p);
  }

  void translate(const CPoint3D &dist) {
    CBox3D::translate(dist);
  }

  void scale(const CPoint3D &size) {
    CBox3D::scale(size);
  }

  void rotate(const CPoint3D &angles) {
    CBox3D::rotate(angles);
  }
};

#endif
