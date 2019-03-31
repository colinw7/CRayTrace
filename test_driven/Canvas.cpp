#include <Canvas.h>

namespace RayTrace {

void
Canvas::
writePPM(std::ostream &os) const
{
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

}
