#ifndef CRAY_TRACE_XML_H
#define CRAY_TRACE_XML_H

#include <CRayTraceShapeData.h>
#include <CPoint3D.h>

class CRayTrace;

class CRayTraceXML {
 private:
  CRayTrace *raytrace_;

 public:
  CRayTraceXML(CRayTrace *raytrace) :
   raytrace_(raytrace) {
  }

  bool read(const std::string &filename);

 private:
  bool shapeOption(CRayTraceShapeData &shape_data, const std::string &name,
                   const std::string &value) const;

  bool parseReal(const std::string &name, const std::string &value, double *real) const;
  bool parsePoint(const std::string &name, const std::string &value, CPoint3D &point) const;
};

#endif
