#ifndef ObjYaml_H
#define ObjYaml_H

#include <string>

namespace RayTrace {

class ObjYaml {
 public:
  ObjYaml(const std::string &filename);

  void setDebug(bool debug=true) { debug_ = debug; }

  bool read();

 private:
  std::string filename_;
  bool        debug_     { false };
};

}

#endif
