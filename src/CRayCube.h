#ifndef CRAY_CUBE_H
#define CRAY_CUBE_H

#include <CRayShape.h>
#include <CCube3D.h>

class CRayCube : public CRayShape, public CCube3D {
 public:
  CRayCube(double size) :
   CCube3D(size) {
  }

  CBBox3D getBBox() const {
    return CCube3D::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const;

  CVector3D pointNormal(const CPoint3D &point) const {
    return CCube3D::pointNormal(point);
  }

  CVector2D pointToSurfaceVector(const CPoint3D &p) const {
    return CCube3D::pointToSurfaceVector(p);
  }

  void translate(const CPoint3D &dist) {
    CCube3D::translate(dist);
  }

  void scale(const CPoint3D &size) {
    CCube3D::scale(size);
  }

  void rotate(const CPoint3D &angles) {
    CCube3D::rotate(angles);
  }
};

#endif
