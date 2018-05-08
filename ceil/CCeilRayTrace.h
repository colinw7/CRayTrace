#ifndef CCEIL_RAYTRACE_H
#define CCEIL_RAYTRACE_H

class CRayTrace;

class CCeilRayTrace {
 private:
  CRayTrace *raytrace_;

 public:
  CCeilRayTrace(CRayTrace *raytrace);

  CRayTrace *getRayTrace() const { return raytrace_; }
};

#endif
