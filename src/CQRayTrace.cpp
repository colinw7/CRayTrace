#include <CQRayTrace.h>
#include <CRayTrace.h>
#include <CRayTraceCamera.h>
#include <CRayTraceLight.h>
#include <CRayShape.h>

#include <CQPropertyTree.h>
#include <CQApp.h>
#include <CQMenu.h>
#include <CQDockWidget.h>
#include <CQUtil.h>
#include <CQUtilRGBA.h>

#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QTimer>

class CQRayTraceCanvas : public QWidget {
 private:
  CQRayTrace *raytrace_;

 public:
  CQRayTraceCanvas(CQRayTrace *parent);
 ~CQRayTraceCanvas();

  CQRayTrace *getRayTrace() { return raytrace_; }

  void resizeEvent(QResizeEvent *);

  void paintEvent(QPaintEvent *);
};

class CQRayTraceCanvasRenderer : public CRayTraceRenderer {
 public:
  CQRayTraceCanvasRenderer(CQRayTraceCanvas *canvas) :
   canvas_(canvas) {
  }

  CQRayTraceCanvas *canvas() const { return canvas_; }

  void setSize(uint w, uint h);

  void clear(const CRGBA &bg);

  void drawPoint(int x, int y, const CRGBA &color);

  const QImage &getImage() const { return image_; }

 private:
  CQRayTraceCanvas *canvas_;
  QImage            image_;
  int               w_, h_;
};

//------------

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  uint num_samples = 0;
  bool smooth      = false;
  bool trace       = false;
  int  width       = 800;
  int  height      = 800;

  std::vector<std::string> filenames;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (strcmp(&argv[i][1], "samples") == 0)
        num_samples = 4;
      else if (strcmp(&argv[i][1], "smooth") == 0)
        smooth = true;
      else if (strcmp(&argv[i][1], "trace") == 0)
        trace = true;
      else if (strcmp(&argv[i][1], "width") == 0) {
        ++i;

        width = atoi(argv[i]);
      }
      else if (strcmp(&argv[i][1], "height") == 0) {
        ++i;

        height = atoi(argv[i]);
      }
      else
        std::cerr << "Unknown option " << argv[i] << std::endl;
    }
    else
      filenames.push_back(argv[i]);
  }

  CQRayTrace *qraytrace = new CQRayTrace(width, height);

  qraytrace->CQMainWindow::init();

  CRayTrace *raytrace = qraytrace->getRayTrace();

  qraytrace->setSmoothNormals(smooth);
  qraytrace->setTrace(trace);
  qraytrace->setNumSamples(num_samples);

  qraytrace->show();

  for (const auto &filename : filenames)
    raytrace->addFile(filename);

  qraytrace->init();

  return app.exec();
}

//-------------

CQRayTrace::
CQRayTrace(int width, int height) :
 CQMainWindow("CQRayTrace"), width_(width), height_(height)
{
  raytrace_ = new CRayTrace;

  timer_ = new QTimer;

  QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(updateSlot()));

  timer_->start(1);

  camera_ = new CQRayTraceCamera(this);
}

CQRayTrace::
~CQRayTrace()
{
  delete raytrace_;
}

int
CQRayTrace::
width() const
{
  return raytrace_->getWidth();
}

int
CQRayTrace::
height() const
{
  return raytrace_->getHeight();
}

int
CQRayTrace::
numSamples() const
{
  return raytrace_->getNumSamples();
}

void
CQRayTrace::
setNumSamples(int i)
{
  raytrace_->setNumSamples(i);
}

double
CQRayTrace::
minT() const
{
  return raytrace_->getMinT();
}

double
CQRayTrace::
maxT() const
{
  return raytrace_->getMaxT();
}

QColor
CQRayTrace::
bg() const
{
  return CQUtil::toQColor(raytrace_->getBg());
}

void
CQRayTrace::
setBg(const QColor &c)
{
  raytrace_->setBg(CQUtil::colorToRGBA(c));
}

QColor
CQRayTrace::
fg() const
{
  return CQUtil::toQColor(raytrace_->getFg());
}

void
CQRayTrace::
setFg(const QColor &c)
{
  raytrace_->setFg(CQUtil::colorToRGBA(c));
}

int
CQRayTrace::
reflectDepth() const
{
  return raytrace_->getReflectDepth();
}

void
CQRayTrace::
setReflectDepth(int i)
{
  raytrace_->setReflectDepth(i);
}

int
CQRayTrace::
refractDepth() const
{
  return raytrace_->getRefractDepth();
}

void
CQRayTrace::
setRefractDepth(int i)
{
  raytrace_->setRefractDepth(i);
}

int
CQRayTrace::
alphaDepth() const
{
  return raytrace_->getAlphaDepth();
}

void
CQRayTrace::
setAlphaDepth(int i)
{
  raytrace_->setAlphaDepth(i);
}

