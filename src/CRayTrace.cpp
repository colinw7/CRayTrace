#include <CRayTrace.h>
#include <CRayTraceCamera.h>
#include <CRayTraceLight.h>
#include <CRayTraceXML.h>

#include <CRayShapeLib.h>

#include <CRayNoiseTexture.h>
#include <CRayMarbleTexture.h>
#include <CRayMandelbrotTexture.h>

#include <CSample.h>

#include <CImageLib.h>

#include <CImport3DS.h>
#include <CImportV3D.h>
#include <CImportScene.h>

#include <CGeometry3D.h>
#include <CGeomScene3D.h>

#include <CStrUtil.h>
#include <CTransform2D.h>
#include <CRGBName.h>

CRayTrace::
CRayTrace()
{
  camera_ = new CRayTraceCamera(this);

  octTree_ = new OctTree(CBBox3D(-10, -10, -10, 10, 10, 10));
}

CRayTrace::
~CRayTrace()
{
  delete camera_;

  delete octTree_;

  for (auto &shape : shapes_)
    delete shape;
}

void
CRayTrace::
setSize(uint width, uint height)
{
  width_  = width;
  height_ = height;

  if (renderer_)
    renderer_->setSize(width_, height_);
}

bool
CRayTrace::
addFile(const std::string &filename)
{
  CRayTraceXML xml(this);

  return xml.read(filename);
}

CRaySphere *
CRayTrace::
addSphere(double radius, const CRayTraceShapeData &shape_data)
{
  CRaySphere *sphere = new CRaySphere(radius);

  shapes_.push_back(sphere);

  applyShapeData(sphere, shape_data);

  return sphere;
}

CRayCone *
CRayTrace::
addCone(double radius, double height, const CRayTraceShapeData &shape_data)
{
  CRayCone *cone = new CRayCone(radius, height);

  shapes_.push_back(cone);

  applyShapeData(cone, shape_data);

  return cone;
}

CRayCylinder *
CRayTrace::
addCylinder(double radius, double height, const CRayTraceShapeData &shape_data)
{
  CRayCylinder *cylinder = new CRayCylinder(radius, height);

  shapes_.push_back(cylinder);

  applyShapeData(cylinder, shape_data);

  return cylinder;
}

CRayHyperboloid *
CRayTrace::
addHyperboloid(const CPoint3D &point1, const CPoint3D &point2,
               const CRayTraceShapeData &shape_data)
{
  CRayHyperboloid *hyperboloid = new CRayHyperboloid(point1, point2);

  shapes_.push_back(hyperboloid);

  applyShapeData(hyperboloid, shape_data);

  return hyperboloid;
}

CRayParaboloid *
CRayTrace::
addParaboloid(double radius, double zmin, double zmax, const CRayTraceShapeData &shape_data)
{
  CRayParaboloid *paraboloid = new CRayParaboloid(radius, zmin, zmax);

  shapes_.push_back(paraboloid);

  applyShapeData(paraboloid, shape_data);

  return paraboloid;
}

CRayDisk *
CRayTrace::
addDisk(double radius, double height, double inner_radius, const CRayTraceShapeData &shape_data)
{
  CRayDisk *disk = new CRayDisk(radius, height, inner_radius);

  shapes_.push_back(disk);

  applyShapeData(disk, shape_data);

  return disk;
}

CRayTriangle *
CRayTrace::
addTriangle(const CPoint3D &point1, const CPoint3D &point2,
            const CPoint3D &point3, const CRayTraceShapeData &shape_data)
{
  CRayTriangle *triangle = new CRayTriangle(point1, point2, point3);

  shapes_.push_back(triangle);

  applyShapeData(triangle, shape_data);

  return triangle;
}

CRayCube *
CRayTrace::
addCube(double size, const CRayTraceShapeData &shape_data)
{
  CRayCube *cube = new CRayCube(size);

  shapes_.push_back(cube);

  applyShapeData(cube, shape_data);

  return cube;
}

CRayBox *
CRayTrace::
addBox(double xsize, double ysize, double zsize, const CRayTraceShapeData &shape_data)
{
  CRayBox *box = new CRayBox(xsize, ysize, zsize);

  shapes_.push_back(box);

  applyShapeData(box, shape_data);

  return box;
}

CRayPlane *
CRayTrace::
addPlane(const CPoint3D &p1, const CPoint3D &p2,
         const CPoint3D &p3, const CRayTraceShapeData &shape_data)
{
  CRayPlane *plane = new CRayPlane(p1, p2, p3);

  shapes_.push_back(plane);

  applyShapeData(plane, shape_data);

  return plane;
}

