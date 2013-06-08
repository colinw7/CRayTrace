#include <CRayImageTexture.h>
#include <CImageLib.h>

CRayImageTexture::
CRayImageTexture(CImagePtr image) :
 image_(image)
{
}

CRayImageTexture::
~CRayImageTexture()
{
}

CRGBA
CRayImageTexture::
value(const CVector2D &uv) const
{
  int x = int(uv.getX()*(image_->getWidth () - 1));
  int y = int(uv.getY()*(image_->getHeight() - 1));

  CRGBA rgba;

  image_->getRGBAPixel(x, y, rgba);

  return rgba;
}
