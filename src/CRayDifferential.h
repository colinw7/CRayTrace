#ifndef CRAY_DIFFERENTIAL_H
#define CRAY_DIFFERENTIAL_H

template<typename T>
class CRayDifferentialT : public CRayT<T> {
 private:
  bool     has_differentials_;
  CRayT<T> ray_x;
  CRayT<T> ray_y;

 public:
  CRayDifferentialT() :
   has_differentials_(false) {
  }

  CRayDifferentialT(const CPoint3DT<T> &origin,
                    const CVector3DT<T> &direction) :
   CRay(origin, direction), has_differentials_(false) {
  }
};

typedef CRayDifferentialT<double> CRayDifferential;

#endif
