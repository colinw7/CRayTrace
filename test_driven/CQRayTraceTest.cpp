#include <CQRayTraceTest.h>
#include <fstream>

void
printTuple(const Tuple &t, bool newline=true)
{
  t.print(std::cerr); std::cerr << " ("; t.printType(std::cerr); std::cerr << ")";
  if (newline) std::cerr << "\n";
}

void
assertTuple(const Tuple &t1, const Tuple &t2)
{
  if (t1 == t2)
    std::cerr << "[32mPASS[0m";
  else {
    std::cerr << "[31mFAIL[0m (!= "; printTuple(t2, false); std::cerr << ")";
  }
}

void
testTuple(const Tuple &t1, const Tuple &t2)
{
  printTuple (t1, false); std::cerr << " ";
  assertTuple(t1, t2   ); std::cerr << "\n";
}

//---

void
printPoint(const Point &t, bool newline=true)
{
  t.print(std::cerr);;
  if (newline) std::cerr << "\n";
}

void
assertPoint(const Point &t1, const Point &t2)
{
  if (t1 == t2)
    std::cerr << "[32mPASS[0m";
  else {
    std::cerr << "[31mFAIL[0m (!= "; printPoint(t2, false); std::cerr << ")";
  }
}

void
testPoint(const Point &t1, const Point &t2)
{
  printPoint (t1, false); std::cerr << " ";
  assertPoint(t1, t2   ); std::cerr << "\n";
}

//---

void
printVector(const Vector &t, bool newline=true)
{
  t.print(std::cerr);;
  if (newline) std::cerr << "\n";
}

void
assertVector(const Vector &t1, const Vector &t2)
{
  if (t1 == t2)
    std::cerr << "[32mPASS[0m";
  else {
    std::cerr << "[31mFAIL[0m (!= "; printVector(t2, false); std::cerr << ")";
  }
}

void
testVector(const Vector &t1, const Vector &t2)
{
  printVector (t1, false); std::cerr << " ";
  assertVector(t1, t2   ); std::cerr << "\n";
}

//---

void
printColor(const Color &c, bool newline=true)
{
  c.print(std::cerr);
  if (newline) std::cerr << "\n";
}

void
assertColor(const Color &c1, const Color &c2)
{
  if (c1 == c2)
    std::cerr << "[32mPASS[0m";
  else {
    std::cerr << "[31mFAIL[0m (!= "; printColor(c2, false); std::cerr << ")";
  }
}

void
testColor(const Color &c1, const Color &c2)
{
  printColor (c1, false); std::cerr << " ";
  assertColor(c1, c2   ); std::cerr << "\n";
}

//---

void
printMatrix(const Matrix4D &m, bool newline=true)
{
  m.print(std::cerr);
  if (newline) std::cerr << "\n";
}

bool
assertMatrix(const Matrix4D &m1, const Matrix4D &m2, bool invert=false)
{
  bool b (! invert ? m1 == m2 : m1 != m2);

  if (b) {
    std::cerr << "[32mPASS[0m"; return true;
  }
  else {
    std::cerr << "[31mFAIL[0m (!= "; printMatrix(m2, false); std::cerr << ")"; return false;
  }
}

void
testMatrix(const Matrix4D &m1, const Matrix4D &m2, bool invert=false)
{
  printMatrix (m1, false);      std::cerr << " ";
  assertMatrix(m1, m2, invert); std::cerr << "\n";
}

//---

void
printMatrix(const Matrix3D &m, bool newline=true)
{
  m.print(std::cerr);
  if (newline) std::cerr << "\n";
}

void
assertMatrix(const Matrix3D &m1, const Matrix3D &m2)
{
  if (m1 == m2)
    std::cerr << "[32mPASS[0m";
  else {
    std::cerr << "[31mFAIL[0m (!= "; printMatrix(m2, false); std::cerr << ")";
  }
}

void
testMatrix(const Matrix3D &m1, const Matrix3D &m2)
{
  printMatrix (m1, false); std::cerr << " ";
  assertMatrix(m1, m2   ); std::cerr << "\n";
}

//---

void
printMatrix(const Matrix2D &m, bool newline=true)
{
  m.print(std::cerr);
  if (newline) std::cerr << "\n";
}

void
assertMatrix(const Matrix2D &m1, const Matrix2D &m2)
{
  if (m1 == m2)
    std::cerr << "[32mPASS[0m";
  else {
    std::cerr << "[31mFAIL[0m (!= "; printMatrix(m2, false); std::cerr << ")";
  }
}

