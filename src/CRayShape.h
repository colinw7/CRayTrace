#ifndef CRAY_SHAPE_H
#define CRAY_SHAPE_H

#include <accessor.h>
#include <CRefPtr.h>
#include <CBBox3D.h>
#include <CRay.h>
#include <CRayHitData.h>
#include <CRaySimpleTexture.h>
#include <CRayImageTexture.h>
#include <CImageLib.h>

class CRayShape {
 public:
  CRayShape();

  virtual ~CRayShape() { }

  virtual CBBox3D getBBox() const = 0;

  virtual void setColor(const CRGBA &color) {
    texture_ = new CRaySimpleTexture(color);
  }

  CRGBA getColor(const CPoint3D &p=CPoint3D()) const;

  virtual void setTexture(CRayTexture *texture) {
    texture_ = texture;
  }

  virtual void setImage(CImagePtr image) {
    texture_ = new CRayImageTexture(image);
  }

  ACCESSOR(Id          , std::string, id          )
  ACCESSOR(Alpha       , double     , alpha       )
  ACCESSOR(Reflect     , double     , reflect     )
  ACCESSOR(Refract     , double     , refract     )
  ACCESSOR(RefractIndex, double     , refractIndex)
  ACCESSOR(IgnoreLight , bool       , ignoreLight )

  virtual bool hit(const CRay &ray, double tmin, double tmax, CRayHitData &hit_data) const {
    return hit(ray, tmin, tmax, &hit_data);
  }

  virtual bool hit(const CRay &ray, double tmin, double tmax) const {
    return hit(ray, tmin, tmax, NULL);
  }

  virtual bool hit(const CRay &ray, double tmin, double tmax, CRayHitData *hit_data) const = 0;

  virtual CVector3D pointNormal(const CPoint3D &point) const = 0;

  virtual CVector2D pointToSurfaceVector(const CPoint3D &point) const = 0;

  virtual CRGBA textureValue(const CPoint3D &p) const {
    return texture_->value(p);
  }

  virtual CRGBA textureValue(const CVector2D &uv) const {
    return texture_->value(uv);
  }

  virtual void setPosition(const CPoint3D &) {
    std::cerr << "setPosition not implemented" << std::endl;
  }

  virtual CPoint3D getPosition() const { return CPoint3D(0,0,0); }

  virtual void translate(const CPoint3D &) {
    std::cerr << "translate not implemented" << std::endl;
  }

  virtual void scale(const CPoint3D &) {
    std::cerr << "scale not implemented" << std::endl;
  }

  virtual void rotate(const CPoint3D &) {
    std::cerr << "rotate not implemented" << std::endl;
  }

 protected:
  std::string          id_;
  CRefPtr<CRayTexture> texture_;
  double               alpha_        { 1.0 };
  double               reflect_      { 0.0 };
  double               refract_      { 0.0 };
  double               refractIndex_ { 1.0 };
  bool                 ignoreLight_  { false };
};

#endif
