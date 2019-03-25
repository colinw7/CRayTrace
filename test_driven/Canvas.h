#ifndef Canvas_H
#define Canvas_H

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

  void writePPM(std::ostream &os) const {
    os << "P3\n";
    os << w_ << " " << h_ << "\n";
    os << "255\n";

    char lastC = '\0';

    int i = 0;
    int n = 0;

    for (int y = 0; y < h_; ++y) {
      for (int x = 0; x < w_; ++x, ++i) {
        const Color &c = pixels_[i];

        if (lastC == '0')
          os << " ";

        os << c.redI() << " " << c.greenI() << " " << c.blueI();

        ++n;

        if (n >= 5) {
          n = 0;

          os << "\n";

          lastC = '\n';
        }
        else
          lastC = '0';
      }
    }

    if (lastC != '\n')
      os << "\n";
  }

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
