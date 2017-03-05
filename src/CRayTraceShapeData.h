#ifndef CRAY_TRACE_SHAPE_DATA_H
#define CRAY_TRACE_SHAPE_DATA_H

#include <CPoint3D.h>

struct CRayTraceShapeData {
  std::string id;
  std::string color;
  CPoint3D    translate;
  CPoint3D    scale;
  CPoint3D    rotate;
  bool        marble { false };
  bool        noise { false };
  bool        mandelbrot { false };
  std::string image;
  double      reflect { 0.0 };
  double      refract { 0.0 };
  double      refract_index { 1.0 };
  bool        ignore_light { false };

  CRayTraceShapeData() {
    init();
  }

  void init() {
    id            = "shape";
    color         = "white";
    translate     = CPoint3D(0,0,0);
    scale         = CPoint3D(1,1,1);
    rotate        = CPoint3D(0,0,0);
    marble        = false;
    noise         = false;
    mandelbrot    = false;
    image         = "";
    reflect       = 0.0;
    refract       = 0.0;
    refract_index = 1.0;
    ignore_light  = false;
  }
};

#endif
