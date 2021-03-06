#ifndef CRAY_IMAGE_TEXTURE_H
#define CRAY_IMAGE_TEXTURE_H

#include <CImagePtr.h>
#include <CRayTexture.h>

class CRayImageTexture : public CRayTexture {
 public:
  CRayImageTexture(CImagePtr image);

  virtual ~CRayImageTexture();

  virtual CRGBA value(const CVector2D &uv) const;

  virtual bool isPointTexture() const { return false; }

 private:
  CImagePtr image_;
};

#endif
