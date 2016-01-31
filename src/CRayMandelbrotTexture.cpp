#include <CRayMandelbrotTexture.h>
#include <CPointFractal.h>

CRayMandelbrotTexture::
CRayMandelbrotTexture()
{
  xmin_ = mandelbrot_.getXMin();
  ymin_ = mandelbrot_.getYMin();
  xmax_ = mandelbrot_.getXMax();
  ymax_ = mandelbrot_.getYMax();
}

CRGBA
CRayMandelbrotTexture::
value(const CVector2D &uv) const
{
  double x = (xmax_ - xmin_)*uv.getX() + xmin_;
  double y = (ymax_ - ymin_)*uv.getY() + ymin_;

  int colorInd = mandelbrot_.calc(x, y, 256);

  if (colorInd == 0) return CRGBA(0,0,0,0);

  return colors_.getColor(colorInd);
}
