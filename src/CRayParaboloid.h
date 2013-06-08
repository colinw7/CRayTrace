#ifndef CRAY_PARABOLOID_H
#define CRAY_PARABOLOID_H

#include <CRayShape.h>
#include <CParaboloid3D.h>

class CRayParaboloid : public CRayShape, public CParaboloid3D {
 public:
  CRayParaboloid(double radius, double zmin, double zmax) :
   CParaboloid3D(radius, zmin, zmax)  {
  }

  CBBox3D getBBox() const {
    return CParaboloid3D::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const;

  CVector3D pointNormal(const CPoint3D &point) const {
    return CParaboloid3D::pointNormal(point);
  }

  CVector2D pointToSurfaceVector(const CPoint3D &p) const {
    return CParaboloid3D::pointToSurfaceVector(p);
  }

  void translate(const CPoint3D &dist) {
    CParaboloid3D::translate(dist);
  }

  void scale(const CPoint3D &size) {
    CParaboloid3D::scale(size);
  }

  void rotate(const CPoint3D &angles) {
    CParaboloid3D::rotate(angles);
  }
};

#endif
