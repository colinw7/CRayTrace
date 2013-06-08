#ifndef CRAY_HIT_DATA_H
#define CRAY_HIT_DATA_H

#include <CVector2D.h>
#include <CVector3D.h>
#include <CRGBA.h>

class CRayTexture;

struct CRayHitData {
  double    t;
  CVector3D normal;
  CRGBA     color;
};

struct CRayHitData1 {
  double       t;
  CVector3D    normal;
  CVector2D    uv;
  CVector3D    hit_point;
  CRayTexture *texture;
};

#endif
