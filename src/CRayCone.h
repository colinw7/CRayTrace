#ifndef CRAY_CONE_H
#define CRAY_CONE_H

#include <CRayShape.h>
#include <CCone3D.h>

class CRayCone : public CRayShape, public CCone3D {
 public:
  CRayCone(double radius, double height) :
   CCone3D(radius, height) {
  }

  CBBox3D getBBox() const {
    return CCone3D::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const;

  CVector3D pointNormal(const CPoint3D &point) const {
    return CCone3D::pointNormal(point);
  }

  CVector2D pointToSurfaceVector(const CPoint3D &p) const {
    return CCone3D::pointToSurfaceVector(p);
  }

  void translate(const CPoint3D &dist) {
    CCone3D::translate(dist);
  }

  void scale(const CPoint3D &size) {
    CCone3D::scale(size);
  }

  void rotate(const CPoint3D &angles) {
    CCone3D::rotate(angles);
  }
};

#endif
