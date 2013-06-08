#ifndef CRAY_TRIANGLE_H
#define CRAY_TRIANGLE_H

#include <CRayShape.h>
#include <CTriangle3D.h>

class CRayTriangle : public CRayShape, public CTriangle3D {
 public:
  CRayTriangle(const CPoint3D &p0, const CPoint3D &p1, const CPoint3D &p2) :
   CTriangle3D(p0, p1, p2) {
  }

  CBBox3D getBBox() const {
    return CTriangle3D::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const;

  CVector3D pointNormal(const CPoint3D &point) const {
    return CTriangle3D::pointNormal(point);
  }

  CVector2D pointToSurfaceVector(const CPoint3D &p) const {
    return CTriangle3D::pointToSurfaceVector(p);
  }

  void translate(const CPoint3D &dist) {
    CTriangle3D::translate(dist);
  }

  void scale(const CPoint3D &size) {
    CTriangle3D::scale(size);
  }

  void rotate(const CPoint3D &angles) {
    CTriangle3D::rotate(angles);
  }
};

#endif
