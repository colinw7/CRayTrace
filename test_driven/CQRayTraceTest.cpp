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
  t.print(std::cerr);
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
  t.print(std::cerr);
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
printMaterial(const Material &m, bool newline=true)
{
  m.print(std::cerr);
  if (newline) std::cerr << "\n";
}

void
assertMaterial(const Material &m1, const Material &m2)
{
  if (m1 == m2)
    std::cerr << "[32mPASS[0m";
  else {
    std::cerr << "[31mFAIL[0m (!= "; printMaterial(m2, false); std::cerr << ")";
  }
}

void
testMaterial(const Material &m1, const Material &m2)
{
  printMaterial (m1, false); std::cerr << " ";
  assertMaterial(m1, m2   ); std::cerr << "\n";
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
    std::cerr << "[31mFAIL[0m (!= " << std::setprecision(7) << r2 << ")";
}

void
testReal(double r1, double r2)
{
  std::cerr << std::setprecision(7) << r1 << " ";

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

  auto fs = std::ofstream("images/projectile.ppm", std::ofstream::out);

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
testCanvasClock()
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

  auto fs = std::ofstream("images/clock.ppm", std::ofstream::out);

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
  SphereP sphere = std::make_shared<Sphere>();

  Ray ray1(Point(0, 0, -5), Vector(0, 0, 1));

  Intersections intersections1 = sphere->intersect(ray1);

  testInt (intersections1.count(), 2);
  testReal(intersections1[0].t(), 4.0);
  testReal(intersections1[1].t(), 6.0);

  //--

  Ray ray2(Point(0, 1, -5), Vector(0, 0, 1));

  Intersections intersections2 = sphere->intersect(ray2);

  testInt (intersections2.count(), 2);
  testReal(intersections2[0].t(), 5.0);
  testReal(intersections2[1].t(), 5.0);

  //--

  Ray ray3(Point(0, 2, -5), Vector(0, 0, 1));

  Intersections intersections3 = sphere->intersect(ray3);

  testInt(intersections3.count(), 0);

  //--

  Ray ray4(Point(0, 0, 0), Vector(0, 0, 1));

  Intersections intersections4 = sphere->intersect(ray4);

  testInt (intersections4.count(), 2);
  testReal(intersections4[0].t(), -1.0);
  testReal(intersections4[1].t(),  1.0);

  //--

  Ray ray5(Point(0, 0, 5), Vector(0, 0, 1));

  Intersections intersections5 = sphere->intersect(ray5);

  testInt (intersections5.count(), 2);
  testReal(intersections5[0].t(), -6.0);
  testReal(intersections5[1].t(), -4.0);

  testPtr(intersections5[0].object(), &sphere);

  //--

  Intersection i(3.5, sphere.get());

  testReal(i.t(), 3.5);
  testPtr(i.object(), sphere.get());

  //---

  Intersection i1(1, sphere.get());
  Intersection i2(2, sphere.get());

  Intersections xs({i1, i2});

  testInt(xs.count(), 2);
  testInt(xs[0].t(), 1);
  testInt(xs[1].t(), 2);

  //--

  Ray ray6(Point(0, 0, -5), Vector(0, 0, 1));

  Intersections intersections6 = sphere->intersect(ray6);

  testInt(intersections6.count(), 2);
  testPtr(intersections6[0].object(), sphere.get());
  testPtr(intersections6[1].object(), sphere.get());
  }

  // hit
  {
  SphereP sphere = std::make_shared<Sphere>();

  Intersection i1(1, sphere.get());
  Intersection i2(2, sphere.get());

  Intersections xs1({i1, i2});

  Intersection ii1 = xs1.hit();

  testReal(ii1.t(), 1.0);
  testPtr (ii1.object(), sphere.get());

  //--

  Intersection i3(-1, sphere.get());

  Intersections xs2({i3, i1});

  Intersection ii2 = xs2.hit();

  testReal(ii2.t(), 1.0);
  testPtr (ii2.object(), sphere.get());

  //--

  Intersection i4(-2, sphere.get());

  Intersections xs3({i4, i3});

  Intersection ii3 = xs3.hit();

  testReal(ii3.t(), 0.0);
  testPtr (ii3.object(), nullptr);

  //---

  Intersection i5( 5, sphere.get());
  Intersection i6( 7, sphere.get());
  Intersection i7(-3, sphere.get());
  Intersection i8( 2, sphere.get());

  Intersections xs4({i5, i6, i7, i8});

  Intersection ii4 = xs4.hit();

  testReal(ii4.t(), 2.0);
  testPtr (ii4.object(), sphere.get());
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
  SphereP sphere = std::make_shared<Sphere>();

  testMatrix(sphere->transform(), Matrix4D::identity());

  Matrix4D m1 = Matrix4D::translation(2, 3, 4);

  sphere->setTransform(m1);

  testMatrix(sphere->transform(), m1);
  }

  // transformed object ray intersect
  {
  Ray ray1(Point(0, 0, -5), Vector(0, 0, 1));

  SphereP sphere1 = std::make_shared<Sphere>();

  sphere1->setTransform(Matrix4D::scale(2, 2, 2));

  Intersections intersections1 = sphere1->intersect(ray1);

  testInt (intersections1.count(), 2);
  testReal(intersections1[0].t(), 3.0);
  testReal(intersections1[1].t(), 7.0);

  //--

  Ray ray2(Point(0, 0, -5), Vector(0, 0, 1));

  SphereP sphere2 = std::make_shared<Sphere>();

  sphere2->setTransform(Matrix4D::translation(5, 0, 0));

  Intersections intersections2 = sphere2->intersect(ray2);

  testInt(intersections2.count(), 0);
  }
}