void
testMatrix(const Matrix2D &m1, const Matrix2D &m2)
{
  printMatrix (m1, false); std::cerr << " ";
  assertMatrix(m1, m2   ); std::cerr << "\n";
}

//---

void
assertReal(double r1, double r2)
{
  auto realCmp = [](double r1, double r2) {
    return std::abs(r1 - r2) < 1E-6;
  };

  if (realCmp(r1, r2))
    std::cerr << "[32mPASS[0m";
  else
    std::cerr << "[31mFAIL[0m (!= " << r2 << ")";
}

void
testReal(double r1, double r2)
{
  std::cerr << r1 << " ";

  assertReal(r1, r2);

  std::cerr << "\n";
}

//---

void
assertInt(int i1, int i2)
{
  std::cerr << (i1 == i2 ? "[32mPASS[0m" : "[31mFAIL[0m");
}

void
testInt(int i1, int i2)
{
  std::cerr << i1 << " ";

  assertInt(i1, i2);

  std::cerr << "\n";
}

//---

void
assertBool(bool b1, bool b2)
{
  std::cerr << (b1 == b2 ? "[32mPASS[0m" : "[31mFAIL[0m");
}

void
testBool(bool b1, bool b2)
{
  std::cerr << b1 << " ";

  assertBool(b1, b2);

  std::cerr << "\n";
}

//---

void
assertPtr(const void *p1, const void *p2)
{
  std::cerr << (p1 == p2 ? "[32mPASS[0m" : "[31mFAIL[0m");
}

void
testPtr(const void * p1, const void *p2)
{
  std::cerr << p1 << " ";

  assertPtr(p1, p2);

  std::cerr << "\n";
}

//------

void
testTuple()
{
  // create
  {
  std::cerr << "-- create\n";

  Tuple t1(4.3, -4.2, 3.1, 1.0);
  Tuple t2(4.3, -4.2, 3.1, 0.0);

  testTuple(t1, t1);
  testTuple(t2, t2);

  Point  p3(4, -4, 3);
  Vector v4(4, -4, 3);

  testTuple(p3, p3);
  testTuple(v4, v4);
  }

  // add
  {
  std::cerr << "-- add\n";

  Tuple t1(3, -2, 5, 1);
  Tuple t2(-2, 3, 1, 0);

  testTuple(t1 + t2, Point(1, 1, 6));
  }

  // subtract
  {
  std::cerr << "-- subtract\n";

  Point  p1(3, 2, 1);
  Vector v2(5, 6, 7);

  testTuple(p1 - v2, Point(-2, -4, -6));

  Vector v3(3, 2, 1);
  Vector v4(5, 6, 7);

  testTuple(v3 - v4, Vector(-2, -4, -6));
  }

  // negate
  {
  std::cerr << "-- negate\n";

  Tuple t1(1, -2, 3, -4);

  testTuple(-t1, Tuple(-1, 2, -3, 4));
  }

  // multiply
  {
  std::cerr << "-- multiply\n";

  Tuple t1(1, -2, 3, -4);

  testTuple(3.5*t1, Tuple(3.5, -7.0, 10.5, -14));
  testTuple(0.5*t1, Tuple(0.5, -1, 1.5, -2));
  }

  // divide
  {
  std::cerr << "-- divide\n";

  Tuple t1(1, -2, 3, -4);

  testTuple(t1/2, Tuple(0.5, -1, 1.5, -2));
  }

  // magnitude
  {
  std::cerr << "-- magnitude\n";

  Vector v1(1, 0, 0);
  Vector v2(0, 1, 0);
  Vector v3(0, 0, 1);
  Vector v4(1, 2, 3);
  Vector v5(-1, -2, -3);

  testReal(v1.magnitude(), 1.0);
  testReal(v2.magnitude(), 1.0);
  testReal(v3.magnitude(), 1.0);
  testReal(v4.magnitude(), sqrt(14.0));
  testReal(v5.magnitude(), sqrt(14.0));
  }

  // normalize
  {
  std::cerr << "-- normalize\n";

  Vector v1(4, 0, 0);
  Vector v2(1, 2, 3);

  v1.normalize();
  v2.normalize();

  testTuple(v1, Vector(1, 0, 0));
  testTuple(v2, Vector(1/sqrt(14.0), 2/sqrt(14.0), 3/sqrt(14.0)));

  testReal(v2.magnitude(), 1.0);
  }

  // dot product
  {
  std::cerr << "-- dot product\n";

  Vector v1(1, 2, 3);
  Vector v2(2, 3, 4);

  testReal(v1.dotProduct(v2), 20.0);
  }

  // cross product
  {
  std::cerr << "-- cross product\n";

  Vector v1(1, 2, 3);
  Vector v2(2, 3, 4);

  testTuple(v1.crossProduct(v2), Vector(-1, 2, -1));
  testTuple(v2.crossProduct(v1), Vector(1, -2, 1));
  }
}

