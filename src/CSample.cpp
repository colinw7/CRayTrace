#include <CSample.h>
#include <CVector2D.h>
#include <cstdlib>

CSample::
CSample(int num_samples) :
 num_samples_(num_samples)
{
  samples_ = new CVector2D [num_samples_];
}

CSample::
~CSample()
{
  delete [] samples_;
}

void
CSample::
init()
{
  calc();
}

void
CSampleRandom::
calc(CVector2D *samples, int num_samples)
{
  for (int i = 0; i < num_samples; ++i)
    samples[i].setXY(drand48(), drand48());
}

void
CSampleRandom::
calc(double *samples, int num_samples)
{
  for (int i = 0; i < num_samples; ++i)
    samples[i] = drand48();
}

void
CSampleJitter::
calc(CVector2D *samples, int num_samples)
{
  int num_samples1 = (int) sqrt(num_samples);

  for (int i = 0, k = 0; i < num_samples1; ++i)
    for (int j = 0; j < num_samples1; ++j, ++k)
      samples[k].setXY((i + drand48())/num_samples1,
                       (j + drand48())/num_samples1);
}

void
CSampleJitter::
calc(double *samples, int num_samples)
{
  for (int i = 0; i < num_samples; ++i)
    samples[i] = (i + drand48())/num_samples;
}

void
CSampleNRooks::
calc(CVector2D *samples, int num_samples)
{
  for (int i = 0; i < num_samples; ++i)
    samples[i].setXY((i + drand48())/num_samples,
                     (i + drand48())/num_samples);

  int    target;
  double x1, x2;

  for (int i = num_samples - 2; i >= 0; --i) {
    target = (int) (drand48()*i);

    x1 = samples[i + 1 ].getX();
    x2 = samples[target].getX();

    samples[i + 1 ].setX(x2);
    samples[target].setX(x1);
  }
}

void
CSampleMultiJitter::
calc()
{
  int num_samples1 = (int) sqrt(num_samples_);

  double width = 1.0/num_samples_;

  for (int i = 0, k = 0; i < num_samples1; ++i)
    for (int j = 0; j < num_samples1; ++j, ++k)
      samples_[k].setXY((k + drand48())*width,
                        (k + drand48())*width);

  int    k1;
  double x1, x2;

  for (int i = 0, k = 0; i < num_samples1; ++i)
    for (int j = 0, j1 = num_samples1 - 1; j < num_samples1; ++j, --j1, ++k) {
      k1 = k + (int) (drand48()*j1);

      x1 = samples_[k ].getX();
      x2 = samples_[k1].getX();

      samples_[k ].setX(x2);
      samples_[k1].setX(x1);
    }

  double y1, y2;

  for (int j = 0, j1 = num_samples1 - 1, k = 0; j < num_samples1; ++j, --j1)
    for (int i = 0; i < num_samples1; ++i, ++k) {
      k1 = k + ((int) (drand48()*j1))*num_samples1;

      y1 = samples_[k ].getY();
      y2 = samples_[k1].getY();

      samples_[k ].setY(y2);
      samples_[k1].setY(y1);
    }
}

void
CSampleShuffle::
calc(CVector2D *samples, int num_samples)
{
  int    target;
  double x1, x2;

  for (int i = num_samples - 2; i >= 0; --i) {
    target = (int) (drand48()*i);

    x1 = samples[i + 1 ].getX();
    x2 = samples[target].getX();

    samples[i + 1 ].setX(x2);
    samples[target].setX(x1);
  }
}

void
CSampleShuffle::
calc(double *samples, int num_samples)
{
  int target;

  for (int i = num_samples - 2; i >= 0; --i) {
    target = (int) (drand48()*i);

    std::swap(samples[i + 1], samples[target]);
  }
}

void
CSampleBoxFilter::
calc(CVector2D *samples, int num_samples)
{
  for (int i = 0; i < num_samples; ++i)
    samples[i].setXY(samples[i].getX() - 0.5, samples[i].getY() - 0.5);
}

void
CSampleTentFilter::
calc(CVector2D *samples, int num_samples)
{
  double x, y;

  for (int i = 0; i < num_samples; ++i) {
    x = samples[i].getX();
    y = samples[i].getY();

    if (x < 0.5)
      samples[i].setX(sqrt(2*x) - 1);
    else
      samples[i].setX(1 - sqrt(2 - 2*x));

    if (y < 0.5)
      samples[i].setY(sqrt(2*y) - 1);
    else
      samples[i].setY(1 - sqrt(2 - 2*y));
  }
}

void
CSampleCubicSplineFilter::
calc(CVector2D *samples, int num_samples)
{
  double x, y;

  for (int i = 0; i < num_samples; ++i) {
    x = samples[i].getX();
    y = samples[i].getY();

    samples[i].setXY(cubicFilter(x), cubicFilter(y));
  }
}
