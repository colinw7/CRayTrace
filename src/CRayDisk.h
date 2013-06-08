#ifndef CRAY_DISK_H
#define CRAY_DISK_H

#include <CRayShape.h>
#include <CDisk3D.h>

class CRayDisk : public CRayShape, public CDisk3D {
 public:
  CRayDisk(double radius, double height, double inner_radius) :
   CDisk3D(radius, height, inner_radius)  {
  }

  CBBox3D getBBox() const {
    return CDisk3D::getBBox();
  }

  bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const;

  CVector3D pointNormal(const CPoint3D &point) const {
    return CDisk3D::pointNormal(point);
  }

  CVector2D pointToSurfaceVector(const CPoint3D &p) const {
    return CDisk3D::pointToSurfaceVector(p);
  }

  void translate(const CPoint3D &dist) {
    CDisk3D::translate(dist);
  }

  void scale(const CPoint3D &size) {
    CDisk3D::scale(size);
  }

  void rotate(const CPoint3D &angles) {
    CDisk3D::rotate(angles);
  }
};

#endif
