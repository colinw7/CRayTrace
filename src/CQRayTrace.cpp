#include "CQRayTrace.h"

#include <QApplication>
#include <QMenu>
#include <QVBoxLayout>
#include <QPainter>
#include <QTimer>

#include <CRayTrace.h>

using std::string;
using std::vector;

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
  QApplication app(argc, argv);

  uint num_samples = 0;
  bool smooth      = false;
  bool trace       = false;

  vector<string> filenames;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (strcmp(&argv[i][1], "sample") == 0)
        num_samples = 4;
      else if (strcmp(&argv[i][1], "smooth") == 0)
        smooth = true;
      else if (strcmp(&argv[i][1], "trace") == 0)
        trace = true;
      else
        std::cerr << "Unknown option " << argv[i] << std::endl;
    }
    else
      filenames.push_back(argv[i]);
  }

  CQRayTrace *qraytrace = new CQRayTrace;

  qraytrace->init();

  CRayTrace *raytrace = qraytrace->getRayTrace();

  raytrace->setSmoothNormals(smooth);

  raytrace->setTrace(trace);

  raytrace->setNumSamples(num_samples);

  qraytrace->show();

  vector<string>::const_iterator p1 = filenames.begin();
  vector<string>::const_iterator p2 = filenames.end  ();

  for ( ; p1 != p2; ++p1)
    raytrace->addFile(*p1);

  CQRayTraceCanvas *canvas = qraytrace->getCanvas();

  qraytrace->initSize(canvas->width(), canvas->height());

  return app.exec();
}

//-------------

CQRayTrace::
CQRayTrace() :
 QMainWindow()
{
  raytrace_ = new CRayTrace;

  timer_ = new QTimer;

  QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(updateSlot()));

  timer_->start(1);
}

CQRayTrace::
~CQRayTrace()
{
  delete raytrace_;
}

void
CQRayTrace::
init()
{
  QWidget *w = createCentralWidget();

  if (w)
    setCentralWidget(w);

  createMenus();

  setWindowTitle("CQRayTrace");
}

void
CQRayTrace::
createMenus()
{
  QMenu *fileMenu = new QMenu("&File", this);

  //----

  QAction *quitItem = new QAction("&Quit", fileMenu);

  quitItem->setShortcut(QString("Ctrl+Q"));
  quitItem->setStatusTip("Quit the application");

  connect(quitItem, SIGNAL(triggered()), this, SLOT(close()));
}

QWidget *
CQRayTrace::
createCentralWidget()
{
  QWidget *widget = new QWidget;

  QVBoxLayout *vlayout = new QVBoxLayout(widget);

  vlayout->setMargin(0); vlayout->setSpacing(0);

  canvas_ = new CQRayTraceCanvas(this);

  canvas_->setMinimumHeight(500);
  canvas_->setMaximumHeight(500);

  vlayout->addWidget(canvas_);

  renderer_ = new CQRayTraceCanvasRenderer(canvas_);

  return widget;
}

void
CQRayTrace::
initSize(int w, int h)
{
  raytrace_->setSize(w, h);

  raytrace_->initRender();

  renderer_->setSize(w, h);

  renderer_->clear(CRGBA(0,0,0,1));
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

  for (uint i = 0; i < 256; ++i)
    raytrace_->stepRender(renderer_);

  canvas_->update();

  timer_->start(1);
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
