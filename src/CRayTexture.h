#ifndef CRAY_TEXTURE_H
#define CRAY_TEXTURE_H

#include <CRGBA.h>
#include <CVector2D.h>
#include <CVector3D.h>

class CRayTexture {
 public:
  virtual ~CRayTexture() { }

  virtual CRGBA value(const CPoint3D &) const {
    std::cerr << "CRayTexture::value(CPoint3D) not implemented" << std::endl;
    return CRGBA(0,0,0,0);
  }

  virtual CRGBA value(const CVector2D &) const {
    std::cerr << "CRayTexture::value(CVector2D) not implemented" << std::endl;
    return CRGBA(0,0,0,0);
  }

  virtual bool isPointTexture() const { return true; }
};

#endif
