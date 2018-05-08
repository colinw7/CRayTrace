#include <CQMainWindow.h>

class CQRayTraceCanvas;
class CRayTrace;
class CImageRayTraceRenderer;
class CQScrolledCommand;
class QPainter;

class CQRayTrace : public CQMainWindow {
  Q_OBJECT

 public:
  CQRayTrace();

  virtual ~CQRayTrace();

  QSize sizeHint() const { return QSize(500, 500); }

  void createMenus();

  QWidget *createCentralWidget();

  void setTrace(bool trace);
  void addFile(const std::string &fileName);
  void setNumSamples(int num_samples);

  void draw(QPainter *painter);

  void checkChanged();

 private slots:
  void executeCommand(const QString &);

 private:
  static void clOutputProc(const char *str, void *data);
  static void clCommandTermProc(void *data);

 private:
  CRayTrace              *raytrace_ { nullptr };
  CImageRayTraceRenderer *renderer_ { nullptr };
  bool                    rendered_ { false };
  CQRayTraceCanvas       *canvas_   { nullptr };
  CQScrolledCommand      *command_  { nullptr };
};
