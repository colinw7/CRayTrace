#ifndef CRAY_TRACE_H
#define CRAY_TRACE_H

#include <CPoint3D.h>
#include <CMatrix3DH.h>
#include <CBBox3D.h>
#include <COctTree.h>
#include <CRGBA.h>
#include <CRay.h>

#include <CRayTraceShapeData.h>

class CRayShape;
class CRaySphere;
class CRayCone;
class CRayCylinder;
class CRayHyperboloid;
class CRayParaboloid;
class CRayDisk;
class CRayTriangle;
class CRayCube;
class CRayBox;
class CRayPlane;
class CRayTraceCamera;
class CGeomScene3D;
class CGeomObject3D;
class CSampleMultiJitter;
class CRayTraceThread;
class CRayTraceLight;

// render interface
//  . set size
//  . clear
//  . draw point
class CRayTraceRenderer {
 public:
  virtual ~CRayTraceRenderer() { }

  virtual void setSize(uint w, uint h) = 0;

  virtual void begin() { }

  virtual void clear(const CRGBA &bg) = 0;

  virtual void drawPoint(int x, int y, const CRGBA &color) = 0;

  virtual void end() { }
};

//------

struct CRayTraceWindow {
  uint xmin { 0 }, ymin { 0 }, xmax { 100 }, ymax { 100 };
  uint x { 0 }, y { 0 }, width { 100 }, height { 100 };
  uint hits { 0 };

  CRayTraceWindow() {
    init(0, 0, 100, 100);
  }

  void init(uint xmin_, uint ymin_, uint xmax_, uint ymax_) {
    hits = 0;

    xmin = xmin_; xmax = xmax_;
    ymin = ymin_; ymax = ymax_;

    x = xmin; y = ymin;

    width  = xmax - xmin + 1;
    height = ymax - ymin + 1;
  }

  void step() {
    ++x;

    if (x > xmax) {
      x = xmin;

      ++y;
    }
  }

  bool done() const {
    return (y > ymax);
  }

  uint size() const {
    return width*height;
  }

  void traceStart() const {
    if (x != xmin) return;
    uint i = y*width + x;
    uint n = size();
    printf("\b\b\b\b\b\b\b\b");
    printf("%03d(%03d)", int(100.0*i/n), int(100.0*hits/n));
    fflush(stdout);
  }

  void traceEnd() const {
    if (x != xmin) return;
    printf("\b\b\b\b\b\b\b\b");
    fflush(stdout);
  }
};

//------

// ray trace
class CRayTrace {
 public:
  // hit information
  class HitData {
   public:
    // compare functor for sort
    class Compare {
      public:
       int operator()(const HitData &a, const HitData &b) {
         return (a.t_ < b.t_);
       }
    };

   public:
    HitData() { }

    HitData(CRayShape *shape, double t) :
     set_(true), shape_(shape), t_(t) {
    }

    ACCESSOR (Set  , bool     , set)
    PACCESSOR(Shape, CRayShape, shape)
    ACCESSOR (T    , double   , t)

    void updateShape(CRayShape *shape, double t) {
      if (! set_ || t < t_) {
        set_   = true;
        shape_ = shape;
        t_     = t;
      }
    }

   private:
    bool       set_   { false };
    CRayShape *shape_ { nullptr };
    double     t_     { 0.0 };
  };

  typedef std::vector<CRayTraceLight *> LightList;
  typedef std::vector<CRayShape *>      ShapeList;

 private:
  typedef COctTree<CRayShape,CBBox3D,double> OctTree;

 public:
  CRayTrace();

  virtual ~CRayTrace();

  PACCESSOR(Renderer     , CRayTraceRenderer, renderer)
  PACCESSOR(Camera       , CRayTraceCamera  , camera)
  PACCESSOR(OctTree      , OctTree          , octTree)
  ACCESSOR (Width        , uint             , width)
  ACCESSOR (Height       , uint             , height)
  ACCESSOR (NumSamples   , uint             , num_samples)
  ACCESSOR (MinT         , double           , minT)
  ACCESSOR (MaxT         , double           , maxT)
  ACCESSOR (Bg           , CRGBA            , bg)
  ACCESSOR (Fg           , CRGBA            , fg)
  ACCESSOR (ReflectDepth , uint             , reflect_depth)
  ACCESSOR (RefractDepth , uint             , refract_depth)
  ACCESSOR (AlphaDepth   , uint             , alpha_depth)
  ACCESSOR (SmoothNormals, bool             , smooth_normals)
  ACCESSOR (Changed      , bool             , changed)
  ACCESSOR (Trace        , bool             , trace)

  virtual void setSize(uint width, uint height);

  //---

  bool addFile(const std::string &filename);

  CRaySphere *addSphere(double radius, const CRayTraceShapeData &shape_data);

  CRayCone *addCone(double radius, double height, const CRayTraceShapeData &shape_data);

  CRayCylinder *addCylinder(double radius, double height, const CRayTraceShapeData &shape_data);