void
testProjectile()
{
  std::cerr << "\nprojectile\n";

  auto tick = [](const Environment &env, Projectile &proj) {
    auto position = proj.position + proj.velocity;
    auto velocity = proj.velocity + env.gravity + env.wind;

    return Projectile(position, velocity);
  };

  Point start(0, 1, 0);

  Vector velocity = Vector(1, 1, 0).normalized();

  auto p = Projectile(start, velocity);

  printTuple(p.position);

  Vector gravity(0, -0.1, 0);
  Vector wind   (-0.01, 0, 0);

  auto e = Environment(gravity, wind);

  while (p.position.y() > 0.0) {
    p = tick(e, p);

    printTuple(p.position);
  }
}

void
testColor()
{
  // add
  {
  std::cerr << "add\n";

  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);

  testColor(c1 + c2, Color(1.6, 0.7, 1.0));
  }

  // subtract
  {
  std::cerr << "subtract\n";

  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);

  testColor(c1 - c2, Color(0.2, 0.5, 0.5));
  }

  // multiply
  {
  std::cerr << "multiply\n";

  Color c1(0.2, 0.3, 0.4);

  testColor(c1*2, Color(0.4, 0.6, 0.8));

  Color c2(1.0, 0.2, 0.4);
  Color c3(0.9, 1.0, 0.1);

  testColor(c2*c3, Color(0.9, 0.2, 0.04));
  }
}

void
testCanvas()
{
  {
  Canvas canvas(10, 20);

  testInt(canvas.width (), 10);
  testInt(canvas.height(), 20);

  for (int y = 0; y < canvas.height(); ++y) {
    for (int x = 0; x < canvas.width(); ++x) {
      std::cerr << " ";
      assertColor(canvas.pixel(x, y), Color());
    }
    std::cerr << "\n";
  }
  }

  {
  Canvas canvas(10, 20);

  Color red(1, 0, 0);

  canvas.setPixel(2, 3, red);

  testColor(canvas.pixel(2, 3), red);
  }

  {
  Canvas canvas(5, 3);

  Color c1(1.5, 0, 0);
  Color c2(0, 0.5, 0);
  Color c3(-0.5, 0, 1);

  canvas.setPixel(0, 0, c1);
  canvas.setPixel(2, 1, c2);
  canvas.setPixel(4, 2, c3);

  canvas.writePPM(std::cerr);
  }

  {
  Canvas canvas(10, 2);

  for (int y = 0; y < canvas.height(); ++y) {
    for (int x = 0; x < canvas.width(); ++x) {
      canvas.setPixel(x, y, Color(1.0, 0.8, 0.6));
    }
  }

  canvas.writePPM(std::cerr);
  }
}