bool
CQRayTrace::
isSmoothNormals() const
{
  return raytrace_->getSmoothNormals();
}

void
CQRayTrace::
setSmoothNormals(bool b)
{
  raytrace_->setSmoothNormals(b);
}

bool
CQRayTrace::
isChanged() const
{
  return raytrace_->getChanged();
}

bool
CQRayTrace::
isTrace() const
{
  return raytrace_->getTrace();
}

void
CQRayTrace::
setTrace(bool b)
{
  raytrace_->setTrace(b);
}

void
CQRayTrace::
createMenus()
{
  CQMenu *fileMenu = new CQMenu(this, "&File");

  //----

  CQMenuItem *quitItem = new CQMenuItem(fileMenu, "&Quit");

  quitItem->setShortcut("Ctrl+Q");
  quitItem->setStatusTip("Quit the application");

  connect(quitItem->getAction(), SIGNAL(triggered()), this, SLOT(close()));
}

void
CQRayTrace::
createDockWindows()
{
  QFrame *controlFrame = new QFrame;

  QVBoxLayout *controlLayout = new QVBoxLayout(controlFrame);

  //---

  QFrame *toolbar = new QFrame;

  QHBoxLayout *toolbarLayout = new QHBoxLayout(toolbar);

  QPushButton *redrawButton = new QPushButton("Redraw");

  connect(redrawButton, SIGNAL(clicked()), this, SLOT(redrawSlot()));

  toolbarLayout->addWidget(redrawButton);
  toolbarLayout->addStretch(1);

  controlLayout->addWidget(toolbar);

  //---

  tree_ = new CQPropertyTree;

  controlLayout->addWidget(tree_);

  //---

  CQDockWidget *controlDock = new CQDockWidget(this, "Control", controlFrame);

  controlDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
}

QWidget *
CQRayTrace::
createCentralWidget()
{
  QWidget *widget = new QWidget;

  QVBoxLayout *vlayout = new QVBoxLayout(widget);

  vlayout->setMargin(0); vlayout->setSpacing(0);

  canvas_ = new CQRayTraceCanvas(this);

  canvas_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  //canvas_->setMinimumWidth (width_ );
  //canvas_->setMaximumHeight(height_);

  vlayout->addWidget(canvas_);

  renderer_ = new CQRayTraceCanvasRenderer(canvas_);

  return widget;
}

void
CQRayTrace::
initTerm()
{
  resize(width_ + 200, height_);
}

void
CQRayTrace::
init()
{
  int w = canvas_->width ();
  int h = canvas_->height();

  raytrace_->setSize(w, h);

  if (! threaded_)
    raytrace_->initRender();

  renderer_->setSize(w, h);

  renderer_->clear(CRGBA(0,0,0,1));

  //------

  for (auto &light : lights_)
    delete light;

  lights_.clear();

  const CRayTrace::LightList &lights = raytrace_->getLights();

  for (std::size_t i = 0; i < lights.size(); ++i)
    lights_.push_back(new CQRayTraceLight(this, i));

  //------

  for (auto &shape : shapes_)
    delete shape;

  shapes_.clear();

  const CRayTrace::ShapeList &shapes = raytrace_->getShapes();

  for (std::size_t i = 0; i < shapes.size(); ++i)
    shapes_.push_back(new CQRayTraceShape(this, i));

  //------

  tree_->clear();

  tree_->addProperty("", this, "width");
  tree_->addProperty("", this, "height");
  tree_->addProperty("", this, "numSamples");
  tree_->addProperty("", this, "minT");
  tree_->addProperty("", this, "maxT");
  tree_->addProperty("", this, "bg");
  tree_->addProperty("", this, "fg");
  tree_->addProperty("", this, "reflectDepth");
  tree_->addProperty("", this, "refractDepth");
  tree_->addProperty("", this, "alphaDepth");
  tree_->addProperty("", this, "smoothNormals");
  tree_->addProperty("", this, "changed");
  tree_->addProperty("", this, "trace");

  tree_->addProperty("camera", camera_, "z1");
  tree_->addProperty("camera", camera_, "z2");
  tree_->addProperty("camera", camera_, "perspective");
  tree_->addProperty("camera", camera_, "x");
  tree_->addProperty("camera", camera_, "y");
  tree_->addProperty("camera", camera_, "z");
  tree_->addProperty("camera", camera_, "lookX");
  tree_->addProperty("camera", camera_, "lookY");
  tree_->addProperty("camera", camera_, "lookZ");
  tree_->addProperty("camera", camera_, "upX");
  tree_->addProperty("camera", camera_, "upY");
  tree_->addProperty("camera", camera_, "upZ");
  tree_->addProperty("camera", camera_, "fov");

  for (auto &light : lights_) {
    QString name = QString("lights/light%1").arg(light->ind());

    tree_->addProperty(name, light, "x");
    tree_->addProperty(name, light, "y");
    tree_->addProperty(name, light, "z");
    tree_->addProperty(name, light, "color");
  }

  for (auto &shape : shapes_) {
    QString name = QString("shapes/shape%1").arg(shape->ind());

    tree_->addProperty(name, shape, "id");
    tree_->addProperty(name, shape, "alpha");
    tree_->addProperty(name, shape, "reflect");
    tree_->addProperty(name, shape, "refract");
    tree_->addProperty(name, shape, "refractIndex");
    tree_->addProperty(name, shape, "ignoreLight");
    tree_->addProperty(name, shape, "color");
  }
}

