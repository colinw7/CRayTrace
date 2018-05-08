#include <CRayTraceRenderer.h>
#include <CPixelRenderer.h>

CRayTracePixelRenderer::
CRayTracePixelRenderer(CPixelRenderer *renderer) :
 renderer_(renderer)
{
}

void
CRayTracePixelRenderer::
setSize(uint /*w*/, uint /*h*/)
{
}

void
CRayTracePixelRenderer::
clear(const CRGBA &bg)
{
  renderer_->setForeground(bg);

  renderer_->fill();
}

void
CRayTracePixelRenderer::
drawPoint(int x, int y, const CRGBA &rgb)
{
  renderer_->setForeground(rgb);

  renderer_->drawPoint(CIPoint2D(x, y));
}
