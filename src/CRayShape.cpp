#include <CRayShape.h>

CRayShape::
CRayShape()
{
}

CRGBA
CRayShape::
getColor(const CPoint3D &p) const
{
  if (texture_.isValid()) {
    if (texture_->isPointTexture())
      return textureValue(p);

    CVector2D uv = pointToSurfaceVector(p);

    return textureValue(uv);
  }

  return CRGBA(1,1,1);
}
