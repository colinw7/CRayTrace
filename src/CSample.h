#ifndef CSAMPLE_H
#define CSAMPLE_H

#include "CVector2D.h"

class CSample {
 protected:
  CVector2D *samples_;
  int        num_samples_;

 public:
  CSample(int num_samples);

  virtual ~CSample();

  void init();

  virtual void calc() = 0;

  double getX(int i) { return samples_[i].getX(); }
  double getY(int i) { return samples_[i].getY(); }
};

class CSampleRandom {
 public:
  void calc(CVector2D *samples, int num_samples);
  void calc(double *samples, int num_samples);
};

class CSampleJitter {
 public:
  void calc(CVector2D *samples, int num_samples);
  void calc(double *samples, int num_samples);
};

class CSampleNRooks {
 public:
  void calc(CVector2D *samples, int num_samples);
};

class CSampleMultiJitter : public CSample {
 public:
  CSampleMultiJitter(int num_samples) :
   CSample(num_samples) {
  }

  void calc();
};

class CSampleShuffle {
 public:
  void calc(CVector2D *samples, int num_samples);
  void calc(double *samples, int num_samples);
};

class CSampleBoxFilter {
 public:
  void calc(CVector2D *samples, int num_samples);
};

class CSampleTentFilter {
 public:
  void calc(CVector2D *samples, int num_samples);
};

class CSampleCubicSplineFilter {
 public:
  void calc(CVector2D *samples, int num_samples);

 private:
  double solve(double r) {
    double u = r;
    for (int i = 0; i < 5; ++i)
      u = (11*r + u*u*(6 + u*(8 - 9*u)))/
          (4 + 12*u*(1 + u*(1 - u)));
    return u;
  }

  double cubicFilter(double x) {
    if      (x < 1.0/24.0)
      return pow(24*x, 0.25) - 2;
    else if (x < 0.5)
      return solve(24*(x - 1.0/24.0)/11) - 1;
    else if (x < 23.0/24.0)
      return 1 - solve(24*(23.0/24.0 - x)/11);
    else
      return 2 - pow(24*(1 - x), 0.25);
  }
};

#endif