void
CQRayTrace::
draw(QPainter *painter)
{
  const QImage &image = renderer_->getImage();

  painter->drawImage(QPoint(0, 0), image);
}

void
CQRayTrace::
updateSlot()
{
  timer_->stop();

  if (threaded_) {
    init();

    int w = raytrace_->getWidth ();
    int h = raytrace_->getHeight();

    int x1 = 0;
    int x2 = w/2;
    int x3 = w - 1;
    int y1 = 0;
    int y2 = h/4;
    int y3 = h/2;
    int y4 = 3*h/4;
    int y5 = h - 1;

    raytrace_->initRender();

    raytrace_->renderThread(renderer_, x1    , y1    , x2, y2);
    raytrace_->renderThread(renderer_, x2 + 1, y1    , x3, y2);
    raytrace_->renderThread(renderer_, x1    , y2 + 1, x2, y3);
    raytrace_->renderThread(renderer_, x2 + 1, y2 + 1, x3, y3);
    raytrace_->renderThread(renderer_, x1    , y3 + 1, x2, y4);
    raytrace_->renderThread(renderer_, x2 + 1, y3 + 1, x3, y4);
    raytrace_->renderThread(renderer_, x1    , y4 + 1, x2, y5);
    raytrace_->renderThread(renderer_, x2 + 1, y4 + 1, x3, y5);

    raytrace_->termRender();

    canvas_->update();
  }
  else {
    for (int i = 0; i < steps_; ++i)
      raytrace_->stepRender(renderer_);

    canvas_->update();

    timer_->start(1);
  }
}

void
CQRayTrace::
redrawSlot()
{
  updateSlot();
}

//-------------

CQRayTraceCanvas::
CQRayTraceCanvas(CQRayTrace *raytrace) :
 QWidget(raytrace), raytrace_(raytrace)
{
}

CQRayTraceCanvas::
~CQRayTraceCanvas()
{
}

void
CQRayTraceCanvas::
resizeEvent(QResizeEvent *)
{
}

void
CQRayTraceCanvas::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  raytrace_->draw(&painter);
}

//----------

void
CQRayTraceCanvasRenderer::
setSize(uint w, uint h)
{
  w_ = w;
  h_ = h;

  image_ = QImage(w_, h_, QImage::Format_ARGB32);
}

void
CQRayTraceCanvasRenderer::
clear(const CRGBA &bg)
{
  image_.fill(bg.getId());
}

void
CQRayTraceCanvasRenderer::
drawPoint(int x, int y, const CRGBA &rgba)
{
  image_.setPixel(x, y, rgba.getId());
}

//------

CQRayTraceCamera::
CQRayTraceCamera(CQRayTrace *raytrace) :
 raytrace_(raytrace)
{
}

double
CQRayTraceCamera::
z1() const
{
  return camera()->getZ1();
}

void
CQRayTraceCamera::
setZ1(double z)
{
  camera()->setZ1(z);
}

double
CQRayTraceCamera::
z2() const
{
  return camera()->getZ2();
}

void
CQRayTraceCamera::
setZ2(double z)
{
  camera()->setZ2(z);
}

bool
CQRayTraceCamera::
isPerspective() const
{
  return camera()->getPerspective();
}

void
CQRayTraceCamera::
setPerspective(bool b)
{
  camera()->setPerspective(b);
}

double
CQRayTraceCamera::
x() const
{
  return camera()->getPosition().getX();
}

void
CQRayTraceCamera::
setX(double x)
{
  CPoint3D p = camera()->getPosition();

  camera()->setPosition(p.setX(x));
}

double
CQRayTraceCamera::
y() const
{
  return camera()->getPosition().getY();
}

void
CQRayTraceCamera::
setY(double y)
{
  CPoint3D p = camera()->getPosition();

  camera()->setPosition(p.setY(y));
}

double
CQRayTraceCamera::
z() const
{
  return camera()->getPosition().getZ();
}

void
CQRayTraceCamera::
setZ(double z)
{
  CPoint3D p = camera()->getPosition();

  camera()->setPosition(p.setZ(z));
}

