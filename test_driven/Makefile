CDEBUG = -g -Wall -fsanitize=address
LDEBUG = -g -lasan

PROG = CQRayTraceTest

CPP_SRC = \
CQRayTraceTest.cpp \
Camera.cpp \
Canvas.cpp \
Color.cpp \
IntersectionData.cpp \
Light.cpp \
Material.cpp \
Matrix4D.cpp \
Object.cpp \
Pattern.cpp \
Ray.cpp \
RayTrace.cpp \
Sphere.cpp \
World.cpp \

EXTRA_CFLAGS = \

include $(MAKE_DIR)/bin.mk

CQRayTraceTest.h: Canvas.h Color.h Matrix2D.h Matrix3D.h Matrix4D.h Point.h Tuple.h Vector.h
