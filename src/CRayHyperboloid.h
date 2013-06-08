#ifndef CRAY_HYPERBOLOID_H
#define CRAY_HYPERBOLOID_H

#include <CRayShape.h>
#include <CHyperboloid3D.h>

class CRayHyperboloid : public CRayShape, public CHyperboloid3D {
 public:
  CRayHyperboloid(const CPoint3D &point1, const CPoint3D &point2) :
   CHyperboloid3D(point1, point2)  {
  }

  CBBox3D getBBox() const {
    return CHyperboloid3D::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const;

  CVector3D pointNormal(const CPoint3D &point) const {
    return CHyperboloid3D::pointNormal(point);
  }

  CVector2D pointToSurfaceVector(const CPoint3D &p) const {
    return CHyperboloid3D::pointToSurfaceVector(p);
  }

  void translate(const CPoint3D &dist) {
    CHyperboloid3D::translate(dist);
  }

  void scale(const CPoint3D &size) {
    CHyperboloid3D::scale(size);
  }

  void rotate(const CPoint3D &angles) {
    CHyperboloid3D::rotate(angles);
  }
};

#endif
