#ifndef CRAY_TRACE_CAMERA_H
#define CRAY_TRACE_CAMERA_H

class CRayTrace;

#include <CPoint3D.h>
#include <CVector3D.h>
#include <CMatrix3DH.h>
#include <CRay.h>

class CRayTraceCamera {
 public:
  CRayTraceCamera(CRayTrace *raytrace);

  ACCESSOR(Z1         , double   , z1)
  ACCESSOR(Z2         , double   , z2)
  ACCESSOR(Perspective, bool     , perspective)
  ACCESSOR(Position   , CPoint3D , position)
  ACCESSOR(LookAt     , CPoint3D , lookAt)
  ACCESSOR(Up         , CVector3D, up)
  ACCESSOR(FieldOfView, double   , fov)

  void init();

  CRay getRay(double x, double y) const;

  CPoint3D worldToRaster(const CPoint3D &p) const;

 private:
  CRayTrace *raytrace_;
  double     z1_, z2_;
  bool       perspective_;
  CPoint3D   position_;
  CPoint3D   lookAt_;
  CVector3D  up_;
  double     fov_;

  mutable CMatrix3DH worldToCamera_;
  mutable CMatrix3DH cameraToWorld_;
  mutable CMatrix3DH screenToRaster_;
  mutable CMatrix3DH rasterToScreen_;
  mutable CMatrix3DH cameraToScreen_;
  mutable CMatrix3DH worldToScreen_;
  mutable CMatrix3DH screenToCamera_;
  mutable CMatrix3DH rasterToCamera_;
  mutable CMatrix3DH worldToRaster_;
};

#endif