double
CQRayTraceCamera::
lookX() const
{
  return camera()->getLookAt().getX();
}

void
CQRayTraceCamera::
setLookX(double x)
{
  CPoint3D p = camera()->getLookAt();

  camera()->setLookAt(p.setX(x));
}

double
CQRayTraceCamera::
lookY() const
{
  return camera()->getLookAt().getY();
}

void
CQRayTraceCamera::
setLookY(double y)
{
  CPoint3D p = camera()->getLookAt();

  camera()->setLookAt(p.setY(y));
}

double
CQRayTraceCamera::
lookZ() const
{
  return camera()->getLookAt().getZ();
}

void
CQRayTraceCamera::
setLookZ(double z)
{
  CPoint3D p = camera()->getLookAt();

  camera()->setLookAt(p.setZ(z));
}

double
CQRayTraceCamera::
upX() const
{
  return camera()->getUp().getX();
}

void
CQRayTraceCamera::
setUpX(double x)
{
  CVector3D p = camera()->getUp();

  camera()->setUp(p.setX(x));
}

double
CQRayTraceCamera::
upY() const
{
  return camera()->getUp().getY();
}

void
CQRayTraceCamera::
setUpY(double y)
{
  CVector3D p = camera()->getUp();

  camera()->setUp(p.setY(y));
}

double
CQRayTraceCamera::
upZ() const
{
  return camera()->getUp().getZ();
}

void
CQRayTraceCamera::
setUpZ(double z)
{
  CVector3D p = camera()->getUp();

  camera()->setUp(p.setZ(z));
}

double
CQRayTraceCamera::
fov() const
{
  return camera()->getFieldOfView();
}

void
CQRayTraceCamera::
setFov(double r)
{
  camera()->setFieldOfView(r);
}

CRayTraceCamera *
CQRayTraceCamera::
camera() const
{
  return raytrace_->getRayTrace()->getCamera();
}

//------

CQRayTraceLight::
CQRayTraceLight(CQRayTrace *raytrace, int ind) :
 raytrace_(raytrace), ind_(ind)
{
}

double
CQRayTraceLight::
x() const
{
  return light()->getPosition().getX();
}

void
CQRayTraceLight::
setX(double x) const
{
  CPoint3D p = light()->getPosition();

  light()->setPosition(p.setX(x));
}

double
CQRayTraceLight::
y() const
{
  return light()->getPosition().getY();
}

void
CQRayTraceLight::
setY(double y) const
{
  CPoint3D p = light()->getPosition();

  light()->setPosition(p.setY(y));
}

double
CQRayTraceLight::
z() const
{
  return light()->getPosition().getZ();
}

void
CQRayTraceLight::
setZ(double z) const
{
  CPoint3D p = light()->getPosition();

  light()->setPosition(p.setZ(z));
}

QColor
CQRayTraceLight::
color() const
{
  return CQUtil::toQColor(light()->getAmbient());
}

void
CQRayTraceLight::
setColor(const QColor &c) const
{
  light()->setAmbient(CQUtil::colorToRGBA(c));
}

CRayTraceLight *
CQRayTraceLight::
light() const
{
  return raytrace_->getRayTrace()->getLight(ind_);
}

//------

CQRayTraceShape::
CQRayTraceShape(CQRayTrace *raytrace, int ind) :
 raytrace_(raytrace), ind_(ind)
{
}

QString
CQRayTraceShape::
id() const
{
  return shape()->getId().c_str();
}

double
CQRayTraceShape::
alpha() const
{
  return shape()->getAlpha();
}

void
CQRayTraceShape::
setAlpha(double r)
{
  shape()->setAlpha(r);
}

double
CQRayTraceShape::
reflect() const
{
  return shape()->getReflect();
}

void
CQRayTraceShape::
setReflect(double r)
{
  shape()->setReflect(r);
}

double
CQRayTraceShape::
refract() const
{
  return shape()->getRefract();
}

void
CQRayTraceShape::
setRefract(double r)
{
  shape()->setRefract(r);
}

double
CQRayTraceShape::
refractIndex() const
{
  return shape()->getRefractIndex();
}

void
CQRayTraceShape::
setRefractIndex(double r)
{
  shape()->setRefractIndex(r);
}

bool
CQRayTraceShape::
ignoreLight() const
{
  return shape()->getIgnoreLight();
}

void
CQRayTraceShape::
setIgnoreLight(bool b)
{
  shape()->setIgnoreLight(b);
}

CRayShape *
CQRayTraceShape::
shape() const
{
  return raytrace_->getRayTrace()->getShape(ind_);
}

QColor
CQRayTraceShape::
color() const
{
  return CQUtil::toQColor(shape()->getColor());
}

void
CQRayTraceShape::
setColor(const QColor &c)
{
  shape()->setColor(CQUtil::colorToRGBA(c));
}
