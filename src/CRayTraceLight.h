#ifndef CRAY_TRACE_LIGHT_H
#define CRAY_TRACE_LIGHT_H

#include <accessor.h>
#include <CPoint3D.h>
#include <CRGBA.h>

class CRayTrace;

class CRayTraceLight {
 public:
  CRayTraceLight(CRayTrace *raytrace, const std::string &name="light");

  ACCESSOR(Name    , std::string, name    )
  ACCESSOR(Position, CPoint3D   , position)
  ACCESSOR(Ambient , CRGBA      , ambient )

 private:
  CRayTrace   *raytrace_ { nullptr };
  std::string  name_;
  CPoint3D     position_;
  CRGBA        ambient_;
};

#endif
