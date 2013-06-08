######################################################################
# Automatically generated by qmake (2.01a) Thu May 16 08:02:14 2013
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .

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
CXML.cpp \
CXMLComment.cpp \
CXMLExecute.cpp \
CXMLNamedChar.cpp \
CXMLParser.cpp \
CXMLTag.cpp \
CXMLText.cpp \
CXMLToken.cpp \
CXMLVisitor.cpp \
CRGBName.cpp \
CThread.cpp \
CSample.cpp \
CSolidNoise.cpp \
CRegExp.cpp \
pthread_rdwr.c \

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
CRGBName.h \
CSample.h \
CShape3D.h \
CSolidNoise.h \
CSphere3D.h \
CSquare3D.h \
CThread.h \
CTransform2D.h \
CTriangle3D.h \
CXMLComment.h \
CXMLExecute.h \
CXML.h \
CXMLLib.h \
CXMLNamedChar.h \
CXMLParser.h \
CXMLTag.h \
CXMLText.h \
CXMLToken.h \
CXMLTypes.h \
CXMLVisitor.h \
CRegExp.h \
pthread_rdwr.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
../include \
../../CImageLib/include \
../../CFile/include \
../../CMath/include \
../../CStrUtil/include \
../../COS/include \
../../CUtil/include \
.

unix:LIBS += \
-L$$LIB_DIR \
-L../../CImageLib/lib \
-L../../CFile/lib \
-L../../CMath/lib \
-L../../CStrUtil/lib \
-L../../COS/lib \
-lCImageLib \
-lCFile \
-lCStrUtil \
-lCOS \
-ltre -lpng -ljpeg