void
testCanvasProjectile()
{
  std::cerr << "\nprojectile\n";

  auto tick = [](const Environment &env, Projectile &proj) {
    auto position = proj.position + proj.velocity;
    auto velocity = proj.velocity + env.gravity + env.wind;

    return Projectile(position, velocity);
  };

  Point start(0, 1, 0);

  Vector velocity = Vector(1, 1.8, 0).normalize()*11.25;

  auto p = Projectile(start, velocity);

  Vector gravity(0, -0.1, 0);
  Vector wind   (-0.01, 0, 0);

  auto e = Environment(gravity, wind);

  Canvas canvas(900, 550);

  Color c(1, 1, 1);

  auto setPixel = [&](const Projectile &p, const Color &c) {
    canvas.setPixel(p.position.x(), canvas.height() - 1 - p.position.y(), c);
  };

  setPixel(p, c);

  while (p.position.y() > 0.0) {
    p = tick(e, p);

    setPixel(p, c);
  }

  auto fs = std::ofstream("projectile.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testMatrix()
{
  // create
  {
    Matrix4D m( 1.0,  2.0,  3.0,  4.0,
                5.5,  6.5,  7.5,  8.5,
                9.0, 10.0, 11.0, 12.0,
               13.5, 14.5, 15.5, 16.5);

    printMatrix(m);

    testReal(m.value(0, 0),  1.0);
    testReal(m.value(0, 3),  4.0);
    testReal(m.value(1, 0),  5.5);
    testReal(m.value(1, 2),  7.5);
    testReal(m.value(2, 2), 11.0);
    testReal(m.value(3, 0), 13.5);
    testReal(m.value(3, 2), 15.5);
  }

  // create
  {
    Matrix2D m(-3.0,  5.0,
                1.0, -2.0);

    printMatrix(m);

    testReal(m.value(0, 0), -3.0);
    testReal(m.value(0, 1),  5.0);
    testReal(m.value(1, 0),  1.0);
    testReal(m.value(1, 1), -2.0);
  }

  // create
  {
    Matrix3D m(-3.0,  5.0,  0.0,
                1.0, -2.0, -7.0,
                0.0,  1.0,  1.0);

    printMatrix(m);

    testReal(m.value(0, 0), -3.0);
    testReal(m.value(1, 1), -2.0);
    testReal(m.value(2, 2),  1.0);
  }

  // compare
  {
    Matrix4D m1(1, 2, 3, 4,
                5, 6, 7, 8,
                9, 8, 7, 6,
                5, 4, 3, 2);

    testMatrix(m1, m1);

    Matrix4D m2(1, 2, 3, 4,
                5, 6, 7, 8,
                9, 8, 7, 6,
                5, 4, 3, 1);

    testMatrix(m1, m2, /*invert*/true);
  }

  // add
  {
  }

  // subtract
  {
  }

  // multiply
  {
    Matrix4D m1(1, 2, 3, 4,
                5, 6, 7, 8,
                9, 8, 7, 6,
                5, 4, 3, 2);

    Matrix4D m2(-2, 1, 2,  3,
                 3, 2, 1, -1,
                 4, 3, 6,  5,
                 1, 2, 7,  8);

    testMatrix(m1*m2, Matrix4D(20, 22,  50,  48,
                               44, 54, 114, 108,
                               40, 58, 110, 102,
                               16, 26,  46,  42));

    Matrix4D m3(1, 2, 3, 4,
                2, 4, 4, 2,
                8, 6, 4, 1,
                0, 0, 0, 1);

    Tuple t1(1, 2, 3, 1);

    testTuple(m3*t1, Tuple(18, 24, 33, 1));

    Matrix4D m4(0, 1,  2,  4,
                1, 2,  4,  8,
                2, 4,  8, 16,
                4, 8, 16, 32);

    testMatrix(m4*Matrix4D::identity(), m4);
    testMatrix(Matrix4D::identity()*m4, m4);
  }

  // transpose
  {
    Matrix4D m1(0, 9, 3, 0,
                9, 8, 0, 8,
                1, 8, 5, 3,
                0, 0, 5, 8);

    Matrix4D m2(0, 9, 1, 0,
                9, 8, 8, 0,
                3, 0, 5, 5,
                0, 8, 3, 8);

    testMatrix(m1.transposed(), m2);

    testMatrix(Matrix4D::identity().transposed(), Matrix4D::identity());
  }

  // determinant
  {
    Matrix2D m1(1, 5, -3, 2);

    testReal(m1.determinant(), 17);
  }

  // submatrix 3d
  {
    Matrix3D m1( 1, 5,  0,
                -3, 2,  7,
                 0, 6, -3);

    Matrix2D m2 = m1.submatrix(0, 2);

    testMatrix(m2, Matrix2D(-3, 2,
                             0, 6));
  }

  // submatrix 4d
  {
    Matrix4D m1(-6, 1,  1, 6,
                -8, 5,  8, 6,
                -1, 0,  8, 2,
                -7, 1, -1, 1);

    Matrix3D m2 = m1.submatrix(2, 1);

    testMatrix(m2, Matrix3D(-6,  1, 6,
                            -8,  8, 6,
                            -7, -1, 1));
  }

  // minor 3d
  {
    Matrix3D m1( 3,  5,  0,
                 2, -1, -7,
                 6, -1,  5);

    testReal(m1.minor   (1, 0),  25);
    testReal(m1.cofactor(1, 0), -25);

    testReal(m1.minor   (0, 0), -12);
    testReal(m1.cofactor(0, 0), -12);
  }

  // cofactor, determinant 3d
  {
    Matrix3D m1( 1, 2,  6,
                -5, 8, -4,
                 2, 6,  4);

    testReal(m1.cofactor(0, 0),  56);
    testReal(m1.cofactor(0, 1),  12);
    testReal(m1.cofactor(0, 2), -46);

    testReal(m1.determinant(), -196);
  }

  // cofactor, determinant 4d
  {
    Matrix4D m1(-2, -8,  3,  5,
                -3,  1,  7,  3,
                 1,  2, -9,  6,
                -6,  7,  7, -9);

    testReal(m1.cofactor(0, 0), 690);
    testReal(m1.cofactor(0, 1), 447);
    testReal(m1.cofactor(0, 2), 210);
    testReal(m1.cofactor(0, 3),  51);

    testReal(m1.determinant(), -4071);
  }

  // inverse
  {
    Matrix4D m1( 6,  4,  4,  4,
                 5,  5,  7,  6,
                 4, -9,  3, -7,
                 9,  1,  7, -6);

    testReal(m1.determinant(), -2120);
    testBool(m1.canInvert(), true);

    Matrix4D m2(-4,  2, -2, -3,
                 9,  6,  2,  6,
                 0, -5,  1, -5,
                 0,  0,  0,  0);

    testReal(m2.determinant(), 0);
    testBool(m2.canInvert(), false);

    Matrix4D m3(-5,  2,  6, -8,
                 1, -5,  1,  8,
                 7,  7, -6, -7,
                 1, -3,  7,  4);

    Matrix4D im3 = m3.inverted();

    testReal(m3.determinant(), 532);

    testReal(m3.cofactor(2, 3), -160);
    testReal(im3.value(3, 2), -160.0/532.0);

    testReal(m3.cofactor(3, 2), 105);
    testReal(im3.value(2, 3), 105.0/532.0);

    testMatrix(im3, Matrix4D( 0.2180451,  0.4511278,  0.2406015, -0.0451128,
                             -0.8082707, -1.4567669, -0.4436090,  0.5206769,
                             -0.0789474, -0.2236842, -0.0526316,  0.1973684,
                             -0.5225564, -0.8139098, -0.3007518,  0.3063910));

    Matrix4D m4( 8, -5,  9,  2,
                 7,  5,  6,  1,
                -6,  0,  9,  6,
                -3,  0, -9, -4);

    testReal(m4.determinant(), -585);

    Matrix4D im4 = m4.inverted();

    testMatrix(im4, Matrix4D(-0.1538462, -0.1538462, -0.2820513, -0.5384615,
                             -0.0769231,  0.1230769,  0.0256410,  0.0307692,
                              0.3589744,  0.3589744,  0.4358974,  0.9230769,
                             -0.6923077, -0.6923077, -0.7692308, -1.9230770));

    Matrix4D m5( 9,  3,  0,  9,
                -5, -2, -6, -3,
                -4,  9,  6,  4,
                -7,  6,  6,  2);

    testReal(m5.determinant(), 1620);

    Matrix4D im5 = m5.inverted();

    testMatrix(im5, Matrix4D(-0.04074074, -0.07777778,  0.1444444, -0.2222222,
                             -0.07777778,  0.03333333,  0.3666667, -0.3333333,
                             -0.02901235, -0.14629630, -0.1092593,  0.1296296,
                              0.17777778,  0.06666667, -0.2666667,  0.3333333));
  }

  // multiply inverse
  {
    Matrix4D m1( 3, -9,  7,  3,
                 3, -8,  2, -9,
                -4,  4,  4,  1,
                -6,  5, -1,  1);

    Matrix4D m2( 8,  2,  2,  2,
                 3, -1,  7,  0,
                 7,  0,  5,  4,
                 6, -2,  0,  5);

    Matrix4D m3 = m1*m2;

    testMatrix(m3*m2.inverted(), m1);
    testMatrix(m1.inverted()*m3, m2);
  }
}

void
testTransform()
{
  // translate point
  {
    std::cerr << "-- translate point\n";

    Matrix4D m1 = Matrix4D::translation(5, -3, 2);

    Point p1(-3, 4, 5);

    testPoint(m1*p1, Point(2, 1, 7));

    Matrix4D im1 = m1.inverted();

    testPoint(im1*p1, Point(-8, 7, 3));
  }

  // translate vector
  {
    std::cerr << "-- translate vector\n";

    Matrix4D m1 = Matrix4D::translation(5, -3, 2);

    Vector v1(-3, 4, 5);

    testVector(m1*v1, Vector(-3, 4, 5));
  }

  // scale point
  {
    std::cerr << "-- scale point\n";

    Matrix4D m1 = Matrix4D::scale(2, 3, 4);

    Point p1(-4, 6, 8);

    testPoint(m1*p1, Point(-8, 18, 32));
  }

  // scale vector
  {
    std::cerr << "-- scale vector\n";

    Matrix4D m1 = Matrix4D::scale(2, 3, 4);

    Vector v1(-4, 6, 8);

    testVector(m1*v1, Vector(-8, 18, 32));

    Matrix4D im1 = m1.inverted();

    testVector(im1*v1, Vector(-2, 2, 2));
  }

  // reflection
  {
    std::cerr << "-- reflection\n";

    Matrix4D m1 = Matrix4D::scale(-1, 1, 1);

    Point p1(2, 3, 4);

    testPoint(m1*p1, Point(-2, 3, 4));
  }

  // rotate x
  {
    std::cerr << "-- rotate x\n";

    Point p1(0, 1, 0);

    Matrix4D m1 = Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/4.0);
    Matrix4D m2 = Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/2.0);

    testPoint(m1*p1, Point(0.0, sqrt(2)/2, sqrt(2)/2));
    testPoint(m2*p1, Point(0.0, 0.0, 1.0));

    Matrix4D m3 = m1.inverted();

    testPoint(m3*p1, Point(0.0, sqrt(2)/2, -sqrt(2)/2));
  }

  // rotate y
  {
    std::cerr << "-- rotate y\n";

    Point p1(0, 0, 1);

    Matrix4D m1 = Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0);
    Matrix4D m2 = Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/2.0);

    testPoint(m1*p1, Point(sqrt(2)/2, 0.0, sqrt(2)/2));
    testPoint(m2*p1, Point(1.0, 0.0, 0.0));

    Matrix4D m3 = m1.inverted();

    testPoint(m3*p1, Point(-sqrt(2)/2, 0.0, sqrt(2)/2));
  }

  // rotate z
  {
    std::cerr << "-- rotate z\n";

    Point p1(0, 1, 0);

    Matrix4D m1 = Matrix4D::rotation(Matrix4D::AxisType::Z, M_PI/4.0);
    Matrix4D m2 = Matrix4D::rotation(Matrix4D::AxisType::Z, M_PI/2.0);

    testPoint(m1*p1, Point(-sqrt(2)/2, sqrt(2)/2, 0.0));
    testPoint(m2*p1, Point(-1.0, 0.0, 0.0));

    Matrix4D m3 = m1.inverted();

    testPoint(m3*p1, Point(sqrt(2)/2, sqrt(2)/2, 0.0));
  }

  // shear
  {
    std::cerr << "-- shear\n";

    Point p1(2, 3, 4);

    Matrix4D m1 = Matrix4D::shear(1, 0, 0, 0, 0, 0); // x in proportion to y

    testPoint(m1*p1, Point(5, 3, 4));

    Matrix4D m2 = Matrix4D::shear(0, 1, 0, 0, 0, 0); // x in proportion to z

    testPoint(m2*p1, Point(6, 3, 4));

    Matrix4D m3 = Matrix4D::shear(0, 0, 1, 0, 0, 0); // y in proportion to x

    testPoint(m3*p1, Point(2, 5, 4));

    Matrix4D m4 = Matrix4D::shear(0, 0, 0, 1, 0, 0); // y in proportion to z

    testPoint(m4*p1, Point(2, 7, 4));

    Matrix4D m5 = Matrix4D::shear(0, 0, 0, 0, 1, 0); // z in proportion to x

    testPoint(m5*p1, Point(2, 3, 6));

    Matrix4D m6 = Matrix4D::shear(0, 0, 0, 0, 0, 1); // z in proportion to x

    testPoint(m6*p1, Point(2, 3, 7));
  }

  // chained transforms
  {
    std::cerr << "-- chained transforms\n";

    Point p1(1, 0, 1);

    Matrix4D m1 = Matrix4D::rotation   (Matrix4D::AxisType::X, M_PI/2.0);
    Matrix4D m2 = Matrix4D::scale      (5, 5, 5);
    Matrix4D m3 = Matrix4D::translation(10, 5, 7);

    Point p2 = m1*p1;

    testPoint(p2   , Point(1, -1, 0));
    testPoint(m1*p1, Point(1, -1, 0));

    Point p3 = m2*p2;

    testPoint(p3      , Point(5, -5, 0));
    testPoint(m2*p2   , Point(5, -5, 0));
    testPoint(m2*m1*p1, Point(5, -5, 0));

    Point p4 = m3*p3;

    testPoint(p4         , Point(15, 0, 7));
    testPoint(m3*p3      , Point(15, 0, 7));
    testPoint(m3*m2*p2   , Point(15, 0, 7));
    testPoint(m3*m2*m1*p1, Point(15, 0, 7));
  }
}

