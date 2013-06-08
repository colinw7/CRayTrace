#include <CRayTraceLight.h>
#include <CRayTrace.h>

using std::string;

CRayTraceLight::
CRayTraceLight(CRayTrace *raytrace, const string &name) :
 raytrace_(raytrace), name_(name), position_(0,0,0), ambient_(0.4, 0.4, 0.4)
{
}
