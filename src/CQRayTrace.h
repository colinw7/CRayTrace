#include <QMainWindow>

class QPainter;
class QTimer;
class CRayTrace;
class CQRayTraceCanvas;
class CQRayTraceCanvasRenderer;

class CQRayTrace : public QMainWindow {
  Q_OBJECT

 public:
  CQRayTrace();

  virtual ~CQRayTrace();

  QSize sizeHint() const { return QSize(500, 500); }

  void init();

  void createMenus();

  QWidget *createCentralWidget();

  CRayTrace *getRayTrace() const { return raytrace_; }

  CQRayTraceCanvas *getCanvas() const { return canvas_; }

  void initSize(int w, int h);

  void draw(QPainter *painter);

  void checkChanged();

 private slots:
  void updateSlot();

 private:
  CRayTrace                *raytrace_;
  bool                      rendered_;
  CQRayTraceCanvas         *canvas_;
  CQRayTraceCanvasRenderer *renderer_;
  QTimer                   *timer_;
};
