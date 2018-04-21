TEMPLATE = app

QT += widgets

TARGET = CQRayTrace

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++14

MOC_DIR = .moc

CONFIG += debug

# Input
SOURCES += \
CQRayTrace.cpp \
CRayBox.cpp \
CRayCone.cpp \
CRayCube.cpp \
CRayCylinder.cpp \
CRayDisk.cpp \
CRayHyperboloid.cpp \
CRayImageTexture.cpp \
CRayMandelbrotTexture.cpp \
CRayMarbleTexture.cpp \
CRayNoiseTexture.cpp \
CRayParaboloid.cpp \
CRayPlane.cpp \
CRayShape.cpp \
CRaySphere.cpp \
CRayTraceCamera.cpp \
CRayTrace.cpp \
CRayTraceLight.cpp \
CRayTraceXML.cpp \
CRayTriangle.cpp \
\
CSample.cpp \
CSolidNoise.cpp \

HEADERS += \
CQRayTrace.h \
CRayBox.h \
CRayCone.h \
CRayCube.h \
CRayCylinder.h \
CRayDifferential.h \
CRayDisk.h \
CRayDynamicShape.h \
CRayDynamicSphere.h \
CRay.h \
CRayHitData.h \
CRayHyperboloid.h \
CRayImageTexture.h \
CRayMandelbrotTexture.h \
CRayMarbleTexture.h \
CRayNoiseTexture.h \
CRayParaboloid.h \
CRayPlane.h \
CRayShape.h \
CRayShapeLib.h \
CRaySimpleTexture.h \
CRaySphere.h \
CRayTexture.h \
CRayTraceCamera.h \
CRayTrace.h \
CRayTraceLight.h \
CRayTraceShapeData.h \
CRayTraceXML.h \
CRayTriangle.h \
\
COctTree.h \
CSample.h \
CSolidNoise.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
../include \
../../CQUtil/include \
../../CQPropertyTree/include \
../../CXML/include \
../../CImportModel/include \
../../CGeometry3D/include \
../../CFractal/include \
../../CImageLib/include \
../../CFont/include \
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
-L../../CQPropertyTree/lib \
-L../../CQUtil/lib \
-L../../CXML/lib \
-L../../CImportModel/lib \
-L../../CGeometry3D/lib \
-L../../CFractal/lib \
-L../../CConfig/lib \
-L../../CImageLib/lib \
-L../../CFont/lib \
-L../../CThread/lib \
-L../../CFileUtil/lib \
-L../../CFile/lib \
-L../../CMath/lib \
-L../../CRegExp/lib \
-L../../CStrUtil/lib \
-L../../CRGBName/lib \
-L../../CUtil/lib \
-L../../COS/lib \
-lCQPropertyTree \
-lCQUtil \
-lCXML \
-lCImportModel \
-lCGeometry3D \
-lCFractal \
-lCConfig \
-lCImageLib \
-lCFont \
-lCThread \
-lCFileUtil \
-lCFile \
-lCMath \
-lCRegExp \
-lCStrUtil \
-lCRGBName \
-lCUtil \
-lCOS \
-ltre -lpng -ljpeg
