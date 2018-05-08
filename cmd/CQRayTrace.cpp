#include <CQRayTrace.h>
#include <CImageRayTrace.h>
#include <CQCommand.h>
#include <CCeilL.h>
#include <CCeilRayTrace.h>

#include <CQApp.h>
#include <CQMenu.h>
#include <CQUtil.h>
#include <QVBoxLayout>
#include <QPainter>

class CQRayTraceCanvas : public QWidget {
 private:
  CQRayTrace *raytrace_;

 public:
  CQRayTraceCanvas(CQRayTrace *parent);
 ~CQRayTraceCanvas();

  void paintEvent(QPaintEvent *);
};

//------------

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  uint num_samples = 0;
  bool trace       = false;

  std::vector<std::string> filenames;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (strcmp(&argv[i][1], "sample") == 0)
        num_samples = 16;
      else if (strcmp(&argv[i][1], "trace") == 0)
        trace = true;
      else
        std::cerr << "Unknown option " << argv[i] << std::endl;
    }
    else
      filenames.push_back(argv[i]);
  }

  CQRayTrace *raytrace = new CQRayTrace;

  raytrace->init();

  raytrace->setTrace(trace);

  raytrace->setNumSamples(num_samples);

  raytrace->show();

  std::vector<std::string>::const_iterator p1 = filenames.begin();
  std::vector<std::string>::const_iterator p2 = filenames.end  ();

  for ( ; p1 != p2; ++p1)
    raytrace->addFile(*p1);

  return app.exec();
}

//-------------

CQRayTrace::
CQRayTrace() :
 CQMainWindow("CQRayTrace")
{
  raytrace_ = new CRayTrace;
  renderer_ = new CImageRayTraceRenderer;
  rendered_ = false;
}

CQRayTrace::
~CQRayTrace()
{
  delete raytrace_;
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

  connect(quitItem->getAction(), SIGNAL(triggered()),
          this, SLOT(close()));
}

QWidget *
CQRayTrace::
createCentralWidget()
{
  ClLanguageMgrInst->init(nullptr, nullptr);

  ClLanguageMgrInst->setOutputProc(clOutputProc, this);

  ClLanguageMgrInst->setCommandTermProc(clCommandTermProc, this);

  //ClParserInst->setDollarPrefix(true);

  //------

  QWidget *widget = new QWidget;

  QVBoxLayout *vlayout = new QVBoxLayout(widget);

  vlayout->setMargin(0); vlayout->setSpacing(0);

  canvas_ = new CQRayTraceCanvas(this);

  canvas_->setMinimumHeight(500);
  canvas_->setMaximumHeight(500);

  vlayout->addWidget(canvas_);

  command_ = new CQScrolledCommand;

  command_->getCommand()->setPrompt(ClLanguageMgrInst->getPrompt());

  connect(command_, SIGNAL(executeCommand(const QString &)),
          this, SLOT(executeCommand(const QString &)));

  command_->setMinimumHeight(200);
  command_->setMaximumHeight(200);

  vlayout->addWidget(command_);

  //------

  CCeilRayTrace *craytrace = new CCeilRayTrace(raytrace_);

  assert(craytrace);

  ClModuleMgrInst->importModule("raytrace");

  //------

  return widget;
}

void
CQRayTrace::
setTrace(bool trace)
{
  raytrace_->setTrace(trace);
}

void
CQRayTrace::
addFile(const std::string &fileName)
{
  //raytrace_->addFile(fileName);

  ClLanguageMgrInst->runFile(fileName);
}

void
CQRayTrace::
setNumSamples(int num_samples)
{
  raytrace_->setNumSamples(num_samples);
}

void
CQRayTrace::
draw(QPainter *painter)
{
  if (! rendered_) {
    raytrace_->setSize(canvas_->width(), canvas_->height());

    raytrace_->render(renderer_);

    rendered_ = true;
  }

  CImagePtr image = renderer_->getImage();

  painter->drawImage(QPoint(0, 0), CQUtil::toQImage(image));
}

void
CQRayTrace::
executeCommand(const QString &str)
{
  if (ClLanguageMgrInst->runCommand(str.toStdString())) {
    ClLanguageMgrInst->term();

    exit(ClLanguageMgrInst->getExitCode());
  }

  command_->getCommand()->setPrompt(ClLanguageMgrInst->getPrompt());
}

void
CQRayTrace::
checkChanged()
{
  if (raytrace_->getChanged()) {
    rendered_ = false;

    canvas_->update();

    QApplication::processEvents();
  }
}

void
CQRayTrace::
clOutputProc(const char *str, void *data)
{
  CQRayTrace *raytrace = static_cast<CQRayTrace *>(data);

  raytrace->command_->outputText(str);
}

void
CQRayTrace::
clCommandTermProc(void *data)
{
  CQRayTrace *raytrace = static_cast<CQRayTrace *>(data);

  raytrace->checkChanged();
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
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  raytrace_->draw(&painter);
}