void
testClock()
{
  Canvas canvas(256, 256);

  Color color(1, 1, 1);

  auto setPixel = [&](const Point &p) {
    canvas.setPixel(p.x(), canvas.height() - 1 - p.y(), color);
  };

  Point center(0, 0, 0);

  double a  = 0.0;
  double da = M_PI/6;
  double r  = 100;

  for (int i = 0; i < 12; ++i) {
    Matrix4D m1 = Matrix4D::translation(r, 0, 0);
    Matrix4D m2 = Matrix4D::rotation   (Matrix4D::AxisType::Z, a);
    Matrix4D m3 = Matrix4D::translation(128, 128, 0);

    Point p = m3*m2*m1*center;

    setPixel(p);

    a += da;
  }

  auto fs = std::ofstream("clock.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testRay()
{
  // create
  {
  Point  origin(1, 2, 3);
  Vector direction(4, 5, 6);

  Ray ray(origin, direction);

  testPoint (ray.origin(), origin);
  testVector(ray.direction(), direction);
  }

  // position
  {
  Point  origin(2, 3, 4);
  Vector direction(1, 0, 0);

  Ray ray(origin, direction);

  testPoint(ray.position(0), origin);
  testPoint(ray.position(1), Point(3, 3, 4));
  testPoint(ray.position(-1), Point(1, 3, 4));
  testPoint(ray.position(2.5), Point(4.5, 3, 4));
  }

  // sphere
  {
  Sphere sphere;

  Ray ray1(Point(0, 0, -5), Vector(0, 0, 1));

  Intersections intersections1 = sphere.intersect(ray1);

  testInt (intersections1.count(), 2);
  testReal(intersections1[0].t(), 4.0);
  testReal(intersections1[1].t(), 6.0);

  //--

  Ray ray2(Point(0, 1, -5), Vector(0, 0, 1));

  Intersections intersections2 = sphere.intersect(ray2);

  testInt (intersections2.count(), 2);
  testReal(intersections2[0].t(), 5.0);
  testReal(intersections2[1].t(), 5.0);

  //--

  Ray ray3(Point(0, 2, -5), Vector(0, 0, 1));

  Intersections intersections3 = sphere.intersect(ray3);

  testInt(intersections3.count(), 0);

  //--

  Ray ray4(Point(0, 0, 0), Vector(0, 0, 1));

  Intersections intersections4 = sphere.intersect(ray4);

  testInt (intersections4.count(), 2);
  testReal(intersections4[0].t(), -1.0);
  testReal(intersections4[1].t(),  1.0);

  //--

  Ray ray5(Point(0, 0, 5), Vector(0, 0, 1));

  Intersections intersections5 = sphere.intersect(ray5);

  testInt (intersections5.count(), 2);
  testReal(intersections5[0].t(), -6.0);
  testReal(intersections5[1].t(), -4.0);

  testPtr(intersections5[0].object(), &sphere);

  //--

  Intersection i(3.5, &sphere);

  testReal(i.t(), 3.5);
  testPtr(i.object(), &sphere);

  //---

  Intersection i1(1, &sphere);
  Intersection i2(2, &sphere);

  Intersections xs({i1, i2});

  testInt(xs.count(), 2);
  testInt(xs[0].t(), 1);
  testInt(xs[1].t(), 2);

  //--

  Ray ray6(Point(0, 0, -5), Vector(0, 0, 1));

  Intersections intersections6 = sphere.intersect(ray6);

  testInt(intersections6.count(), 2);
  testPtr(intersections6[0].object(), &sphere);
  testPtr(intersections6[1].object(), &sphere);
  }

  // hit
  {
  Sphere sphere;

  Intersection i1(1, &sphere);
  Intersection i2(2, &sphere);

  Intersections xs1({i1, i2});

  Intersection ii1 = xs1.hit();

  testReal(ii1.t(), 1.0);
  testPtr (ii1.object(), &sphere);

  //--

  Intersection i3(-1, &sphere);

  Intersections xs2({i3, i1});

  Intersection ii2 = xs2.hit();

  testReal(ii2.t(), 1.0);
  testPtr (ii2.object(), &sphere);

  //--

  Intersection i4(-2, &sphere);

  Intersections xs3({i4, i3});

  Intersection ii3 = xs3.hit();

  testReal(ii3.t(), 0.0);
  testPtr (ii3.object(), nullptr);

  //---

  Intersection i5(5, &sphere);
  Intersection i6(7, &sphere);
  Intersection i7(-3, &sphere);
  Intersection i8(2, &sphere);

  Intersections xs4({i5, i6, i7, i8});

  Intersection ii4 = xs4.hit();

  testReal(ii4.t(), 2.0);
  testPtr (ii4.object(), &sphere);
  }

  // transform ray
  {
  Ray ray1(Point(1, 2, 3), Vector(0, 1, 0));

  Matrix4D m1 = Matrix4D::translation(3, 4, 5);

  Ray r1t = ray1.transform(m1);

  testPoint (r1t.origin   (), Point (4, 6, 8));
  testVector(r1t.direction(), Vector(0, 1, 0));

  //--

  Ray r2(Point(1, 2, 3), Vector(0, 1, 0));

  Matrix4D m2 = Matrix4D::scale(2, 3, 4);

  Ray r2t = r2.transform(m2);

  testPoint (r2t.origin   (), Point (2, 6, 12));
  testVector(r2t.direction(), Vector(0, 3, 0));
  }

  // object transform
  {
  Sphere sphere;

  testMatrix(sphere.transform(), Matrix4D::identity());

  Matrix4D m1 = Matrix4D::translation(2, 3, 4);

  sphere.setTransform(m1);

  testMatrix(sphere.transform(), m1);
  }

  // transformed object ray intersect
  {
  Ray ray1(Point(0, 0, -5), Vector(0, 0, 1));

  Sphere sphere1;

  sphere1.setTransform(Matrix4D::scale(2, 2, 2));

  Intersections intersections1 = sphere1.intersect(ray1);

  testInt (intersections1.count(), 2);
  testReal(intersections1[0].t(), 3.0);
  testReal(intersections1[1].t(), 7.0);

  //--

  Ray ray2(Point(0, 0, -5), Vector(0, 0, 1));

  Sphere sphere2;

  sphere2.setTransform(Matrix4D::translation(5, 0, 0));

  Intersections intersections2 = sphere2.intersect(ray2);

  testInt(intersections2.count(), 0);
  }
}

void
testRaySphere()
{
  Sphere sphere;

  sphere.transform(Matrix4D::rotation(Matrix4D::AxisType::Z, M_PI/4.0)*
                   Matrix4D::scale   (0.5, 1, 1));

  int canvasSize = 256;

  Canvas canvas(canvasSize, canvasSize);

  Color red(1, 0, 0);

  Point src(0, 0, -5);

  double wallZ     = 10.0;
  double wallSize  = 7.0;
  double pixelSize = wallSize/canvasSize;

  for (int y = 0; y < canvas.height(); ++y) {
    double y1 = wallSize/2.0 - pixelSize*y;

    for (int x = 0; x < canvas.width(); ++x) {
      double x1 = -wallSize/2.0 + pixelSize*x;

      Point dest(x1, y1, wallZ);

      Ray ray(src, (dest - src).normalized());

      Intersections intersections = sphere.intersect(ray);

      if (intersections.count()) {
        //Intersection intersection = intersections.hit();

        canvas.setPixel(x, y, red);
      }
    }
  }

  auto fs = std::ofstream("sphere.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

int
main(int /*argc*/, char** /*argv*/)
{
  //testTuple();

  //testProjectile();

  //---

  //testColor ();
  //testCanvas();

  //testCanvasProjectile();

  //---

  //testMatrix();

  //testTransform();

  //testClock();

  //--

  //testRay();

  testRaySphere();

  return 0;
}