void
CRayTrace::
addModel(const std::string &filename, double scale, bool auto_scale,
         const CPoint3D &translate, bool auto_translate,
         const CPoint3D &rotate, const CRayTraceShapeData &shape_data)
{
  CFile file(filename);

  if (! file.exists()) {
    std::cerr << "File " << filename << " does not exist" << std::endl;
    return;
  }

  std::string suffix = file.getSuffix();

  suffix = CStrUtil::toLower(suffix);

  CGeomScene3D *scene = CGeometryInst->createScene3D();

  if      (suffix == "3ds") {
    CImport3DS import(scene);

    import.read(file);
  }
  else if (suffix == "v3d") {
    CImportV3D import(scene);

    import.read(file);
  }
  else if (suffix == "scene") {
    CImportScene import(scene);

    import.read(file);
  }
  else {
    std::cerr << "File " << filename << " not recognised" << std::endl;
    return;
  }

  addScene(*scene, scale, auto_scale, translate, auto_translate, rotate, shape_data);

  delete scene;
}

void
CRayTrace::
addScene(const CGeomScene3D &scene, double scale, bool auto_scale,
         const CPoint3D &translate, bool auto_translate,
         const CPoint3D &rotate, const CRayTraceShapeData &shape_data)
{
  CBBox3D bbox;

  scene.getBBox(bbox);

  std::cerr << "Scene  Orig BBox: " << bbox << std::endl;

  CPoint3D c = bbox.getCenter();

  CPoint3D translate1;

  if (auto_translate) {
    //CPoint3D pmax = bbox.getMax();

    translate1 = CPoint3D(0.5, 0.5, 1) - c;
  }
  else
    translate1 = translate;

  if (auto_scale) {
    CVector3D s = bbox.getSize();

    double xs = 1.0/s.getX();
    double ys = 1.0/s.getY();

    scale = std::min(xs, ys);
  }

  bbox.setMin((bbox.getMin() - c)*scale + c + translate1);
  bbox.setMax((bbox.getMax() - c)*scale + c + translate1);

  std::cerr << "Scene  New  BBox: " << bbox << std::endl;

  const CGeomScene3D::ObjectList &objects = scene.getObjects();

  for (const auto &object : objects)
    addObject(*object, scale, false, translate1, false, c, false, rotate, shape_data);
}

void
CRayTrace::
addObject(CGeomObject3D &object, double scale, bool auto_scale,
          const CPoint3D &translate, bool auto_translate,
          const CPoint3D &center, bool auto_center,
          const CPoint3D &rotate, const CRayTraceShapeData &shape_data)
{
  CBBox3D bbox;

  object.getModelBBox(bbox);

  std::cerr << "Object Orig BBox: " << bbox << std::endl;

  CPoint3D c;

  if (auto_center)
    c = bbox.getCenter();
  else
    c = center;

  CPoint3D translate1;

  if (auto_translate) {
    //CPoint3D pmax = bbox.getMax();

    translate1 = CPoint3D(0.5, 0.5, 1) - c;
  }
  else
    translate1 = translate;

  if (auto_scale) {
    CVector3D s = bbox.getSize();

    double xs = 1.0/s.getX();
    double ys = 1.0/s.getY();

    scale = std::min(xs, ys);
  }

  double xa = CMathGen::DegToRad(rotate.x);
  double ya = CMathGen::DegToRad(rotate.y);
  double za = CMathGen::DegToRad(rotate.z);

  CMatrix3D matrix1, matrix2, matrix3, matrix4;

  matrix1.setTranslation(-c);
  matrix2.setScale      (scale);
  matrix3.setXYZRotation(xa, ya, za);
  matrix4.setTranslation(c + translate1);

  CMatrix3D matrix = matrix4*matrix3*matrix2*matrix1;

  bbox.setMin(matrix.multiplyPoint(bbox.getMin()));
  bbox.setMax(matrix.multiplyPoint(bbox.getMax()));

  std::cerr << "Object New BBox: " << bbox << std::endl;

  const CGeomObject3D::FaceList &faces = object.getFaces();

  for (const auto &face : faces) {
    const CGeomFace3D::VertexList &vertices = face->getVertices();

    uint num_vertices = vertices.size();

    for (uint i = 0; i < num_vertices; ++i) {
      CGeomVertex3D &vertex = object.getVertex(vertices[i]);

      object.addVertexFace(vertices[i], face->getInd());

      CPoint3D point = vertex.getModel();

      point = matrix.multiplyPoint(point);

      vertex.setViewed(point);
    }
  }

  CRayTraceShapeData shape_data1 = shape_data;

  std::vector<CPoint3D>  points;
  std::vector<CVector3D> normals;

  for (const auto &face : faces) {
    const CRGBA &color = face->getMaterial().getDiffuse();

    shape_data1.color = color.stringEncode();

    const CGeomFace3D::VertexList &vertices = face->getVertices();

    uint num_vertices = vertices.size();

    if (num_vertices < 3) continue;

    points .resize(num_vertices);
    normals.resize(num_vertices);

    for (uint i = 0; i < num_vertices; ++i) {
      CGeomVertex3D &vertex = object.getVertex(vertices[i]);

      //points[i] = vertex.getModel();
      //points[i] = matrix.multiplyPoint(points[i]);

      //vertex.setViewed(points[i]);

      points[i] = vertex.getViewed();
    }

    CVector3D normal;

    if (face->getNormalSet())
      normal = face->getNormal();
    else
      face->calcNormal(normal);

    for (uint i = 0; i < num_vertices; ++i)
      normals[i] = object.getVertexFaceNormal(vertices[i]);

    for (uint i = 0; i < num_vertices - 2; ++i) {
      CRayTriangle *triangle1 =
        addTriangle(points[0], points[i + 1], points[i + 2], shape_data1);

      if (! smooth_normals_) {
        CVector3D tnormal = triangle1->getNormal();

        triangle1->setNormals(tnormal, tnormal, tnormal);
      }
      else
        triangle1->setNormals(normals[0], normals[i + 1], normals[i + 2]);

      //CRayTriangle *triangle2 =
      //  addTriangle(points[i + 2], points[i + 1], points[0], shape_data1);

      //if (! smooth_normals_)
      //  triangle2->setNormals(-tnormal, -tnormal, -tnormal);
      //else
      //  triangle1->setNormals(-normals[0], -normals[i + 1], -normals[i + 2]);
    }
  }
}

