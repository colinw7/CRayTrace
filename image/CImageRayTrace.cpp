#include <CImageRayTrace.h>

CImageRayTraceRenderer::
CImageRayTraceRenderer()
{
  image_ = CImageMgrInst->createImage();
}

CImageRayTraceRenderer::
~CImageRayTraceRenderer()
{
}

void
CImageRayTraceRenderer::
setSize(uint w, uint h)
{
  image_->setDataSize(w, h);
}

void
CImageRayTraceRenderer::
begin()
{
  CImage::setCombineEnabled(false);
}

void
CImageRayTraceRenderer::
clear(const CRGBA &bg)
{
  image_->setRGBAData(bg);
}

void
CImageRayTraceRenderer::
drawPoint(int x, int y, const CRGBA &fg)
{
  image_->setRGBAPixel(x, y, fg);
}

void
CImageRayTraceRenderer::
writeImage(const std::string &name)
{
  image_->writePNG(name);
}

CImagePtr
CImageRayTraceRenderer::
getImage() const
{
  return image_;
}
