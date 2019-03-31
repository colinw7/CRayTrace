#ifndef Canvas_H
#define Canvas_H

#include <Color.h>
#include <vector>

namespace RayTrace {

class Canvas {
 public:
  Canvas(int w=0, int h=0) :
   w_(w), h_(h) {
    applySize();
  }

  int width () const { return w_; }
  int height() const { return h_; }

  Color pixel(int x, int y) {
    int i = y*w_ + x;

    if (i < 0 || i >= s_)
      return Color();

    return pixels_[i];
  }

  void setPixel(int x, int y, const Color &c) {
    int i = y*w_ + x;

    if (i < 0 || i >= s_)
      return;

    pixels_[i] = c;
  }

  void writePPM(std::ostream &os) const;

 private:
  void applySize() {
    s_ = w_*h_;

    pixels_.resize(s_);
  }

 private:
  using Pixels = std::vector<Color>;

  int    w_ { 0 };
  int    h_ { 0 };
  Pixels pixels_;

  mutable int s_ { 0 };
};

}

#endif
