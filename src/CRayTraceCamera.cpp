#include <CRayTraceCamera.h>
#include <CRayTrace.h>

CRayTraceCamera::
CRayTraceCamera(CRayTrace *raytrace) :
 raytrace_(raytrace)
{
  setPosition(CPoint3D (0.5,0.5,-1.0));
  setLookAt  (CPoint3D (0.5,0.5, 0.0));
  setUp      (CVector3D(0.0,1.0, 0.0));
}

void
CRayTraceCamera::
init()
{
  valid_ = true;

  double aspect = 1.0;

  double screen[4];

  if (aspect >= 1.0) {
    screen[0] = -aspect;
    screen[1] =  aspect;
    screen[2] = -1.0;
    screen[3] =  1.0;
  }
  else {
    double iaspect = 1.0/aspect;

    screen[0] = -1.0;
    screen[1] =  1.0;
    screen[2] = -iaspect;
    screen[3] =  iaspect;
  }

  double z1 = getZ1();
  double z2 = getZ2();

  cameraToWorld_.setLookAt(getPosition(), getLookAt(), getUp());

  if (! cameraToWorld_.invert(worldToCamera_))
    valid_ = false;

  screenToRaster_ =
    CMatrix3DH::scale(raytrace_->getWidth () - 1.0, raytrace_->getHeight() - 1.0, 1.0)*
    CMatrix3DH::scale(1.0/(screen[1] - screen[0]), 1.0/(screen[2] - screen[3]), 1.0)*
    CMatrix3DH::translation(-screen[0], -screen[3], 0.0);

  if (! screenToRaster_.invert(rasterToScreen_))
    valid_ = false;

  if (perspective_) {
    double iz21 = 1.0/(z2 - z1);
    double itf2 = 1.0/tan(0.5*CMathGen::DegToRad(fov_));

    cameraToScreen_ =
      CMatrix3DH(itf2, 0.0 ,     0.0,         0.0,
                 0.0 , itf2,     0.0,         0.0,
                 0.0 , 0.0 , z2*iz21, -z2*z1*iz21,
                 0.0 , 0.0 ,     1.0,         0.0);
  }
  else {
    double iz21 = 1.0/(z2 - z1);

    cameraToScreen_ =
      CMatrix3DH(1.0 , 0.0 ,  0.0, 0.0,
                 0.0 , 1.0 ,  0.0, 0.0,
                 0.0 , 0.0 , iz21, -z1*iz21,
                 0.0 , 0.0 ,  0.0, 1.0);
  }

  if (! cameraToScreen_.invert(screenToCamera_))
    valid_ = false;

  worldToScreen_  = cameraToScreen_*worldToCamera_;
  rasterToCamera_ = screenToCamera_*rasterToScreen_;
  worldToRaster_  = screenToRaster_*worldToScreen_;
}

CRay
CRayTraceCamera::
getRay(double x, double y) const
{
  CPoint3D rp(x, y, 0);

  CPoint3D sp = rasterToCamera_.multiplyPoint(rp);

  CPoint3D ro = sp;

  CVector3D rd;

  if (perspective_)
    rd = CVector3D(sp).unit();
  else
    rd = CVector3D(0,0,1);

  CPoint3D l1 = cameraToWorld_.multiplyPoint(ro);
  CPoint3D l2 = cameraToWorld_.multiplyPoint(ro + rd);

  return CRay(l1, l2);
}

CPoint3D
CRayTraceCamera::
worldToRaster(const CPoint3D &p) const
{
  return worldToRaster_.multiplyPoint(p);
}
