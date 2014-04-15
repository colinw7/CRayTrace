TEMPLATE = app

TARGET = CQRayTrace

DEPENDPATH += .

QT += widgets

CONFIG += debug

# Input
SOURCES += \
CQRayTrace.cpp \
CRayTrace.cpp \
CRayTraceCamera.cpp \
CRayTraceLight.cpp \
CRayBox.cpp \
CRayCone.cpp \
CRayCube.cpp \
CRayCylinder.cpp \
CRayDisk.cpp \
CRayHyperboloid.cpp \
CRayParaboloid.cpp \
CRayPlane.cpp \
CRaySphere.cpp \
CRayTraceXML.cpp \
CRayTriangle.cpp \
CRayNoiseTexture.cpp \
CRayMarbleTexture.cpp \
CRayImageTexture.cpp \
CSample.cpp \
CSolidNoise.cpp \

HEADERS += \
CQRayTrace.h \
CRayTrace.h \
CRayTraceCamera.h \
CRayTraceLight.h \
CRayTraceXML.h \
CRayBox.h \
CRayCone.h \
CRayCube.h \
CRayCylinder.h \
CRayDisk.h \
CRay.h \
CRayHitData.h \
CRayHyperboloid.h \
CRayImageTexture.h \
CRayMarbleTexture.h \
CRayNoiseTexture.h \
CRayParaboloid.h \
CRayPlane.h \
CRayShape.h \
CRayShapeLib.h \
CRaySimpleTexture.h \
CRaySphere.h \
CRayTexture.h \
CRayTraceShapeData.h \
CRayTriangle.h \
CBox3D.h \
CCone3D.h \
CCube3D.h \
CCylinder3D.h \
CDisk3D.h \
CHyperboloid3D.h \
CMathGeom3D.h \
CNPlane3D.h \
COctTree.h \
CParaboloid3D.h \
CPlane3D.h \
CSample.h \
CShape3D.h \
CSolidNoise.h \
CSphere3D.h \
CSquare3D.h \
CTriangle3D.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
../include \
../../CXML/include \
../../CImageLib/include \
../../CThread/include \
../../CFile/include \
../../CMath/include \
../../CRegExp/include \
../../CStrUtil/include \
../../CRGBName/include \
../../COS/include \
../../CUtil/include \
.

unix:LIBS += \
-L$$LIB_DIR \
-L../../CXML/lib \
-L../../CImageLib/lib \
-L../../CThread/lib \
-L../../CFile/lib \
-L../../CMath/lib \
-L../../CRegExp/lib \
-L../../CStrUtil/lib \
-L../../CRGBName/lib \
-L../../COS/lib \
-lCXML \
-lCImageLib \
-lCThread \
-lCFile \
-lCRegExp \
-lCStrUtil \
-lCRGBName \
-lCOS \
-ltre -lpng -ljpeg
