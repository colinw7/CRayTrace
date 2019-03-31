#ifndef Light_H
#define Light_H

#include <Types.h>
#include <Point.h>
#include <Color.h>

namespace RayTrace {

class Light {
 public:
  Light() { }

  virtual ~Light() { }
};

}

#endif
