#ifndef CQRayTrace_H
#define CQRayTrace_H

#include <CQMainWindow.h>

class CQRayTraceCanvas;
class CQRayTraceCanvasRenderer;
class CQRayTraceCamera;
class CQRayTraceLight;
class CQRayTraceShape;
class CQPropertyTree;
class CRayTrace;
class CRayTraceCamera;
class CRayTraceLight;
class CRayShape;
class QTimer;

class CQRayTrace : public CQMainWindow {
  Q_OBJECT

  Q_PROPERTY(int    width         READ width)
  Q_PROPERTY(int    height        READ height)
  Q_PROPERTY(int    numSamples    READ numSamples      WRITE setNumSamples)
  Q_PROPERTY(double minT          READ minT)
  Q_PROPERTY(double maxT          READ maxT)
  Q_PROPERTY(QColor bg            READ bg              WRITE setBg)
  Q_PROPERTY(QColor fg            READ fg              WRITE setFg)
  Q_PROPERTY(int    reflectDepth  READ reflectDepth    WRITE setReflectDepth)
  Q_PROPERTY(int    refractDepth  READ refractDepth    WRITE setRefractDepth)
  Q_PROPERTY(int    alphaDepth    READ alphaDepth      WRITE setAlphaDepth)
  Q_PROPERTY(bool   smoothNormals READ isSmoothNormals WRITE setSmoothNormals)
  Q_PROPERTY(bool   changed       READ isChanged)
  Q_PROPERTY(bool   trace         READ isTrace         WRITE setTrace)

 public:
  CQRayTrace(int width, int height);

  virtual ~CQRayTrace();

  int width() const;
  int height() const;

  int numSamples() const;
  void setNumSamples(int i);

  double minT() const;
  double maxT() const;

  QColor bg() const;
  void setBg(const QColor &c);

  QColor fg() const;
  void setFg(const QColor &c);

  int reflectDepth() const;
  void setReflectDepth(int i);

  int refractDepth() const;
  void setRefractDepth(int i);

  int alphaDepth() const;
  void setAlphaDepth(int i);

  bool isSmoothNormals() const;
  void setSmoothNormals(bool b);

  bool isChanged() const;

  bool isTrace() const;
  void setTrace(bool b);

  void createMenus() override;

  void createDockWindows() override;

  QWidget *createCentralWidget() override;

  void initTerm() override;

  CRayTrace *getRayTrace() const { return raytrace_; }

  CQRayTraceCanvas *getCanvas() const { return canvas_; }

  void init();

  void draw(QPainter *painter);

  void checkChanged();

  QSize sizeHint() const { return QSize(800, 800); }

 private slots:
  void updateSlot();

  void redrawSlot();

 private:
  typedef std::vector<CQRayTraceLight *> Lights;
  typedef std::vector<CQRayTraceShape *> Shapes;

  int                       width_    { 800 };
  int                       height_   { 800 };
  CRayTrace*                raytrace_ { nullptr };
  bool                      rendered_ { false };
  CQRayTraceCanvas*         canvas_   { nullptr };
  CQRayTraceCanvasRenderer* renderer_ { nullptr };
  CQRayTraceCamera*         camera_   { nullptr };
  Lights                    lights_;
  Shapes                    shapes_;
  CQPropertyTree*           tree_     { nullptr };
  QTimer*                   timer_    { nullptr };
  int                       steps_    { 64 };
  bool                      threaded_ { true };
};

//------

class CQRayTraceCamera : public QObject {
  Q_OBJECT

  Q_PROPERTY(double z1          READ z1            WRITE setZ1)
  Q_PROPERTY(double z2          READ z2            WRITE setZ2)
  Q_PROPERTY(bool   perspective READ isPerspective WRITE setPerspective)
  Q_PROPERTY(double x           READ x             WRITE setX)
  Q_PROPERTY(double y           READ y             WRITE setY)
  Q_PROPERTY(double z           READ z             WRITE setZ)
  Q_PROPERTY(double lookX       READ lookX         WRITE setLookX)
  Q_PROPERTY(double lookY       READ lookY         WRITE setLookY)
  Q_PROPERTY(double lookZ       READ lookZ         WRITE setLookZ)
  Q_PROPERTY(double upX         READ upX           WRITE setUpX)
  Q_PROPERTY(double upY         READ upY           WRITE setUpY)
  Q_PROPERTY(double upZ         READ upZ           WRITE setUpZ)
  Q_PROPERTY(double fov         READ fov           WRITE setFov)

 public:
  CQRayTraceCamera(CQRayTrace *raytrace);

  double z1() const;
  void setZ1(double r);

  double z2() const;
  void setZ2(double r);

  bool isPerspective() const;
  void setPerspective(bool b);

  double x() const;
  void setX(double r);

  double y() const;
  void setY(double r);

  double z() const;
  void setZ(double r);

  double lookX() const;
  void setLookX(double r);

  double lookY() const;
  void setLookY(double r);

  double lookZ() const;
  void setLookZ(double r);

  double upX() const;
  void setUpX(double r);

  double upY() const;
  void setUpY(double r);

  double upZ() const;
  void setUpZ(double r);

  double fov() const;
  void setFov(double r);

 private:
  CRayTraceCamera *camera() const;

 private:
  CQRayTrace *raytrace_ { nullptr };
};

//------

class CQRayTraceLight : public QObject {
  Q_OBJECT

  Q_PROPERTY(double x     READ x     WRITE setX)
  Q_PROPERTY(double y     READ y     WRITE setY)
  Q_PROPERTY(double z     READ z     WRITE setZ)
  Q_PROPERTY(QColor color READ color WRITE setColor)

 public:
  CQRayTraceLight(CQRayTrace *raytrace, int ind);

  int ind() const { return ind_; }

  double x() const;
  void setX(double x) const;

  double y() const;
  void setY(double y) const;

  double z() const;
  void setZ(double z) const;

  QColor color() const;
  void setColor(const QColor &c) const;

 private:
  CRayTraceLight *light() const;

 public:
  CQRayTrace *raytrace_ { nullptr };
  int         ind_      { 0 };
};

//------

class CQRayTraceShape : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString id           READ id)
  Q_PROPERTY(double  alpha        READ alpha        WRITE setAlpha)
  Q_PROPERTY(double  reflect      READ reflect      WRITE setReflect)
  Q_PROPERTY(double  refract      READ refract      WRITE setRefract)
  Q_PROPERTY(double  refractIndex READ refractIndex WRITE setRefractIndex)
  Q_PROPERTY(bool    ignoreLight  READ ignoreLight  WRITE setIgnoreLight)
  Q_PROPERTY(QColor  color        READ color        WRITE setColor)

 public:
  CQRayTraceShape(CQRayTrace *raytrace, int ind);

  int ind() const { return ind_; }

  QString id() const;

  double alpha() const;
  void setAlpha(double r);

  double reflect() const;
  void setReflect(double r);

  double refract() const;
  void setRefract(double r);

  double refractIndex() const;
  void setRefractIndex(double r);

  bool ignoreLight() const;
  void setIgnoreLight(bool b);

  QColor color() const;
  void setColor(const QColor &c);

 private:
  CRayShape *shape() const;

 public:
  CQRayTrace *raytrace_ { nullptr };
  int         ind_      { 0 };
};

#endif
