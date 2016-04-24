TEMPLATE = app

QT += widgets

TARGET = CQRayTrace

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++11

MOC_DIR = .moc

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
COctTree.h \
CSample.h \
CSolidNoise.h \

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