  CRayHyperboloid *addHyperboloid(const CPoint3D &point1, const CPoint3D &point2,
                                  const CRayTraceShapeData &shape_data);

  CRayParaboloid *addParaboloid(double radius, double zmin, double zmax,
                                const CRayTraceShapeData &shape_data);

  CRayDisk *addDisk(double radius, double height, double inner_radius,
                    const CRayTraceShapeData &shape_data);

  CRayTriangle *addTriangle(const CPoint3D &point1, const CPoint3D &point2, const CPoint3D &point3,
                            const CRayTraceShapeData &shape_data);

  CRayCube *addCube(double size, const CRayTraceShapeData &shape_data);

  CRayBox *addBox(double xsize, double ysize, double zsize,
                  const CRayTraceShapeData &shape_data);

  CRayPlane *addPlane(const CPoint3D &p1, const CPoint3D &p2,
                      const CPoint3D &p3, const CRayTraceShapeData &shape_data);

  void addModel(const std::string &filename, double scale, bool auto_scale,
                const CPoint3D &translate, bool auto_translate,
                const CPoint3D &rotate, const CRayTraceShapeData &shape_data);

  void addScene(const CGeomScene3D &scene, double scale, bool auto_scale,
                const CPoint3D &translate, bool auto_translate,
                const CPoint3D &rotate, const CRayTraceShapeData &shape_data);

  void addObject(CGeomObject3D &object, double scale, bool auto_scale,
                 const CPoint3D &translate, bool auto_translate,
                 const CPoint3D &center, bool auto_center,
                 const CPoint3D &rotate, const CRayTraceShapeData &shape_data);

  void applyShapeData(CRayShape *shape, const CRayTraceShapeData &shape_data);

  const ShapeList &getShapes() const { return shapes_; }

  CRayShape *getShape(const std::string &name) const;
  CRayShape *getShape(int ind) const;

  //---

  CRayTraceLight *addLight(const CPoint3D &position);

  const LightList &getLights() const { return lights_; }

  CRayTraceLight *getLight(const std::string &name) const;
  CRayTraceLight *getLight(int ind) const;

  //---

  void render();
  void render(CRayTraceRenderer *renderer);

  void renderThread(CRayTraceRenderer *renderer, int xmin, int ymin, int xmax, int ymax);

  void initRender();

  void stepRender();
  void stepRender(CRayTraceRenderer *renderer);
  void stepRender(CRayTraceRenderer *renderer, CRayTraceWindow &window);

  void termRender();

  bool raytrace(const CRay &ray, CRGBA &color, uint depth);

  CRGBA rayColor(const CRay &ray, const HitData &hitData, uint depth);

  CRGBA lightColor(const CPoint3D &point, const CVector3D &normal);

  bool getHitData(const CRay &ray, double minT, double maxT, HitData &hitData);

  void addTreeShapes(OctTree *t, const CRay &ray, const CPoint3D &p1, const CPoint3D &p2,
                     double minT, double maxT, HitData &hitData);

  void updateHitData(CRayShape *shape, const CRay &ray, double minT, double maxT, HitData &hitData);

  void drawLights();

 private:
  bool renderSimple();
  bool renderSampled();

  void nextSimple (CRayTraceRenderer *renderer, CRayTraceWindow &window);
  void nextSampled(CRayTraceRenderer *renderer, CRayTraceWindow &window);

 private:
  typedef std::vector<CRayTraceThread *> ThreadList;

  CRayTraceRenderer *  renderer_ { nullptr };
  CRayTraceCamera *    camera_ { nullptr };
  ShapeList            shapes_;
  OctTree *            octTree_ { nullptr };
  uint                 width_ { 500 }, height_ { 500 };
  uint                 num_samples_ { 0 };
  double               minT_ { 1E-10 }, maxT_ { 1E50 };
  LightList            lights_;
  CRGBA                bg_ { 0.0, 0.0, 0.0 };
  CRGBA                fg_ { 0.2, 0.2, 0.2 };
  uint                 reflect_depth_ { 1 };
  uint                 refract_depth_ { 2 };
  uint                 alpha_depth_ { 2 };
  bool                 smooth_normals_ { false };
  bool                 changed_ { false };
  bool                 trace_ { false };
  bool                 sampled_ { false };
  CSampleMultiJitter * samples_ { nullptr };
  CRayTraceWindow      window_;
  ThreadList           threads_;
};

//------

#include <CThread.h>

class CRayTraceThread : public CThread {
 public:
  CRayTraceThread(CRayTrace *raytrace, CRayTraceRenderer *renderer) :
   raytrace_(raytrace), renderer_(renderer) {
  }

  void setWindow(int xmin, int ymin, int xmax, int ymax) {
    window_.init(xmin, ymin, xmax, ymax);
  }

  void *execute();

 private:
  CRayTrace         *raytrace_ { nullptr };
  CRayTraceRenderer *renderer_ { nullptr };
  CRayTraceWindow    window_;
};

#endif