void
CRayTrace::
applyShapeData(CRayShape *shape, const CRayTraceShapeData &shape_data)
{
  shape->setId(shape_data.id);

  double r, g, b, a;

  CRGBName::lookup(shape_data.color, &r, &g, &b, &a);

  shape->setColor(CRGBA(r, g, b, a));

  if (shape_data.translate.x != 0 || shape_data.translate.y != 0 || shape_data.translate.z != 0)
    shape->translate(shape_data.translate);

  if (shape_data.scale.x != 1 || shape_data.scale.y != 1 || shape_data.scale.z != 1)
    shape->scale(shape_data.scale);

  if (shape_data.rotate.x != 0 || shape_data.rotate.y != 0 || shape_data.rotate.z != 0)
    shape->rotate(CPoint3D(CMathGen::DegToRad(shape_data.rotate.x),
                           CMathGen::DegToRad(shape_data.rotate.y),
                           CMathGen::DegToRad(shape_data.rotate.z)));

  if (shape_data.marble)
    shape->setTexture(new CRayMarbleTexture(.15, 5));

  if (shape_data.noise)
    shape->setTexture(new CRayNoiseTexture());

  if (shape_data.mandelbrot)
    shape->setTexture(new CRayMandelbrotTexture());

  if (shape_data.image != "") {
    CImageFileSrc src(shape_data.image);

    shape->setImage(CImageMgrInst->lookupImage(src));
  }

  shape->setReflect     (shape_data.reflect);
  shape->setRefract     (shape_data.refract);
  shape->setRefractIndex(shape_data.refract_index);

  shape->setIgnoreLight(shape_data.ignore_light);
}

CRayTraceLight *
CRayTrace::
addLight(const CPoint3D &position)
{
  CRayTraceLight *light = new CRayTraceLight(this, "light");

  light->setPosition(position);

  lights_.push_back(light);

  return light;
}

CRayShape *
CRayTrace::
getShape(const std::string &name) const
{
  for (const auto &shape : shapes_)
    if (shape->getId() == name)
      return shape;

  return nullptr;
}

CRayShape *
CRayTrace::
getShape(int ind) const
{
  if (ind >= 0 && ind < int(shapes_.size()))
    return shapes_[ind];

  return nullptr;
}

CRayTraceLight *
CRayTrace::
getLight(const std::string &name) const
{
  for (const auto &light : lights_)
    if (light->getName() == name)
      return light;

  return nullptr;
}