void
testCanvasRaySphere()
{
  SphereP sphere = std::make_shared<Sphere>();

  sphere->transform(Matrix4D::rotation(Matrix4D::AxisType::Z, M_PI/4.0)*
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

      Intersections intersections = sphere->intersect(ray);

      if (intersections.count()) {
        //Intersection intersection = intersections.hit();

        canvas.setPixel(x, y, red);
      }
    }
  }

  auto fs = std::ofstream("images/sphere.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testSphereNormal()
{
  // basic sphere
  {
  SphereP sphere = std::make_shared<Sphere>();

  Vector normal1 = sphere->pointNormal(Point(1, 0, 0));

  testVector(normal1, Vector(1, 0, 0));

  Vector normal2 = sphere->pointNormal(Point(0, 1, 0));

  testVector(normal2, Vector(0, 1, 0));

  Vector normal3 = sphere->pointNormal(Point(0, 0, 1));

  testVector(normal3, Vector(0, 0, 1));

  Vector normal4 = sphere->pointNormal(Point(sqrt(3)/3.0, sqrt(3)/3.0, sqrt(3)/3.0));

  testVector(normal4, Vector(sqrt(3)/3.0, sqrt(3)/3.0, sqrt(3)/3.0));

  testVector(normal4.normalized(), normal4);
  }

  // transformed sphere
  {
  SphereP sphere1 = std::make_shared<Sphere>();

  sphere1->setTransform(Matrix4D::translation(0, 1, 0));

  Vector normal1 = sphere1->pointNormal(Point(0, 1 + sqrt(2)/2, -sqrt(2)/2));

  testVector(normal1, Vector(0, sqrt(2)/2, -sqrt(2)/2));

  //---

  SphereP sphere2 = std::make_shared<Sphere>();

  sphere2->setTransform(Matrix4D::scale(1, 0.5, 1)*
                        Matrix4D::rotation(Matrix4D::AxisType::Z, M_PI/5.0));

  Vector normal2 = sphere2->pointNormal(Point(0, sqrt(2)/2, -sqrt(2)/2));

  testVector(normal2, Vector(0, 0.970143, -0.242536));
  }

  // reflect
  {
  Vector v1(1, -1, 0);
  Vector n1(0, 1, 0);

  Vector r1 = v1.reflect(n1);

  testVector(r1, Vector(1, 1, 0));

  //---

  Vector v2(0, -1, 0);
  Vector n2(sqrt(2)/2, sqrt(2)/2, 0);

  Vector r2 = v2.reflect(n2);

  testVector(r2, Vector(1, 0, 0));
  }
}

void
testLight()
{
  // point light
  {
    Point position (0, 0, 0);
    Color intensity(1, 1, 1);

    PointLight light(position, intensity);

    testPoint(light.position (), position );
    testColor(light.intensity(), intensity);
  }
}

void
testMaterial()
{
  // material
  {
  Material material;

  SphereP sphere = std::make_shared<Sphere>();

  testMaterial(sphere->material(), material);

  //---

  material.setAmbient(1);

  sphere->setMaterial(material);

  testMaterial(sphere->material(), material);
  }
}

void
testLighting()
{
  {
  Material material;

  Point position(0, 0, 0);

  bool inShadow = false;

  Vector eye1(0, 0, -1);

  Vector normal1(0, 0, -1);

  PointLight light1(Point(0, 0, -10), Color(1, 1, 1));

  Color c1 = RayTrace::lighting(nullptr, material, light1, position, eye1, normal1, inShadow);

  testColor(c1, Color(1.9, 1.9, 1.9));

  //---

  Vector eye2(0, sqrt(2)/2, -sqrt(2)/2);

  Vector normal2(0, 0, -1);

  PointLight light2(Point(0, 0, -10), Color(1, 1, 1));

  Color c2 = RayTrace::lighting(nullptr, material, light2, position, eye2, normal2, inShadow);

  testColor(c2, Color(1.0, 1.0, 1.0));

  //---

  Vector eye3(0, 0, -1);

  Vector normal3(0, 0, -1);

  PointLight light3(Point(0, 10, -10), Color(1, 1, 1));

  Color c3 = RayTrace::lighting(nullptr, material, light3, position, eye3, normal3, inShadow);

  testColor(c3, Color(0.736396, 0.736396, 0.736396));

  //---

  Vector eye4(0, -sqrt(2)/2, -sqrt(2)/2);

  Vector normal4(0, 0, -1);

  PointLight light4(Point(0, 10, -10), Color(1, 1, 1));

  Color c4 = RayTrace::lighting(nullptr, material, light4, position, eye4, normal4, inShadow);

  testColor(c4, Color(1.636396, 1.636396, 1.636396));

  //---

  Vector eye5(0, 0, -1);

  Vector normal5(0, 0, -1);

  PointLight light5(Point(0, 0, 10), Color(1, 1, 1));

  Color c5 = RayTrace::lighting(nullptr, material, light5, position, eye5, normal5, inShadow);

  testColor(c5, Color(0.1, 0.1, 0.1));
  }
}

void
testCanvasLightingRaySphere()
{
  SphereP sphere = std::make_shared<Sphere>();

  Material material;

  material.setColor(Color(1.0, 0.2, 1.0));

  sphere->setMaterial(material);

  PointLight light;

  light.setPosition (Point(-10, 10, -10));
  light.setIntensity(Color(1, 1, 1));

  //---

  //sphere->transform(Matrix4D::rotation(Matrix4D::AxisType::Z, M_PI/4.0)*
  //                  Matrix4D::scale   (0.5, 1, 1));

  int canvasSize = 256;

  Canvas canvas(canvasSize, canvasSize);

  bool inShadow = false;

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

      Intersections intersections = sphere->intersect(ray);

      if (intersections.count()) {
        Intersection intersection = intersections.hit();

        Point point = ray.position(intersection.t());

        Vector normal = sphere->pointNormal(point);

        Vector eye = -ray.direction();

        Color c = RayTrace::lighting(nullptr, material, light, point, eye, normal, inShadow);

        canvas.setPixel(x, y, c);
      }
    }
  }

  auto fs = std::ofstream("images/sphere.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testWorld()
{
  {
  World world;

  testInt(world.objects().size(), 0);
  testInt(world.lights().size(), 0);
  }

  //---

  {
  DefaultWorld defaultWorld;

  testInt(defaultWorld.objects().size(), 2);
  testInt(defaultWorld.lights().size(), 1);

  //--

  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

  Intersections intersections = defaultWorld.intersect(ray);

  testInt(intersections.count(), 4);

  testReal(intersections.at(0).t(), 4);
  testReal(intersections.at(1).t(), 4.5);
  testReal(intersections.at(2).t(), 5.5);
  testReal(intersections.at(3).t(), 6);
  }

  //--

  {
  Ray ray1(Point(0, 0, -5), Vector(0, 0, 1));

  SphereP sphere1 = std::make_shared<Sphere>();

  Intersection intersection1(4, sphere1.get());

  IntersectionData intersectionData1(intersection1, ray1);

  testBool  (intersectionData1.inside(), false);
  testReal  (intersectionData1.t()     , intersection1.t());
  testPtr   (intersectionData1.object(), intersection1.object());
  testPoint (intersectionData1.point() , Point(0, 0, -1));
  testVector(intersectionData1.eye()   , Vector(0, 0, -1));
  testVector(intersectionData1.normal(), Vector(0, 0, -1));

  //--

  Ray ray2(Point(0, 0, 0), Vector(0, 0, 1));

  SphereP sphere2 = std::make_shared<Sphere>();

  Intersection intersection2(1, sphere2.get());

  IntersectionData intersectionData2(intersection2, ray2);

  testPoint (intersectionData2.point() , Point(0, 0, 1));
  testVector(intersectionData2.eye()   , Vector(0, 0, -1));
  testBool  (intersectionData2.inside(), true);
  testVector(intersectionData2.normal(), Vector(0, 0, -1));
  }

  //--

  {
  DefaultWorld defaultWorld;

  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

  ObjectP object = defaultWorld.objects()[0];

  Intersection intersection(4, object.get());

  IntersectionData intersectionData(intersection, ray);

  Color color = defaultWorld.shadeHit(intersectionData);

  testColor(color, Color(0.380661, 0.475826, 0.285496));
  }

  {
  DefaultWorld defaultWorld;

  auto light = std::make_shared<PointLight>(Point(0, 0.25, 0), Color(1, 1, 1));

  defaultWorld.setLight(0, light);

  Ray ray(Point(0, 0, 0), Vector(0, 0, 1));

  ObjectP object = defaultWorld.objects()[1];

  Intersection intersection(0.5, object.get());

  IntersectionData intersectionData(intersection, ray);

  Color color = defaultWorld.shadeHit(intersectionData);

  testColor(color, Color(0.904984, 0.904984, 0.904984));
  }

  {
  DefaultWorld defaultWorld;

  Ray ray(Point(0, 0, -5), Vector(0, 1, 0));

  Color color = defaultWorld.colorAt(ray);

  testColor(color, Color(0, 0, 0));
  }

  {
  DefaultWorld defaultWorld;

  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

  Color color = defaultWorld.colorAt(ray);

  testColor(color, Color(0.380661, 0.475826, 0.285496));
  }

  {
  DefaultWorld defaultWorld;

  ObjectP outer = defaultWorld.objects()[0];
  ObjectP inner = defaultWorld.objects()[1];

  outer->material().setAmbient(1);
  inner->material().setAmbient(1);

  Ray ray(Point(0, 0, 0.75), Vector(0, 0, -1));

  Color color = defaultWorld.colorAt(ray);

  testColor(color, inner->material().color());
  }

  {
  Point  from(0, 0, 8);
  Point  to  (0, 0, 0);
  Vector up  (0, 1, 0);

  Matrix4D t = viewTransform(from, to, up);

  testMatrix(t, Matrix4D::translation(0, 0, -8));
  }

  {
  Point  from(1,  3, 2);
  Point  to  (4, -2, 8);
  Vector up  (1,  1, 0);

  Matrix4D t = viewTransform(from, to, up);

  testMatrix(t, Matrix4D(-0.5070926, 0.5070926,  0.6761234, -2.366432,
                          0.7677159, 0.6060915,  0.1212183, -2.828427,
                         -0.3585686, 0.5976143, -0.7171372,  0.000000,
                          0.0000000, 0.0000000,  0.0000000,  1.000000));
  }
}

void
testCamera()
{
  {
  Camera camera;

  testInt   (camera.hsize(), 160);
  testInt   (camera.vsize(), 120);
  testReal  (camera.fov(), M_PI/2.0);
  testMatrix(camera.transform(), Matrix4D::identity());
  }

  {
  Camera camera(200, 125, M_PI/2.0);

  testReal(camera.pixelSize(), 0.01);
  }

  {
  Camera camera(125, 200, M_PI/2.0);

  testReal(camera.pixelSize(), 0.01);
  }

  {
  Camera camera(201, 101, M_PI/2.0);

  Ray ray = camera.rayForPixel(100, 50);

  testPoint (ray.origin   (), Point (0, 0,  0));
  testVector(ray.direction(), Vector(0, 0, -1));
  }

  {
  Camera camera(201, 101, M_PI/2.0);

  Ray ray = camera.rayForPixel(0, 0);

  testPoint (ray.origin   (), Point (0, 0,  0));
  testVector(ray.direction(), Vector(0.6651864, 0.3325932, -0.6685124));
  }

  {
  Camera camera(201, 101, M_PI/2.0);

  camera.setTransform(Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0)*
                      Matrix4D::translation(0, -2, 5));

  Ray ray = camera.rayForPixel(100, 50);

  testPoint (ray.origin   (), Point (0, 2,  -5));
  testVector(ray.direction(), Vector(sqrt(2)/2, 0, -sqrt(2)/2));
  }
}

