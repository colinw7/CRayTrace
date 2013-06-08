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
//class CGeomScene3D;
//class CGeomObject3D;
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

struct CRayTraceWindow {
  uint xmin, ymin, xmax, ymax;
  uint x, y, width, height;
  uint hits;

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

// ray trace
class CRayTrace {
 public:
  // hit information
  class HitData {
   private:
    bool       set_;
    CRayShape *shape_;
    double     t_;

   public:
    // compare functor for sort
    class Compare {
      public:
       int operator()(const HitData &a, const HitData &b) {
         return (a.t_ < b.t_);
       }
    };

   public:
    HitData() :
     set_(false), shape_(NULL), t_(0.0) {
    }

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
  };

 private:
  typedef std::vector<CRayShape *>           ShapeList;
  typedef std::vector<CRayTraceLight *>      LightList;
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

#if 0
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
#endif

  void applyShapeData(CRayShape *shape, const CRayTraceShapeData &shape_data);

  CRayTraceLight *addLight(const CPoint3D &position);

  CRayShape *getShape(const std::string &name) const;

  CRayTraceLight *getLight(const std::string &name) const;

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

  CRayTraceRenderer *  renderer_;
  CRayTraceCamera *    camera_;
  ShapeList            shapes_;
  OctTree *            octTree_;
  uint                 width_, height_;
  uint                 num_samples_;
  double               minT_, maxT_;
  LightList            lights_;
  CRGBA                bg_, fg_;
  uint                 reflect_depth_;
  uint                 refract_depth_;
  uint                 alpha_depth_;
  bool                 smooth_normals_;
  bool                 changed_;
  bool                 trace_;
  bool                 sampled_;
  CSampleMultiJitter * samples_;
  CRayTraceWindow      window_;
  ThreadList           threads_;
};

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
  CRayTrace         *raytrace_;
  CRayTraceRenderer *renderer_;
  CRayTraceWindow    window_;
};

#endif