CRayTraceLight *
CRayTrace::
getLight(int ind) const
{
  if (ind >= 0 && ind < int(lights_.size()))
    return lights_[ind];

  return nullptr;
}

void
CRayTrace::
render()
{
  render(renderer_);
}

void
CRayTrace::
render(CRayTraceRenderer *renderer)
{
  uint n = window_.size();

  for (uint i = 0; i < n; ++i)
    stepRender(renderer, window_);
}

void
CRayTrace::
initRender()
{
  for (const auto &thread : threads_)
    delete thread;

  threads_.clear();

  // add shapes to oct tree
  octTree_->reset();

  for (const auto &shape : shapes_)
    octTree_->addData(shape);

  //---

  sampled_ = (num_samples_ > 0);

  if (renderer_) {
    renderer_->begin();

    renderer_->clear(bg_);
  }

  if (sampled_) {
    samples_ = new CSampleMultiJitter(num_samples_);

    samples_->init();
  }

  camera_->init();

  window_.init(0, 0, width_ - 1, height_ - 1);
}

void
CRayTrace::
renderThread(CRayTraceRenderer *renderer, int xmin, int ymin, int xmax, int ymax)
{
  CRayTraceThread *thread = new CRayTraceThread(this, renderer);

  thread->setWindow(xmin, ymin, xmax, ymax);

  threads_.push_back(thread);

  thread->start();
}

void
CRayTrace::
stepRender()
{
  stepRender(renderer_, window_);
}

void
CRayTrace::
stepRender(CRayTraceRenderer *renderer)
{
  stepRender(renderer, window_);
}

void
CRayTrace::
stepRender(CRayTraceRenderer *renderer, CRayTraceWindow &window)
{
  if (sampled_)
    nextSampled(renderer, window);
  else
    nextSimple(renderer, window);
}

void
CRayTrace::
termRender()
{
  for (const auto &thread : threads_)
    thread->join();

  if (sampled_)
    delete samples_;

  if (renderer_)
    renderer_->end();

  changed_ = false;
}

void
CRayTrace::
nextSampled(CRayTraceRenderer *renderer, CRayTraceWindow &window)
{
  if (window.done()) return;

  if (trace_) window.traceStart();

  bool is_hit = false;

  CRGBA fg = CRGBA(0,0,0,0);

  for (uint i = 0; i < num_samples_; ++i) {
    double sx = window.x + samples_->getX(i);
    double sy = window.y + samples_->getY(i);

    CRay ray = camera_->getRay(sx, sy);

    CRGBA fg1;

    if (raytrace(ray, fg1, 0)) {
      fg += fg1;

      is_hit = true;
    }
  }

  if (is_hit) {
    fg /= num_samples_;

    renderer->drawPoint(window.x, window.y, fg);

    ++window.hits;
  }

  if (trace_) window.traceEnd();

  window.step();
}

void
CRayTrace::
nextSimple(CRayTraceRenderer *renderer, CRayTraceWindow &window)
{
  if (window.done()) return;

  if (trace_) window.traceStart();

  CRay ray = camera_->getRay(window.x, window.y);

  CRGBA fg;

  if (raytrace(ray, fg, 0)) {
    renderer->drawPoint(window.x, window.y, fg);

    ++window.hits;
  }

  if (trace_) window.traceEnd();

  window.step();
}

bool
CRayTrace::
raytrace(const CRay &ray, CRGBA &color, uint depth)
{
  HitData hitData;

  if (! getHitData(ray, minT_, maxT_, hitData))
    return false;

  color.zero();

  double alpha = 1.0;

  while (true) {
    CRGBA color1 = rayColor(ray, hitData, depth);

    alpha = color1.getAlpha();

    color = (1 - alpha)*color + alpha*color1;

    if (alpha >= 1.0)
      break;

    if (! getHitData(ray, hitData.getT() + 1E-3, maxT_, hitData))
      break;
  }

  color.setAlpha(1.0);

  return true;
}