void
testRender1()
{
  DefaultWorld defaultWorld;

  Camera camera(11, 11, M_PI/2.0);

  Point  from(0, 0, -5);
  Point  to  (0, 0,  0);
  Vector up  (0, 1,  0);

  camera.setTransform(viewTransform(from, to, up));

  Canvas canvas;

  render(canvas, camera, defaultWorld);

  testColor(canvas.pixel(5, 5), Color(0.3806612, 0.4758265, 0.2854959));

  auto fs = std::ofstream("images/render1.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testRender2()
{
  World world;

  //--

  SphereP floor = std::make_shared<Sphere>();

  floor->transform(Matrix4D::scale(10, 0.01, 10));

  floor->material().setColor(Color(1, 0.9, 0.9));
  floor->material().setSpecular(0);

  world.addObject(floor);

  //--

  SphereP leftWall = std::make_shared<Sphere>();

  leftWall->transform(Matrix4D::translation(0, 0, 5)*
                      Matrix4D::rotation(Matrix4D::AxisType::Y, -M_PI/4.0)*
                      Matrix4D::rotation(Matrix4D::AxisType::X,  M_PI/2.0)*
                      Matrix4D::scale(10, 0.01, 10));

  leftWall->setMaterial(floor->material());

  world.addObject(leftWall);

  //--

  SphereP rightWall = std::make_shared<Sphere>();

  rightWall->transform(Matrix4D::translation(0, 0, 5)*
                       Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0)*
                       Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/2.0)*
                       Matrix4D::scale(10, 0.01, 10));

  rightWall->setMaterial(floor->material());

  world.addObject(rightWall);

  //--

  SphereP middle = std::make_shared<Sphere>();

  middle->transform(Matrix4D::translation(-0.5, 1, 0.5));

  middle->material().setColor(Color(0.1, 1, 0.5));
  middle->material().setDiffuse(0.7);
  middle->material().setSpecular(0.3);

  world.addObject(middle);

  //--

  SphereP right = std::make_shared<Sphere>();

  right->transform(Matrix4D::translation(1.5, 0.5, -0.5)*
                   Matrix4D::scale(0.5, 0.5, 0.5));

  right->material().setColor(Color(0.5, 1, 0.1));
  right->material().setDiffuse(0.7);
  right->material().setSpecular(0.3);

  world.addObject(right);

  //--

  SphereP left = std::make_shared<Sphere>();

  left->transform(Matrix4D::translation(-1.5, 0.33, -0.75)*
                  Matrix4D::scale(0.33, 0.33, 0.33));

  left->material().setColor(Color(1, 0.8, 0.1));
  left->material().setDiffuse(0.7);
  left->material().setSpecular(0.3);

  world.addObject(left);

  //---

  auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

  world.addLight(light);

  //---

  //Camera camera(100, 50, M_PI/3.0);
  Camera camera(512, 384, M_PI/3.0);

  camera.setTransform(viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

  Canvas canvas;

  render(canvas, camera, world);

  auto fs = std::ofstream("images/render2.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testShadow()
{
  {
  Material material;

  Point position(0, 0, 0);

  Vector eye(0, 0, -1);

  Vector normal(0, 0, -1);

  PointLight light(Point(0, 0, -10), Color(1, 1, 1));

  bool inShadow = true;

  Color c = RayTrace::lighting(nullptr, material, light, position, eye, normal, inShadow);

  testColor(c, Color(0.1, 0.1, 0.1));
  }

  {
  DefaultWorld defaultWorld;

  testBool(defaultWorld.isShadowed(Point(  0,  10,   0)), false);
  testBool(defaultWorld.isShadowed(Point( 10, -10,  10)), true );
  testBool(defaultWorld.isShadowed(Point(-20,  20, -20)), false);
  testBool(defaultWorld.isShadowed(Point( -2,   2,  -2)), false);
  }

  {
  World world;

  auto light = std::make_shared<PointLight>(Point(0, 0, -10), Color(1, 1, 1));

  world.addLight(light);

  SphereP sphere1 = std::make_shared<Sphere>();

  world.addObject(sphere1);

  SphereP sphere2 = std::make_shared<Sphere>();

  sphere2->transform(Matrix4D::translation(0, 0, -10));

  world.addObject(sphere2);

  Ray ray(Point(0, 0, 5), Vector(0, 0, 1));

  Intersection intersection(4, sphere2.get());

  IntersectionData intersectionData(intersection, ray);

  Color color = world.shadeHit(intersectionData);

  testColor(color, Color(0.1, 0.1, 0.1));
  }

  {
  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

  SphereP sphere = std::make_shared<Sphere>();

  sphere->transform(Matrix4D::translation(0, 0, 1));

  Intersection intersection(5, sphere.get());

  IntersectionData intersectionData(intersection, ray);

  testBool(intersectionData.overPoint().z() < -World::EPSILON()/2, true);
  testBool(intersectionData.point().z() > intersectionData.overPoint().z(), true);
  }
}

void
testShape()
{
  {
  TestObject testObject;

  testMatrix(testObject.transform(), Matrix4D::identity());

  //--

  testObject.setTransform(Matrix4D::translation(2, 3, 4));

  testMatrix(testObject.transform(), Matrix4D::translation(2, 3, 4));

  //--

  testMaterial(testObject.material(), Material());

  Material material;

  material.setAmbient(1);

  testObject.setMaterial(material);

  testMaterial(testObject.material(), material);
  }

  //--

  {
  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

  TestObject testObject;

  testObject.setTransform(Matrix4D::scale(2, 2, 2));

  Intersections intersections1 = testObject.intersect(ray);

  testPoint (testObject.saveRay().origin   (), Point (0, 0, -2.5));
  testVector(testObject.saveRay().direction(), Vector(0, 0, 0.5));

  //--

  testObject.setTransform(Matrix4D::translation(5, 0, 0));

  Intersections intersections2 = testObject.intersect(ray);

  testPoint (testObject.saveRay().origin   (), Point (-5, 0, -5));
  testVector(testObject.saveRay().direction(), Vector(0, 0, 1));
  }

  //--

  {
  TestObject testObject;

  testObject.setTransform(Matrix4D::translation(0, 1, 0));

  Vector normal1 = testObject.pointNormal(Point(0, 1.7071068, -0.7071068));

  testVector(normal1, Vector(0, 0.7071068, -0.7071068));

  //--

  testObject.setTransform(Matrix4D::scale(1, 0.5, 1)*
                          Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/5.0));

  Vector normal2 = testObject.pointNormal(Point(0, sqrt(2)/2.0, -sqrt(2)/2.0));

  testVector(normal2, Vector(0, 0.9701425, -0.2425356));
  }

  //--

  {
  Plane plane;

  Vector n1 = plane.pointNormal(Point( 0, 0,   0));
  Vector n2 = plane.pointNormal(Point(10, 0, -10));
  Vector n3 = plane.pointNormal(Point(-5, 0, 150));

  testVector(n1, Vector(0, 1, 0));
  testVector(n2, Vector(0, 1, 0));
  testVector(n3, Vector(0, 1, 0));
  }

  {
  PlaneP plane = std::make_shared<Plane>();

  Ray ray1(Point(0, 10, 0), Vector(0, 0, 1));

  Intersections intersections1 = plane->intersect(ray1);

  testInt(intersections1.count(), 0);

  //--

  Ray ray2(Point(0, 0, 0), Vector(0, 0, 1));

  Intersections intersections2 = plane->intersect(ray2);

  testInt(intersections2.count(), 0);

  //--

  Ray ray3(Point(0, 1, 0), Vector(0, -1, 0));

  Intersections intersections3 = plane->intersect(ray3);

  testInt (intersections3.count(), 1);
  testReal(intersections3[0].t(), 1.0);
  testPtr (intersections3[0].object(), plane.get());

  //--

  Ray ray4(Point(0, -1, 0), Vector(0, 1, 0));

  Intersections intersections4 = plane->intersect(ray4);

  testInt (intersections4.count(), 1);
  testReal(intersections4[0].t(), 1.0);
  testPtr (intersections4[0].object(), plane.get());
  }
}

void
testRenderShape()
{
  World world;

  //--

  PlaneP floor = std::make_shared<Plane>();

  //floor->transform(Matrix4D::scale(10, 0.01, 10));

  floor->material().setColor(Color(1, 0.9, 0.9));
  floor->material().setSpecular(0);

  world.addObject(floor);

  //--

  PlaneP leftWall = std::make_shared<Plane>();

  //leftWall->transform(Matrix4D::translation(0, 0, 5)*
  //                    Matrix4D::rotation(Matrix4D::AxisType::Y, -M_PI/4.0)*
  //                    Matrix4D::rotation(Matrix4D::AxisType::X,  M_PI/2.0)*
  //                    Matrix4D::scale(10, 0.01, 10));

  leftWall->transform(Matrix4D::translation(0, 0, 5)*
                      Matrix4D::rotation(Matrix4D::AxisType::Y, -M_PI/4.0)*
                      Matrix4D::rotation(Matrix4D::AxisType::X,  M_PI/2.0));

  leftWall->setMaterial(floor->material());

  world.addObject(leftWall);

  //--

  PlaneP rightWall = std::make_shared<Plane>();

  //rightWall->transform(Matrix4D::translation(0, 0, 5)*
  //                     Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0)*
  //                     Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/2.0)*
  //                     Matrix4D::scale(10, 0.01, 10));

  rightWall->transform(Matrix4D::translation(0, 0, 5)*
                       Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0)*
                       Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/2.0));

  rightWall->setMaterial(floor->material());

  world.addObject(rightWall);

  //--

  SphereP middle = std::make_shared<Sphere>();

  middle->transform(Matrix4D::translation(-0.5, 1, 0.5));

  middle->material().setColor(Color(0.1, 1, 0.5));
  middle->material().setDiffuse(0.7);
  middle->material().setSpecular(0.3);

  world.addObject(middle);

  //--

  SphereP right = std::make_shared<Sphere>();

  right->transform(Matrix4D::translation(1.5, 0.5, -0.5)*
                   Matrix4D::scale(0.5, 0.5, 0.5));

  right->material().setColor(Color(0.5, 1, 0.1));
  right->material().setDiffuse(0.7);
  right->material().setSpecular(0.3);

  world.addObject(right);

  //--

  SphereP left = std::make_shared<Sphere>();

  left->transform(Matrix4D::translation(-1.5, 0.33, -0.75)*
                  Matrix4D::scale(0.33, 0.33, 0.33));

  left->material().setColor(Color(1, 0.8, 0.1));
  left->material().setDiffuse(0.7);
  left->material().setSpecular(0.3);

  world.addObject(left);

  //---

  auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

  world.addLight(light);

  //---

  //Camera camera(100, 50, M_PI/3.0);
  Camera camera(512, 384, M_PI/3.0);

  camera.setTransform(viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

  Canvas canvas;

  render(canvas, camera, world);

  auto fs = std::ofstream("images/render_shape.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testStripedPattern()
{
  {
  StripedPattern pattern(Color::makeWhite(), Color::makeBlack());

  testColor(pattern.color1(), Color::makeWhite());
  testColor(pattern.color2(), Color::makeBlack());

  //---

  testColor(pattern.pointColor(Point(0, 0, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point(0, 1, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point(0, 2, 0)), Color::makeWhite());

  testColor(pattern.pointColor(Point(0, 0, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point(0, 0, 1)), Color::makeWhite());
  testColor(pattern.pointColor(Point(0, 0, 2)), Color::makeWhite());

  testColor(pattern.pointColor(Point( 0.0, 0, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point( 0.9, 0, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point( 1.0, 0, 0)), Color::makeBlack());
  testColor(pattern.pointColor(Point(-0.1, 0, 0)), Color::makeBlack());
  testColor(pattern.pointColor(Point(-1.0, 0, 0)), Color::makeBlack());
  testColor(pattern.pointColor(Point(-1.1, 0, 0)), Color::makeWhite());
  }

  {
  Material material;

  material.setPattern(std::make_shared<StripedPattern>(Color::makeWhite(), Color::makeBlack()));

  material.setAmbient (1.0);
  material.setDiffuse (0.0);
  material.setSpecular(0.0);

  Vector eye   (0, 0, -1);
  Vector normal(0, 0, -1);

  auto light = std::make_shared<PointLight>(Point(0, 0, -10), Color(1, 1, 1));

  Color c1 = RayTrace::lighting(nullptr, material, *light, Point(0.9, 0, 0), eye, normal, false);
  Color c2 = RayTrace::lighting(nullptr, material, *light, Point(1.1, 0, 0), eye, normal, false);

  testColor(c1, Color(1, 1, 1));
  testColor(c2, Color(0, 0, 0));
  }
}

void
testPattern()
{
  {
  TestPattern testPattern;

  testMatrix(testPattern.transform(), Matrix4D::identity());

  testPattern.setTransform(Matrix4D::translation(1, 2, 3));

  testMatrix(testPattern.transform(), Matrix4D::translation(1, 2, 3));
  }
}

void
testGradientPattern()
{
  {
  GradientPattern pattern(Color::makeWhite(), Color::makeBlack());

  testColor(pattern.color1(), Color::makeWhite());
  testColor(pattern.color2(), Color::makeBlack());

  //---

  testColor(pattern.pointColor(Point(0.00, 0, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point(0.25, 0, 0)), Color(0.75, 0.75, 0.75));
  testColor(pattern.pointColor(Point(0.50, 0, 0)), Color(0.50, 0.50, 0.50));
  testColor(pattern.pointColor(Point(0.75, 0, 0)), Color(0.25, 0.25, 0.25));

  testColor(pattern.pointColor(Point(0.9999999, 0, 0)), Color::makeBlack());
  }
}

void
testRingPattern()
{
  {
  RingPattern pattern(Color::makeWhite(), Color::makeBlack());

  testColor(pattern.color1(), Color::makeWhite());
  testColor(pattern.color2(), Color::makeBlack());

  //---

  testColor(pattern.pointColor(Point(0, 0, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point(1, 0, 0)), Color::makeBlack());
  testColor(pattern.pointColor(Point(0, 0, 1)), Color::makeBlack());

  testColor(pattern.pointColor(Point(0.708, 0, 0.708)), Color::makeBlack());
  }
}

void
testCheckerPattern()
{
  {
  CheckerPattern pattern(Color::makeWhite(), Color::makeBlack());

  testColor(pattern.color1(), Color::makeWhite());
  testColor(pattern.color2(), Color::makeBlack());

  //---

  testColor(pattern.pointColor(Point(0.00, 0, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point(0.99, 0, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point(1.01, 0, 0)), Color::makeBlack());

  testColor(pattern.pointColor(Point(0, 0.00, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point(0, 0.99, 0)), Color::makeWhite());
  testColor(pattern.pointColor(Point(0, 1.01, 0)), Color::makeBlack());

  testColor(pattern.pointColor(Point(0, 0, 0.00)), Color::makeWhite());
  testColor(pattern.pointColor(Point(0, 0, 0.99)), Color::makeWhite());
  testColor(pattern.pointColor(Point(0, 0, 1.01)), Color::makeBlack());
  }
}

void
testRenderPattern()
{
  auto stripedPattern  = std::make_shared<StripedPattern >(Color::makeWhite(), Color::makeRed   ());
  auto gradientPattern = std::make_shared<GradientPattern>(Color::makeWhite(), Color::makeGreen ());
  auto ringPattern     = std::make_shared<RingPattern    >(Color::makeWhite(), Color::makeBlue  ());
  auto checkerPattern  = std::make_shared<CheckerPattern >(Color::makeWhite(), Color::makeYellow());

  //---

  World world;

  //--

  PlaneP floor = std::make_shared<Plane>();

  floor->material().setColor(Color(1, 0.9, 0.9));
  floor->material().setSpecular(0);
  floor->material().setPattern(checkerPattern);

  world.addObject(floor);

  //--

  PlaneP leftWall = std::make_shared<Plane>();

  leftWall->transform(Matrix4D::translation(0, 0, 5)*
                      Matrix4D::rotation(Matrix4D::AxisType::Y, -M_PI/4.0)*
                      Matrix4D::rotation(Matrix4D::AxisType::X,  M_PI/2.0));

  leftWall->material().setColor(Color(1, 0.9, 0.9));
  leftWall->material().setSpecular(0);
  leftWall->material().setPattern(stripedPattern);

  world.addObject(leftWall);

  //--

  PlaneP rightWall = std::make_shared<Plane>();

  rightWall->transform(Matrix4D::translation(0, 0, 5)*
                       Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0)*
                       Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/2.0));

  rightWall->material().setColor(Color(1, 0.9, 0.9));
  rightWall->material().setSpecular(0);
  rightWall->material().setPattern(ringPattern);

  world.addObject(rightWall);

  //--

  SphereP middle = std::make_shared<Sphere>();

  middle->transform(Matrix4D::translation(-0.5, 1, 0.5));

  middle->material().setColor(Color(0.1, 1, 0.5));
  middle->material().setDiffuse(0.7);
  middle->material().setSpecular(0.3);
  middle->material().setPattern(stripedPattern);

  world.addObject(middle);

  //--

  SphereP right = std::make_shared<Sphere>();

  right->transform(Matrix4D::translation(1.5, 0.5, -0.5)*
                   Matrix4D::scale(0.5, 0.5, 0.5));

  right->material().setColor(Color(0.5, 1, 0.1));
  right->material().setDiffuse(0.7);
  right->material().setSpecular(0.3);
  right->material().setPattern(gradientPattern);

  world.addObject(right);

  //--

  SphereP left = std::make_shared<Sphere>();

  left->transform(Matrix4D::translation(-1.5, 0.33, -0.75)*
                  Matrix4D::scale(0.33, 0.33, 0.33));

  left->material().setColor(Color(1, 0.8, 0.1));
  left->material().setDiffuse(0.7);
  left->material().setSpecular(0.3);
  left->material().setPattern(ringPattern);

  world.addObject(left);

  //---

  auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

  world.addLight(light);

  //---

  //Camera camera(100, 50, M_PI/3.0);
  Camera camera(512, 384, M_PI/3.0);

  camera.setTransform(viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

  Canvas canvas;

  render(canvas, camera, world);

  auto fs = std::ofstream("images/render_pattern.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testTransformPattern()
{
  {
  SphereP sphere = std::make_shared<Sphere>();

  sphere->setTransform(Matrix4D::scale(2, 2, 2));

  auto pattern = std::make_shared<StripedPattern>(Color::makeWhite(), Color::makeBlack());

  Color color = pattern->objectPointColor(sphere.get(), Point(1.5, 0, 0));

  testColor(color, Color::makeWhite());
  }

  //---

  {
  SphereP sphere = std::make_shared<Sphere>();

  auto pattern = std::make_shared<StripedPattern>(Color::makeWhite(), Color::makeBlack());

  pattern->setTransform(Matrix4D::scale(2, 2, 2));

  Color color = pattern->objectPointColor(sphere.get(), Point(1.5, 0, 0));

  testColor(color, Color::makeWhite());
  }

  //---

  {
  SphereP sphere = std::make_shared<Sphere>();

  sphere->setTransform(Matrix4D::scale(2, 2, 2));

  auto pattern = std::make_shared<StripedPattern>(Color::makeWhite(), Color::makeBlack());

  pattern->setTransform(Matrix4D::translation(0.5, 0, 0));

  Color color = pattern->objectPointColor(sphere.get(), Point(2.5, 0, 0));

  testColor(color, Color::makeWhite());
  }

  //---

  {
  SphereP sphere = std::make_shared<Sphere>();

  sphere->setTransform(Matrix4D::scale(2, 2, 2));

  auto pattern = std::make_shared<TestPattern>();

  Color color = pattern->objectPointColor(sphere.get(), Point(2, 3, 4));

  testColor(color, Color(1, 1.5, 2));
  }

  //---

  {
  SphereP sphere = std::make_shared<Sphere>();

  auto pattern = std::make_shared<TestPattern>();

  pattern->setTransform(Matrix4D::scale(2, 2, 2));

  Color color = pattern->objectPointColor(sphere.get(), Point(2, 3, 4));

  testColor(color, Color(1, 1.5, 2));
  }

  //---

  {
  SphereP sphere = std::make_shared<Sphere>();

  sphere->setTransform(Matrix4D::scale(2, 2, 2));

  auto pattern = std::make_shared<TestPattern>();

  pattern->setTransform(Matrix4D::translation(0.5, 1, 1.5));

  Color color = pattern->objectPointColor(sphere.get(), Point(2.5, 3, 3.5));

  testColor(color, Color(0.75, 0.5, 0.25));
  }
}

void
testReflect()
{
  {
  Material material;

  testReal(material.reflective(), 0.0);
  }

  {
  PlaneP plane = std::make_shared<Plane>();

  Ray ray(Point(0, 1, -1), Vector(0, -sqrt(2)/2, sqrt(2)/2));

  Intersection intersection(sqrt(2), plane.get());

  IntersectionData intersectionData(intersection, ray);

  testVector(intersectionData.reflect(), Vector(0, sqrt(2)/2, sqrt(2)/2));
  }

  {
  DefaultWorld defaultWorld;

  Ray ray(Point(0, 0, 0), Vector(0, 0, 1));

  ObjectP object = defaultWorld.objects()[1];

  object->material().setAmbient(1);

  Intersection intersection(1, object.get());

  IntersectionData intersectionData(intersection, ray);

  Color color = defaultWorld.reflectedColor(intersectionData);

  testColor(color, Color(0, 0, 0));
  }

  {
  DefaultWorld defaultWorld;

  PlaneP plane = std::make_shared<Plane>();

  plane->material().setReflective(0.5);
  plane->setTransform(Matrix4D::translation(0, -1, 0));

  defaultWorld.addObject(plane);

  Ray ray(Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2));

  Intersection intersection(sqrt(2), plane.get());

  IntersectionData intersectionData(intersection, ray);

  Color color = defaultWorld.reflectedColor(intersectionData);

  testColor(color, Color(0.190331, 0.237913, 0.142748));
  }

  {
  DefaultWorld defaultWorld;

  PlaneP plane = std::make_shared<Plane>();

  plane->material().setReflective(0.5);
  plane->setTransform(Matrix4D::translation(0, -1, 0));

  defaultWorld.addObject(plane);

  Ray ray(Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2));

  Intersection intersection(sqrt(2), plane.get());

  IntersectionData intersectionData(intersection, ray);

  Color color = defaultWorld.shadeHit(intersectionData);

  testColor(color, Color(0.876756, 0.924339, 0.829173));
  }

  {
  World world;

  auto light = std::make_shared<PointLight>(Point(0, 0, 0), Color(1, 1, 1));

  world.addLight(light);

  PlaneP lower = std::make_shared<Plane>();

  lower->material().setReflective(1.0);
  lower->setTransform(Matrix4D::translation(0, -1, 0));

  world.addObject(lower);

  PlaneP upper = std::make_shared<Plane>();

  upper->material().setReflective(1.0);
  upper->setTransform(Matrix4D::translation(0, 1, 0));

  world.addObject(upper);

  Ray ray(Point(0, 0, 0), Vector(0, 1, 0));

  Color color = world.colorAt(ray);

  testColor(color, Color(9.5, 9.5, 9.5));
  }

  {
  DefaultWorld defaultWorld;

  PlaneP plane = std::make_shared<Plane>();

  plane->material().setReflective(0.5);
  plane->setTransform(Matrix4D::translation(0, -1, 0));

  defaultWorld.addObject(plane);

  Ray ray(Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2));

  Intersection intersection(sqrt(2), plane.get());

  IntersectionData intersectionData(intersection, ray);

  Color color = defaultWorld.reflectedColor(intersectionData, 0);

  testColor(color, Color(0, 0, 0));
  }
}

void
testRenderReflect()
{
  World world;

  auto checkerPattern  = std::make_shared<CheckerPattern >(Color::makeWhite(), Color::makeBlack());

  //--

  PlaneP floor = std::make_shared<Plane>();

  floor->material().setColor(Color(0.0, 0.0, 0.0));
  floor->material().setSpecular(0);
  floor->material().setPattern(checkerPattern);
  floor->material().setReflective(0.7);

  world.addObject(floor);

  //--

  PlaneP leftWall = std::make_shared<Plane>();

  leftWall->transform(Matrix4D::translation(0, 0, 5)*
                      Matrix4D::rotation(Matrix4D::AxisType::Y, -M_PI/4.0)*
                      Matrix4D::rotation(Matrix4D::AxisType::X,  M_PI/2.0));

  leftWall->material().setColor(Color(0.0, 0.0, 0.0));
  leftWall->material().setSpecular(0);
  leftWall->material().setPattern(checkerPattern);

  world.addObject(leftWall);

  //--

  PlaneP rightWall = std::make_shared<Plane>();

  rightWall->transform(Matrix4D::translation(0, 0, 5)*
                       Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0)*
                       Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/2.0));

  rightWall->material().setColor(Color(0.0, 0.0, 0.0));
  rightWall->material().setSpecular(0);
  rightWall->material().setPattern(checkerPattern);

  world.addObject(rightWall);

  //--

  SphereP middle = std::make_shared<Sphere>();

  middle->transform(Matrix4D::translation(-0.5, 1, 0.5));

  middle->material().setColor(Color(0.8, 0.2, 0.2));
  middle->material().setDiffuse(0.7);
  middle->material().setSpecular(0.3);
  middle->material().setReflective(0.5);

  world.addObject(middle);

  //--

  SphereP right = std::make_shared<Sphere>();

  right->transform(Matrix4D::translation(1.5, 0.5, -0.5)*
                   Matrix4D::scale(0.5, 0.5, 0.5));

  right->material().setColor(Color(0.2, 0.8, 0.2));
  right->material().setDiffuse(0.7);
  right->material().setSpecular(0.3);
  right->material().setReflective(0.3);

  world.addObject(right);

  //--

  SphereP left = std::make_shared<Sphere>();

  left->transform(Matrix4D::translation(-1.5, 0.33, -0.75)*
                  Matrix4D::scale(0.33, 0.33, 0.33));

  left->material().setColor(Color(0.2, 0.2, 0.8));
  left->material().setDiffuse(0.7);
  left->material().setSpecular(0.3);
  left->material().setReflective(0.1);

  world.addObject(left);

  //---

  auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

  world.addLight(light);

  //---

  //Camera camera(100, 50, M_PI/3.0);
  Camera camera(512, 384, M_PI/3.0);

  camera.setTransform(viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

  Canvas canvas;

  render(canvas, camera, world);

  auto fs = std::ofstream("images/render_reflect.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testRefract()
{
  {
  Material material;

  testReal(material.transparency(), 0.0);
  testReal(material.refractiveIndex(), 1.0);
  }

  {
  GlassSphere sphere;

  testReal(sphere.material().transparency(), 1.0);
  testReal(sphere.material().refractiveIndex(), 1.5);
  }

  {
  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

  GlassSphereP sphere = std::make_shared<GlassSphere>();

  sphere->setTransform(Matrix4D::translation(0, 0, 1));

  Intersection intersection(5, sphere.get());

  Intersections intersections { intersection };

  IntersectionData intersectionData(intersection, ray, intersections);

  testBool(intersectionData.underPoint().z() > World::EPSILON()/2, true);

  testBool(intersectionData.point().z() < intersectionData.underPoint().z(), true);
  }

  {
  DefaultWorld defaultWorld;

  ObjectP object = defaultWorld.objects()[0];

  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

  Intersections intersections { Intersection(4, object.get()), Intersection(6, object.get()), };

  IntersectionData intersectionData(intersections.at(0), ray, intersections);

  Color color = defaultWorld.refractedColor(intersectionData, 5);

  testColor(color, Color(0, 0, 0));
  }

  {
  DefaultWorld defaultWorld;

  ObjectP object = defaultWorld.objects()[0];

  object->material().setTransparency   (1.0);
  object->material().setRefractiveIndex(1.5);

  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

  Intersections intersections { Intersection(4, object.get()), Intersection(6, object.get()), };

  IntersectionData intersectionData(intersections.at(0), ray, intersections);

  Color color = defaultWorld.refractedColor(intersectionData, 0);

  testColor(color, Color(0, 0, 0));
  }

  {
  DefaultWorld defaultWorld;

  ObjectP object = defaultWorld.objects()[0];

  object->material().setTransparency   (1.0);
  object->material().setRefractiveIndex(1.5);

  Ray ray(Point(0, 0, sqrt(2)/2), Vector(0, 1, 0));

  Intersections intersections { Intersection(-sqrt(2)/2, object.get()),
                                Intersection( sqrt(2)/2, object.get()) };

  IntersectionData intersectionData(intersections.at(1), ray, intersections);

  Color color = defaultWorld.refractedColor(intersectionData, 5);

  testColor(color, Color(0, 0, 0));
  }

  {
  DefaultWorld defaultWorld;

  auto pattern = std::make_shared<TestPattern>();

  ObjectP object1 = defaultWorld.objects()[0];

  object1->material().setAmbient(1.0);
  object1->material().setPattern(pattern);

  ObjectP object2 = defaultWorld.objects()[1];

  object2->material().setTransparency   (1.0);
  object2->material().setRefractiveIndex(1.5);

  Ray ray(Point(0, 0, 0.1), Vector(0, 1, 0));

  Intersections intersections { Intersection(-0.9899, object1.get()),
                                Intersection(-0.4899, object2.get()),
                                Intersection( 0.4899, object2.get()),
                                Intersection( 0.9899, object1.get())  };

  IntersectionData intersectionData(intersections.at(2), ray, intersections);

  Color color = defaultWorld.refractedColor(intersectionData, 5);

  testColor(color, Color(0, 0.998884, 0.0472167));
  }

  {
  DefaultWorld defaultWorld;

  PlaneP floor = std::make_shared<Plane>();

  floor->setTransform(Matrix4D::translation(0, -1, 0));
  floor->material().setTransparency   (0.5);
  floor->material().setRefractiveIndex(1.5);

  defaultWorld.addObject(floor);

  SphereP ball = std::make_shared<Sphere>();

  ball->material().setColor(Color(1, 0, 0));
  ball->material().setAmbient(0.5);
  ball->setTransform(Matrix4D::translation(0, -3.5, -0.5));

  defaultWorld.addObject(ball);

  Ray ray(Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2));

  Intersections intersections { Intersection(sqrt(2), floor.get()) };

  IntersectionData intersectionData(intersections.at(0), ray, intersections);

  Color color = defaultWorld.shadeHit(intersectionData, 5);

  testColor(color, Color(0.936425, 0.686425, 0.686425));
  }
}

void
testRefractN1N2()
{
  {
  GlassSphereP sphere1 = std::make_shared<GlassSphere>();

  sphere1->setTransform(Matrix4D::scale(2, 2, 2));
  sphere1->material().setRefractiveIndex(1.5);

  GlassSphereP sphere2 = std::make_shared<GlassSphere>();

  sphere2->setTransform(Matrix4D::translation(0, 0, -0.25));
  sphere2->material().setRefractiveIndex(2.0);

  GlassSphereP sphere3 = std::make_shared<GlassSphere>();

  sphere3->setTransform(Matrix4D::translation(0, 0, 0.25));
  sphere3->material().setRefractiveIndex(2.5);

  Ray ray(Point(0, 0, -4), Vector(0, 0, 1));

  Intersections intersections = {
    Intersection(2.00, sphere1.get()),
    Intersection(2.75, sphere2.get()),
    Intersection(3.25, sphere3.get()),
    Intersection(4.75, sphere2.get()),
    Intersection(5.25, sphere3.get()),
    Intersection(6.00, sphere1.get())
  };

  IntersectionData intersectionData1(intersections.at(0), ray, intersections);
  IntersectionData intersectionData2(intersections.at(1), ray, intersections);
  IntersectionData intersectionData3(intersections.at(2), ray, intersections);
  IntersectionData intersectionData4(intersections.at(3), ray, intersections);
  IntersectionData intersectionData5(intersections.at(4), ray, intersections);
  IntersectionData intersectionData6(intersections.at(5), ray, intersections);

  testReal(intersectionData1.n1(), 1.0); testReal(intersectionData1.n2(), 1.5);
  testReal(intersectionData2.n1(), 1.5); testReal(intersectionData2.n2(), 2.0);
  testReal(intersectionData3.n1(), 2.0); testReal(intersectionData3.n2(), 2.5);
  testReal(intersectionData4.n1(), 2.5); testReal(intersectionData4.n2(), 2.5);
  testReal(intersectionData5.n1(), 2.5); testReal(intersectionData5.n2(), 1.5);
  testReal(intersectionData6.n1(), 1.5); testReal(intersectionData6.n2(), 1.0);
  }
}

void
testRenderRefract()
{
  World world;

  auto checkerPattern  = std::make_shared<CheckerPattern >(Color::makeWhite(), Color::makeBlack());

  //--

  PlaneP floor = std::make_shared<Plane>();

  floor->material().setColor(Color(0.0, 0.0, 0.0));
  floor->material().setSpecular(0);
  floor->material().setPattern(checkerPattern);
  floor->material().setReflective(0.7);

  world.addObject(floor);

  //--

  PlaneP leftWall = std::make_shared<Plane>();

  leftWall->transform(Matrix4D::translation(0, 0, 5)*
                      Matrix4D::rotation(Matrix4D::AxisType::Y, -M_PI/4.0)*
                      Matrix4D::rotation(Matrix4D::AxisType::X,  M_PI/2.0));

  leftWall->material().setColor(Color(0.0, 0.0, 0.0));
  leftWall->material().setSpecular(0);
  leftWall->material().setPattern(checkerPattern);

  world.addObject(leftWall);

  //--

  PlaneP rightWall = std::make_shared<Plane>();

  rightWall->transform(Matrix4D::translation(0, 0, 5)*
                       Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0)*
                       Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/2.0));

  rightWall->material().setColor(Color(0.0, 0.0, 0.0));
  rightWall->material().setSpecular(0);
  rightWall->material().setPattern(checkerPattern);

  world.addObject(rightWall);

  //--

  SphereP middle = std::make_shared<Sphere>();

  middle->transform(Matrix4D::translation(-0.5, 1, 0.5));

  middle->material().setColor(Color(0.8, 0.2, 0.2));
  middle->material().setDiffuse(0.3);
  middle->material().setSpecular(0.3);
  middle->material().setTransparency(0.9);
  middle->material().setReflective(0.9);
  middle->material().setRefractiveIndex(1.5);

  world.addObject(middle);

  //--

  SphereP right = std::make_shared<Sphere>();

  right->transform(Matrix4D::translation(1.5, 0.5, -0.5)*
                   Matrix4D::scale(0.5, 0.5, 0.5));

  right->material().setColor(Color(0.2, 0.8, 0.2));
  right->material().setDiffuse(0.3);
  right->material().setSpecular(0.3);
  right->material().setTransparency(0.7);
  right->material().setReflective(0.7);
  right->material().setRefractiveIndex(1.5);

  world.addObject(right);

  //--

  SphereP left = std::make_shared<Sphere>();

  left->transform(Matrix4D::translation(-1.5, 0.33, -0.75)*
                  Matrix4D::scale(0.33, 0.33, 0.33));

  left->material().setColor(Color(0.2, 0.2, 0.8));
  left->material().setDiffuse(0.3);
  left->material().setSpecular(0.3);
  left->material().setTransparency(0.5);
  left->material().setReflective(0.5);
  left->material().setRefractiveIndex(1.5);

  world.addObject(left);

  //---

  auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

  world.addLight(light);

  //---

  //Camera camera(100, 50, M_PI/3.0);
  Camera camera(512, 384, M_PI/3.0);

  camera.setTransform(viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

  Canvas canvas;

  render(canvas, camera, world);

  auto fs = std::ofstream("images/render_refract.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testSchlick()
{
  {
  GlassSphereP sphere = std::make_shared<GlassSphere>();

  Ray ray(Point(0, 0, sqrt(2)/2), Vector(0, 1, 0));

  Intersections intersections = {
    Intersection(-sqrt(2)/2, sphere.get()),
    Intersection( sqrt(2)/2, sphere.get())
  };

  IntersectionData intersectionData(intersections.at(1), ray, intersections);

  double reflectance = intersectionData.schlick();

  testReal(reflectance, 1.0);
  }

  {
  GlassSphereP sphere = std::make_shared<GlassSphere>();

  Ray ray(Point(0, 0, 0), Vector(0, 1, 0));

  Intersections intersections = {
    Intersection(-1, sphere.get()),
    Intersection( 1, sphere.get())
  };

  IntersectionData intersectionData(intersections.at(1), ray, intersections);

  double reflectance = intersectionData.schlick();

  testReal(reflectance, 0.04);
  }

  {
  GlassSphereP sphere = std::make_shared<GlassSphere>();

  Ray ray(Point(0, 0.99, -2), Vector(0, 0, 1));

  Intersections intersections = {
    Intersection(1.8589, sphere.get())
  };

  IntersectionData intersectionData(intersections.at(0), ray, intersections);

  double reflectance = intersectionData.schlick();

  testReal(reflectance, 0.48873);
  }

  {
  DefaultWorld defaultWorld;

  Ray ray(Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2));

  PlaneP floor = std::make_shared<Plane>();

  floor->setTransform(Matrix4D::translation(0, -1, 0));
  floor->material().setReflective     (0.5);
  floor->material().setTransparency   (0.5);
  floor->material().setRefractiveIndex(1.5);

  defaultWorld.addObject(floor);

  SphereP ball = std::make_shared<Sphere>();

  ball->material().setColor(Color(1, 0, 0));
  ball->material().setAmbient(0.5);
  ball->setTransform(Matrix4D::translation(0, -3.5, -0.5));

  defaultWorld.addObject(ball);

  Intersections intersections { Intersection(sqrt(2), floor.get()) };

  IntersectionData intersectionData(intersections.at(0), ray, intersections);

  Color color = defaultWorld.shadeHit(intersectionData, 5);

  testColor(color, Color(0.933915, 0.696434, 0.692431));
  }
}

void
testCube()
{
  {
  CubeP cube = std::make_shared<Cube>();

  struct TestData {
    Ray    ray;
    double t1 { 0.0 };
    double t2 { 0.0 };

    TestData(const Ray &ray, double t1, double t2) :
     ray(ray), t1(t1), t2(t2) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Ray(Point( 5.0,  0.5,  0.0), Vector(-1,  0,  0)),  4, 6 },
    { Ray(Point(-5.0,  0.5,  0.0), Vector( 1,  0,  0)),  4, 6 },
    { Ray(Point( 0.5,  5.0,  0.0), Vector( 0, -1,  0)),  4, 6 },
    { Ray(Point( 0.5, -5.0,  0.0), Vector( 0,  1,  0)),  4, 6 },
    { Ray(Point( 0.5,  0.0,  5.0), Vector( 0,  0, -1)),  4, 6 },
    { Ray(Point( 0.5,  0.0, -5.0), Vector( 0,  0,  1)),  4, 6 },
    { Ray(Point( 0.0,  0.5,  0.0), Vector( 0,  0,  1)), -1, 1 }
  };

  for (const auto &testData : testDatas) {
    Intersections intersections = cube->intersect(testData.ray);

    testInt (intersections.count(), 2);
    testReal(intersections.at(0).t(), testData.t1);
    testReal(intersections.at(1).t(), testData.t2);
  }
  }

  {
  CubeP cube = std::make_shared<Cube>();

  struct TestData {
    Ray ray;

    TestData(const Ray &ray) :
     ray(ray) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Ray(Point(-2.0,  0.0,  0.0), Vector( 0.2673,  0.5345,  0.8018)) },
    { Ray(Point( 0.0, -2.0,  0.0), Vector( 0.8018,  0.2673,  0.5345)) },
    { Ray(Point( 0.0,  0.0, -2.0), Vector( 0.5345,  0.8018,  0.2673)) },
    { Ray(Point( 2.0,  0.0,  2.0), Vector( 0     ,  0     , -1     )) },
    { Ray(Point( 0.0,  2.0,  2.0), Vector( 0     , -1     ,  0     )) },
    { Ray(Point( 2.0,  2.0,  0.0), Vector(-1     ,  0     ,  0     )) }
  };

  for (const auto &testData : testDatas) {
    Intersections intersections = cube->intersect(testData.ray);

    testInt(intersections.count(), 0);
  }
  }

  {
  CubeP cube = std::make_shared<Cube>();

  struct TestData {
    Point  point;
    Vector normal;

    TestData(const Point &point, const Vector &normal) :
     point(point), normal(normal) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Point( 1.0,  0.5, -0.8), Vector( 1,  0,  0) },
    { Point(-1.0, -0.2,  0.9), Vector(-1,  0,  0) },
    { Point(-0.4,  1.0, -0.1), Vector( 0,  1,  0) },
    { Point( 0.3, -1.0, -0.7), Vector( 0, -1,  0) },
    { Point(-0.6,  0.3,  1.0), Vector( 0,  0,  1) },
    { Point( 0.4,  0.4, -1.0), Vector( 0,  0, -1) },
    { Point( 1.0,  1.0,  1.0), Vector( 1,  0,  0) },
    { Point(-1.0, -1.0, -1.0), Vector(-1,  0,  0) }
  };

  for (const auto &testData : testDatas) {
    Vector normal = cube->pointNormal(testData.point);

    testVector(testData.normal, normal);
  }
  }
}

void
testRenderCube()
{
  World world;

  auto checkerPattern  = std::make_shared<CheckerPattern >(Color::makeWhite(), Color::makeBlack());

  //--

  PlaneP floor = std::make_shared<Plane>();

  floor->material().setColor(Color(0.0, 0.0, 0.0));
  floor->material().setSpecular(0);
  floor->material().setPattern(checkerPattern);
  floor->material().setReflective(0.7);

  world.addObject(floor);

  //--

  PlaneP leftWall = std::make_shared<Plane>();

  leftWall->transform(Matrix4D::translation(0, 0, 5)*
                      Matrix4D::rotation(Matrix4D::AxisType::Y, -M_PI/4.0)*
                      Matrix4D::rotation(Matrix4D::AxisType::X,  M_PI/2.0));

  leftWall->material().setColor(Color(0.0, 0.0, 0.0));
  leftWall->material().setSpecular(0);
  leftWall->material().setPattern(checkerPattern);

  world.addObject(leftWall);

  //--

  PlaneP rightWall = std::make_shared<Plane>();

  rightWall->transform(Matrix4D::translation(0, 0, 5)*
                       Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0)*
                       Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/2.0));

  rightWall->material().setColor(Color(0.0, 0.0, 0.0));
  rightWall->material().setSpecular(0);
  rightWall->material().setPattern(checkerPattern);

  world.addObject(rightWall);

  //--

  CubeP middle = std::make_shared<Cube>();

  middle->transform(Matrix4D::translation(-0.5, 1, 0.5));

  middle->material().setColor(Color(0.8, 0.2, 0.2));
  middle->material().setDiffuse(0.3);
  middle->material().setSpecular(0.3);
  middle->material().setTransparency(0.9);
  middle->material().setReflective(0.9);
  middle->material().setRefractiveIndex(1.5);

  world.addObject(middle);

  //--

  CubeP right = std::make_shared<Cube>();

  right->transform(Matrix4D::translation(1.5, 0.5, -0.5)*
                   Matrix4D::scale(0.5, 0.5, 0.5));

  right->material().setColor(Color(0.2, 0.8, 0.2));
  right->material().setDiffuse(0.3);
  right->material().setSpecular(0.3);
  right->material().setTransparency(0.7);
  right->material().setReflective(0.7);
  right->material().setRefractiveIndex(1.5);

  world.addObject(right);

  //--

  CubeP left = std::make_shared<Cube>();

  left->transform(Matrix4D::translation(-1.5, 0.33, -0.75)*
                  Matrix4D::scale(0.33, 0.33, 0.33));

  left->material().setColor(Color(0.2, 0.2, 0.8));
  left->material().setDiffuse(0.3);
  left->material().setSpecular(0.3);
  left->material().setTransparency(0.5);
  left->material().setReflective(0.5);
  left->material().setRefractiveIndex(1.5);

  world.addObject(left);

  //---

  auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

  world.addLight(light);

  //---

  //Camera camera(100, 50, M_PI/3.0);
  Camera camera(512, 384, M_PI/3.0);

  camera.setTransform(viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

  Canvas canvas;

  render(canvas, camera, world);

  auto fs = std::ofstream("images/render_cube.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testCylinder()
{
  {
  CylinderP cylinder = std::make_shared<Cylinder>();

  struct TestData {
    Point  origin;
    Vector direction;

    TestData(const Point &origin, const Vector &direction) :
     origin(origin), direction(direction) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Point(1.0, 0.0,  0.0), Vector(0, 1, 0) },
    { Point(0.0, 0.0,  0.0), Vector(0, 1, 0) },
    { Point(0.0, 0.0, -5.0), Vector(1, 1, 1) }
  };

  for (const auto &testData : testDatas) {
    Vector direction = testData.direction.normalized();

    Ray ray(testData.origin, direction);

    Intersections intersections = cylinder->intersect(ray);

    testInt(intersections.count(), 0);
  }
  }

  {
  CylinderP cylinder = std::make_shared<Cylinder>();

  struct TestData {
    Point  origin;
    Vector direction;
    double t1 { 0.0 };
    double t2 { 0.0 };

    TestData(const Point &origin, const Vector &direction, double t1, double t2) :
     origin(origin), direction(direction), t1(t1), t2(t2) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Point(1.0, 0.0, -5.0), Vector(0.0, 0, 1), 5.000000, 5.000000 },
    { Point(0.0, 0.0, -5.0), Vector(0.0, 0, 1), 4.000000, 6.000000 },
    { Point(0.5, 0.0, -5.0), Vector(0.1, 1, 1), 6.807982, 7.088723 }
  };

  for (const auto &testData : testDatas) {
    Vector direction = testData.direction.normalized();

    Ray ray(testData.origin, direction);

    Intersections intersections = cylinder->intersect(ray);

    testInt (intersections.count(), 2);
    testReal(intersections.at(0).t(), testData.t1);
    testReal(intersections.at(1).t(), testData.t2);
  }
  }

  {
  CylinderP cylinder = std::make_shared<Cylinder>();

  struct TestData {
    Point  point;
    Vector normal;

    TestData(const Point &point, const Vector &normal) :
     point(point), normal(normal) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Point( 1.0,  0.0,  0.0), Vector( 1, 0,  0) },
    { Point( 0.0,  5.0, -1.0), Vector( 0, 0, -1) },
    { Point( 0.0, -2.0,  1.0), Vector( 0, 0,  1) },
    { Point(-1.0,  1.0,  0.0), Vector(-1, 0,  0) }
  };

  for (const auto &testData : testDatas) {
    Vector normal = cylinder->pointNormal(testData.point);

    testVector(testData.normal, normal);
  }
  }

  {
  CylinderP cylinder = std::make_shared<Cylinder>();

  testReal(cylinder->minimum(), -RayTrace::INFINITY());
  testReal(cylinder->maximum(),  RayTrace::INFINITY());
  }

  {
  CylinderP cylinder = std::make_shared<Cylinder>();

  cylinder->setMinimum(1);
  cylinder->setMaximum(2);

  struct TestData {
    Point  point;
    Vector direction;
    int    n { 0 };

    TestData(const Point &point, const Vector &direction, int n) :
     point(point), direction(direction), n(n) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Point(0.0, 1.5,  0.0), Vector(0.1, 1, 0), 0 },
    { Point(0.0, 3.0, -5.0), Vector(0.0, 0, 1), 0 },
    { Point(0.0, 0.0, -5.0), Vector(0.0, 0, 1), 0 },
    { Point(0.0, 2.0, -5.0), Vector(0.0, 0, 1), 0 },
    { Point(0.0, 1.0, -5.0), Vector(0.0, 0, 1), 0 },
    { Point(0.0, 1.5, -2.0), Vector(0.0, 0, 1), 2 }
  };

  for (const auto &testData : testDatas) {
    Vector direction = testData.direction.normalized();

    Ray ray(testData.point, direction);

    Intersections intersections = cylinder->intersect(ray);

    testInt (intersections.count(), testData.n);
  }
  }

  {
  CylinderP cylinder = std::make_shared<Cylinder>();

  testBool(cylinder->isClosed(), false);
  }

  {
  CylinderP cylinder = std::make_shared<Cylinder>();

  cylinder->setMinimum(1);
  cylinder->setMaximum(2);
  cylinder->setClosed(true);

  struct TestData {
    Point  point;
    Vector direction;
    int    n { 0 };

    TestData(const Point &point, const Vector &direction, int n) :
     point(point), direction(direction), n(n) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Point(0.0,  3.0,  0.0), Vector(0, -1, 0), 2 },
    { Point(0.0,  3.0, -2.0), Vector(0, -1, 2), 2 },
    { Point(0.0,  4.0, -2.0), Vector(0, -1, 1), 2 },
    { Point(0.0,  0.0, -2.0), Vector(0,  1, 2), 2 },
    { Point(0.0, -1.0, -2.0), Vector(0,  1, 1), 2 }
  };

  for (const auto &testData : testDatas) {
    Vector direction = testData.direction.normalized();

    Ray ray(testData.point, direction);

    Intersections intersections = cylinder->intersect(ray);

    testInt(intersections.count(), testData.n);
  }
  }

  {
  CylinderP cylinder = std::make_shared<Cylinder>();

  cylinder->setMinimum(1);
  cylinder->setMaximum(2);
  cylinder->setClosed(true);

  struct TestData {
    Point  point;
    Vector normal;

    TestData(const Point &point, const Vector &normal) :
     point(point), normal(normal) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Point(0.0, 1.0,  0.0), Vector(0, -1, 0) },
    { Point(0.5, 1.0,  0.0), Vector(0, -1, 0) },
    { Point(0.0, 1.0,  0.5), Vector(0, -1, 0) },
    { Point(0.0, 2.0,  0.0), Vector(0,  1, 0) },
    { Point(0.5, 2.0,  0.0), Vector(0,  1, 0) },
    { Point(0.0, 2.0,  0.5), Vector(0,  1, 0) }
  };

  for (const auto &testData : testDatas) {
    Vector normal = cylinder->pointNormal(testData.point);

    testVector(normal, testData.normal);
  }
  }
}

void
testRenderCylinder()
{
  World world;

  auto checkerPattern  = std::make_shared<CheckerPattern >(Color::makeWhite(), Color::makeBlack());

  //--

  PlaneP floor = std::make_shared<Plane>();

  floor->material().setColor(Color(0.0, 0.0, 0.0));
  floor->material().setSpecular(0);
  floor->material().setPattern(checkerPattern);
  floor->material().setReflective(0.7);

  world.addObject(floor);

  //--

  PlaneP leftWall = std::make_shared<Plane>();

  leftWall->transform(Matrix4D::translation(0, 0, 5)*
                      Matrix4D::rotation(Matrix4D::AxisType::Y, -M_PI/4.0)*
                      Matrix4D::rotation(Matrix4D::AxisType::X,  M_PI/2.0));

  leftWall->material().setColor(Color(0.0, 0.0, 0.0));
  leftWall->material().setSpecular(0);
  leftWall->material().setPattern(checkerPattern);

  world.addObject(leftWall);

  //--

  PlaneP rightWall = std::make_shared<Plane>();

  rightWall->transform(Matrix4D::translation(0, 0, 5)*
                       Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0)*
                       Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/2.0));

  rightWall->material().setColor(Color(0.0, 0.0, 0.0));
  rightWall->material().setSpecular(0);
  rightWall->material().setPattern(checkerPattern);

  world.addObject(rightWall);

  //--

  CylinderP middle = std::make_shared<Cylinder>();

  middle->setMinimum(0);
  middle->setMaximum(2);
  middle->setClosed(true);

  middle->transform(Matrix4D::translation(-0.5, 0, 0.5));

  middle->material().setColor(Color(0.8, 0.2, 0.2));
  middle->material().setDiffuse(0.3);
  middle->material().setSpecular(0.3);
  middle->material().setTransparency(0.9);
  middle->material().setReflective(0.9);
  middle->material().setRefractiveIndex(1.5);

  world.addObject(middle);

  //--

  CylinderP right = std::make_shared<Cylinder>();

  right->setMinimum(0);
  right->setMaximum(1.5);
  right->setClosed(true);

  right->transform(Matrix4D::translation(1.5, 0.0, -0.5)*
                   Matrix4D::scale(0.5, 1.0, 0.5));

  right->material().setColor(Color(0.2, 0.8, 0.2));
  right->material().setDiffuse(0.3);
  right->material().setSpecular(0.3);
  right->material().setTransparency(0.7);
  right->material().setReflective(0.7);
  right->material().setRefractiveIndex(1.5);

  world.addObject(right);

  //--

  CylinderP left = std::make_shared<Cylinder>();

  left->setMinimum(0);
  left->setMaximum(1);
  left->setClosed(true);

  left->transform(Matrix4D::translation(-1.5, 0.0, -0.75)*
                  Matrix4D::scale(0.33, 1.0, 0.33));

  left->material().setColor(Color(0.2, 0.2, 0.8));
  left->material().setDiffuse(0.3);
  left->material().setSpecular(0.3);
  left->material().setTransparency(0.5);
  left->material().setReflective(0.5);
  left->material().setRefractiveIndex(1.5);

  world.addObject(left);

  //---

  auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

  world.addLight(light);

  //---

  //Camera camera(100, 50, M_PI/3.0);
  Camera camera(512, 384, M_PI/3.0);

  camera.setTransform(viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

  Canvas canvas;

  render(canvas, camera, world);

  auto fs = std::ofstream("images/render_cylinder.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testCone()
{
  {
  ConeP cone = std::make_shared<Cone>();

  struct TestData {
    Point  origin;
    Vector direction;
    double t1 { 0.0 };
    double t2 { 0.0 };

    TestData(const Point &origin, const Vector &direction, double t1, double t2) :
     origin(origin), direction(direction), t1(t1), t2(t2) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Point(0.0, 0.0, -5.0), Vector( 0.0,  0, 1), 5.000000,  5.000000 },
    { Point(0.0, 0.0, -5.0), Vector( 1.0,  1, 1), 8.660254,  8.660254 },
    { Point(1.0, 1.0, -5.0), Vector(-0.5, -1, 1), 4.550056, 49.449944 }
  };

  for (const auto &testData : testDatas) {
    Vector direction = testData.direction.normalized();

    Ray ray(testData.origin, direction);

    Intersections intersections = cone->intersect(ray);

    testInt (intersections.count(), 2);
    testReal(intersections.at(0).t(), testData.t1);
    testReal(intersections.at(1).t(), testData.t2);
  }
  }

  {
  ConeP cone = std::make_shared<Cone>();

  Vector direction = Vector(0, 1, 1).normalized();

  Ray ray(Point(0, 0, -1), direction);

  Intersections intersections = cone->intersect(ray);

  testInt (intersections.count(), 1);
  testReal(intersections.at(0).t(), 0.3535534);
  }

  {
  ConeP cone = std::make_shared<Cone>();

  cone->setMinimum(-0.5);
  cone->setMaximum(0.5);
  cone->setClosed(true);

  struct TestData {
    Point  origin;
    Vector direction;
    int    n { 0 };

    TestData(const Point &origin, const Vector &direction, int n) :
     origin(origin), direction(direction), n(n) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Point(0.0, 0.0, -5.00), Vector(0, 1, 0), 0 },
    { Point(0.0, 0.0, -0.25), Vector(0, 1, 1), 2 },
    { Point(0.0, 0.0, -0.25), Vector(0, 1, 0), 4 }
  };

  for (const auto &testData : testDatas) {
    Vector direction = testData.direction.normalized();

    Ray ray(testData.origin, direction);

    Intersections intersections = cone->intersect(ray);

    testInt(intersections.count(), testData.n);
  }
  }

  {
  ConeP cone = std::make_shared<Cone>();

  struct TestData {
    Point  point;
    Vector normal;

    TestData(const Point &point, const Vector &normal) :
     point(point), normal(normal) {
    }
  };

  using TestDatas = std::vector<TestData>;

  TestDatas testDatas = {
    { Point( 0.0,  0.0, 0.0), Vector(       0.0,          0, 0.0) },
    { Point( 1.0,  1.0, 1.0), Vector(       0.5, -sqrt(2)/2, 0.5) },
    { Point(-1.0, -1.0, 0.0), Vector(-sqrt(2)/2,  sqrt(2)/2, 0.0) }
  };

  for (const auto &testData : testDatas) {
    Vector normal = cone->pointNormal(testData.point);

    testVector(normal, testData.normal);
  }
  }
}

void
testRenderCone()
{
  World world;

  auto checkerPattern  = std::make_shared<CheckerPattern >(Color::makeWhite(), Color::makeBlack());

  //--

  PlaneP floor = std::make_shared<Plane>();

  floor->material().setColor(Color(0.0, 0.0, 0.0));
  floor->material().setSpecular(0);
  floor->material().setPattern(checkerPattern);
  floor->material().setReflective(0.7);

  world.addObject(floor);

  //--

  PlaneP leftWall = std::make_shared<Plane>();

  leftWall->transform(Matrix4D::translation(0, 0, 5)*
                      Matrix4D::rotation(Matrix4D::AxisType::Y, -M_PI/4.0)*
                      Matrix4D::rotation(Matrix4D::AxisType::X,  M_PI/2.0));

  leftWall->material().setColor(Color(0.0, 0.0, 0.0));
  leftWall->material().setSpecular(0);
  leftWall->material().setPattern(checkerPattern);

  world.addObject(leftWall);

  //--

  PlaneP rightWall = std::make_shared<Plane>();

  rightWall->transform(Matrix4D::translation(0, 0, 5)*
                       Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/4.0)*
                       Matrix4D::rotation(Matrix4D::AxisType::X, M_PI/2.0));

  rightWall->material().setColor(Color(0.0, 0.0, 0.0));
  rightWall->material().setSpecular(0);
  rightWall->material().setPattern(checkerPattern);

  world.addObject(rightWall);

  //--

  ConeP middle = std::make_shared<Cone>();

  middle->setMinimum(0);
  middle->setMaximum(2);
  middle->setClosed(true);

  middle->transform(Matrix4D::translation(-0.5, 0, 0.5));

  middle->material().setColor(Color(0.8, 0.2, 0.2));
  middle->material().setDiffuse(0.3);
  middle->material().setSpecular(0.3);
  middle->material().setTransparency(0.9);
  middle->material().setReflective(0.9);
  middle->material().setRefractiveIndex(1.5);

  world.addObject(middle);

  //--

  ConeP right = std::make_shared<Cone>();

  right->setMinimum(0);
  right->setMaximum(1.5);
  right->setClosed(true);

  right->transform(Matrix4D::translation(1.5, 0.0, -0.5)*
                   Matrix4D::scale(0.5, 1.0, 0.5));

  right->material().setColor(Color(0.2, 0.8, 0.2));
  right->material().setDiffuse(0.3);
  right->material().setSpecular(0.3);
  right->material().setTransparency(0.7);
  right->material().setReflective(0.7);
  right->material().setRefractiveIndex(1.5);

  world.addObject(right);

  //--

  ConeP left = std::make_shared<Cone>();

  left->setMinimum(0);
  left->setMaximum(1);
  left->setClosed(true);

  left->transform(Matrix4D::translation(-1.5, 0.0, -0.75)*
                  Matrix4D::scale(0.33, 1.0, 0.33));

  left->material().setColor(Color(0.2, 0.2, 0.8));
  left->material().setDiffuse(0.3);
  left->material().setSpecular(0.3);
  left->material().setTransparency(0.5);
  left->material().setReflective(0.5);
  left->material().setRefractiveIndex(1.5);

  world.addObject(left);

  //---

  auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

  world.addLight(light);

  //---

  //Camera camera(100, 50, M_PI/3.0);
  Camera camera(512, 384, M_PI/3.0);

  camera.setTransform(viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

  Canvas canvas;

  render(canvas, camera, world);

  auto fs = std::ofstream("images/render_cone.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
testGroup()
{
  {
  GroupP group = std::make_shared<Group>();

  testMatrix(group->transform(), Matrix4D::identity());

  testInt(group->children().size(), 0);

  SphereP sphere = std::make_shared<Sphere>();

  testPtr(sphere->parent(), nullptr);

  group->addObject(sphere);

  testInt(group->children().size(), 1);

  testPtr(group->children()[0].get(), sphere.get());

  testPtr(sphere->parent(), group.get());
  }

  {
  GroupP group = std::make_shared<Group>();

  Ray ray(Point(0, 0, 0), Vector(0, 0, 1));

  Intersections intersections = group->intersect(ray);

  testInt(intersections.count(), 0);
  }

  {
  GroupP group = std::make_shared<Group>();

  SphereP sphere1 = std::make_shared<Sphere>();
  SphereP sphere2 = std::make_shared<Sphere>();

  sphere2->setTransform(Matrix4D::translation(0, 0, -3));

  SphereP sphere3 = std::make_shared<Sphere>();

  sphere3->setTransform(Matrix4D::translation(5, 0, 0));

  group->addObject(sphere1);
  group->addObject(sphere2);
  group->addObject(sphere3);

  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

  Intersections intersections = group->intersect(ray);

  testInt(intersections.count(), 4);
  testPtr(intersections.at(0).object(), sphere2.get());
  testPtr(intersections.at(1).object(), sphere2.get());
  testPtr(intersections.at(2).object(), sphere1.get());
  testPtr(intersections.at(3).object(), sphere1.get());
  }

  {
  GroupP group = std::make_shared<Group>();

  group->setTransform(Matrix4D::scale(2, 2, 2));

  SphereP sphere = std::make_shared<Sphere>();

  sphere->setTransform(Matrix4D::translation(5, 0, 0));

  group->addObject(sphere);

  Ray ray(Point(10, 0, -10), Vector(0, 0, 1));

  Intersections intersections = group->intersect(ray);

  testInt(intersections.count(), 2);
  }

  {
  GroupP group1 = std::make_shared<Group>();

  group1->setTransform(Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/2.0));

  GroupP group2 = std::make_shared<Group>();

  group2->setTransform(Matrix4D::scale(2, 2, 2));

  group1->addObject(group2);

  SphereP sphere = std::make_shared<Sphere>();

  sphere->setTransform(Matrix4D::translation(5, 0, 0));

  group2->addObject(sphere);

  Point p = sphere->transformPoint(Point(-2, 0, -10));

  testPoint(p, Point(0, 0, -1));
  }

  {
  GroupP group1 = std::make_shared<Group>();

  group1->setTransform(Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/2.0));

  GroupP group2 = std::make_shared<Group>();

  group2->setTransform(Matrix4D::scale(1, 2, 3));

  group1->addObject(group2);

  SphereP sphere = std::make_shared<Sphere>();

  sphere->setTransform(Matrix4D::translation(5, 0, 0));

  group2->addObject(sphere);

  Vector n = sphere->transformNormal(Vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));

  testVector(n, Vector(0.2857143, 0.4285714, -0.8571429));
  }

  {
  GroupP group1 = std::make_shared<Group>();

  group1->setTransform(Matrix4D::rotation(Matrix4D::AxisType::Y, M_PI/2.0));

  GroupP group2 = std::make_shared<Group>();

  group2->setTransform(Matrix4D::scale(1, 2, 3));

  group1->addObject(group2);

  SphereP sphere = std::make_shared<Sphere>();

  sphere->setTransform(Matrix4D::translation(5, 0, 0));

  group2->addObject(sphere);

  Vector n = sphere->pointNormal(Point(1.732051, 1.154701, -5.577350));

  testVector(n, Vector(0.2857143, 0.4285714, -0.8571429));
  }
}

void
testRenderGroup()
{
  auto hexagonCorner = []() {
    SphereP corner = std::make_shared<Sphere>();

    corner->setTransform(Matrix4D::translation(0, 0, -1)*
                         Matrix4D::scale(0.25, 0.25, 0.25));

    return corner;
  };

  auto hexagonEdge = []() {
    CylinderP edge = std::make_shared<Cylinder>();

    edge->setMinimum(0.0);
    edge->setMaximum(1.0);

    edge->setTransform(Matrix4D::translation(0, 0, -1)*
                       Matrix4D::rotation(Matrix4D::AxisType::Y, -M_PI/6.0)*
                       Matrix4D::rotation(Matrix4D::AxisType::Z, -M_PI/2.0)*
                       Matrix4D::scale(0.25, 1.00, 0.25));

    return edge;
  };

  auto hexagonSide = [&]() {
    GroupP side = std::make_shared<Group>();

    side->addObject(hexagonCorner());
    side->addObject(hexagonEdge  ());

    return side;
  };

  auto hexagon = [&]() {
    GroupP hex = std::make_shared<Group>();

    for (int n = 0; n < 5; ++n) {
      GroupP side = hexagonSide();

      side->setTransform(Matrix4D::rotation(Matrix4D::AxisType::Y, n*M_PI/3.0));

      hex->addObject(side);
    }

    return hex;
  };

  //----

  World world;

  //--

  GroupP hex = hexagon();

  world.addObject(hex);

  //--

  auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Color(1, 1, 1));

  world.addLight(light);

  //---

  //Camera camera(100, 50, M_PI/3.0);
  Camera camera(512, 384, M_PI/3.0);

  camera.setTransform(viewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

  Canvas canvas;

  render(canvas, camera, world);

  auto fs = std::ofstream("images/render_group.ppm", std::ofstream::out);

  canvas.writePPM(fs);
}

void
tesTriangle()
{
  {
  Point p1( 0, 1, 0);
  Point p2(-1, 0, 0);
  Point p3( 1, 0, 0);

  Triangle triangle(p1, p2, p3);

  testPoint(triangle.p1(), p1);
  testPoint(triangle.p2(), p2);
  testPoint(triangle.p3(), p3);

  testVector(triangle.e1(), Vector(-1, -1, 0));
  testVector(triangle.e2(), Vector( 1, -1, 0));

  testVector(triangle.normal(), Vector(0, 0, -1));
  }
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

  //testCanvasClock();

  //--

  //testRay();

  //testCanvasRaySphere();

  //testSphereNormal();

  //--

  //testLight();

  //testMaterial();

  //testLighting();

  //testCanvasLightingRaySphere();

  //---

  //testWorld();

  //testCamera();

  //testRender1();

  //testRender2();

  //---

  //testShadow();

  //---

  //testShape();

  //testRenderShape();

  //---

  //testStripedPattern();

  //testPattern();

  //testGradientPattern();

  //testRingPattern();

  //testCheckerPattern();

  //testRenderPattern();

  //testTransformPattern();

  //---

  //testReflect();

  //testRenderReflect();

  //---

  //testRefract();

  //testRefractN1N2();

  //testRenderRefract();

  //---

  //testSchlick();

  //testRenderRefract();

  //---

  //testCube();

  //testRenderCube();

  //---

  //testCylinder();

  //testRenderCylinder();

  //---

  //testCone();

  //testRenderCone();

  //---

  //testGroup();

  //testRenderGroup();

  //---

  tesTriangle();

  return 0;
}