CRGBA
CRayTrace::
rayColor(const CRay &ray, const HitData &hitData, uint depth)
{
  // get hit point
  CPoint3D p = ray.pointAt(hitData.getT());

  // get normal
  CVector3D normal = hitData.getShape()->pointNormal(p).unit();

  double cos_theta = ray.getDirection().dotProduct(normal);
  if (cos_theta > 0) normal = -normal;

  // get shape color
  CRGBA color = CRGBA(0,0,0,0);

  CRGBA shape_color = hitData.getShape()->getColor(p);

  // get light color
  CRGBA light_color;

  if (! hitData.getShape()->getIgnoreLight())
    light_color = lightColor(p, normal);
  else
    light_color = CRGBA(1,1,1);

  // combine colors using reflection and refraction values
  double reflect = (depth < reflect_depth_ ? hitData.getShape()->getReflect() : 0.0);
  double refract = (depth < refract_depth_ ? hitData.getShape()->getRefract() : 0.0);

  color += (1 - reflect - refract)*light_color*shape_color;

  // reflect ray
  if (reflect != 0.0) {
    CRay rray = ray.reflect(p, normal);

    CRGBA reflect_color;

    if (raytrace(rray, reflect_color, depth + 1))
      color += reflect*reflect_color;
  }

  // refract ray
  if (refract != 0.0) {
    double refract_index1 = 1.0;
    double refract_index2 = hitData.getShape()->getRefractIndex();

    //double cos_theta1 = ray.getDirection().dotProduct(normal);
    //if (cos_theta1 < 0) swap(refract_index1, refract_index2);

    CRay rray = ray.refract(p, normal, refract_index1, refract_index2);

    CRGBA refract_color;

    if (raytrace(rray, refract_color, depth + 1))
      color += refract*refract_color;
  }

  return color.clamped();
}

CRGBA
CRayTrace::
lightColor(const CPoint3D &point, const CVector3D &normal)
{
  if (lights_.empty()) return CRGBA(1,1,1);

  HitData hitData;

  CRGBA color(0.1,0.1,0.1);

  for (const auto &light : lights_) {
    // get ray from point to light
    CRay lray(point, light->getPosition());

    // get angle to normal
    double factor = normal.dotProduct(lray.getDirection().unit());

    if (factor < 0.01) continue;

    double alpha = 1.0;

    double minT = minT_;

    // check if light ray hits shape
    while (getHitData(lray, minT, maxT_, hitData)) {
      // get alpha for shape
      CPoint3D p = lray.pointAt(hitData.getT());

      CRGBA shape_color = hitData.getShape()->getColor(p);

      alpha *= 1.0 - shape_color.getAlpha();

      if (alpha <= 0.0) break;

      // move to next nearest shape
      minT = hitData.getT() + 1E-3;
    }

    // add light color
    color += alpha*factor*light->getAmbient();
  }

  return color.clamped();
}

bool
CRayTrace::
getHitData(const CRay &ray, double minT, double maxT, HitData &hitData)
{
  hitData.setSet(false);

#if 1
  OctTree *t = octTree_;

  CPoint3D p1 = ray.point(minT);
  CPoint3D p2 = ray.point(maxT);

  addTreeShapes(t, ray, p1, p2, minT, maxT, hitData);
#else
  for (const auto &shape : shapes_)
    updateHitData(shape, ray, minT, maxT, hitData);
#endif

  return hitData.getSet();
}

void
CRayTrace::
addTreeShapes(OctTree *t, const CRay &ray, const CPoint3D &p1, const CPoint3D &p2,
              double minT, double maxT, HitData &hitData)
{
  CPoint3D pi;

  if (t->dead()) return;

  if (! t->getBBox().lineIntersect(p1, p2, pi)) return;

  const OctTree::DataList &dataList = t->getDataList();

  for (const auto &shape : dataList)
    updateHitData(shape, ray, minT, maxT, hitData);

  if (t->isSplit()) {
    for (uint i = 0; i < 8; ++i) {
      addTreeShapes(t->getChild(i), ray, p1, p2, minT, maxT, hitData);
    }
  }
}

void
CRayTrace::
updateHitData(CRayShape *shape, const CRay &ray, double minT, double maxT, HitData &hitData)
{
  // skip if not hit by ray
  CRayHitData hit_data;

  if (! shape->hit(ray, minT, maxT, hit_data))
    return;

  // update closest
  hitData.updateShape(shape, hit_data.t);
}

void
CRayTrace::
drawLights()
{
  if (! renderer_) return;

  for (const auto &light : lights_) {
    CPoint3D p = camera_->worldToRaster(light->getPosition());

    int px = int(p.x);
    int py = int(p.y);

    if (px >= 0 && px < int(width_) && py >= 0 && py < int(height_))
      renderer_->drawPoint(px, py, CRGBA(1,1,1));
  }
}

//---------

void *
CRayTraceThread::
execute()
{
  uint n = window_.size();

  for (uint i = 0; i < n; ++i)
    raytrace_->stepRender(renderer_, window_);

  return nullptr;
}
