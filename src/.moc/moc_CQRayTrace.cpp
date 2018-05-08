/****************************************************************************
** Meta object code from reading C++ file 'CQRayTrace.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CQRayTrace.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CQRayTrace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CQRayTrace_t {
    QByteArrayData data[17];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQRayTrace_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQRayTrace_t qt_meta_stringdata_CQRayTrace = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CQRayTrace"
QT_MOC_LITERAL(1, 11, 10), // "updateSlot"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "redrawSlot"
QT_MOC_LITERAL(4, 34, 5), // "width"
QT_MOC_LITERAL(5, 40, 6), // "height"
QT_MOC_LITERAL(6, 47, 10), // "numSamples"
QT_MOC_LITERAL(7, 58, 4), // "minT"
QT_MOC_LITERAL(8, 63, 4), // "maxT"
QT_MOC_LITERAL(9, 68, 2), // "bg"
QT_MOC_LITERAL(10, 71, 2), // "fg"
QT_MOC_LITERAL(11, 74, 12), // "reflectDepth"
QT_MOC_LITERAL(12, 87, 12), // "refractDepth"
QT_MOC_LITERAL(13, 100, 10), // "alphaDepth"
QT_MOC_LITERAL(14, 111, 13), // "smoothNormals"
QT_MOC_LITERAL(15, 125, 7), // "changed"
QT_MOC_LITERAL(16, 133, 5) // "trace"

    },
    "CQRayTrace\0updateSlot\0\0redrawSlot\0"
    "width\0height\0numSamples\0minT\0maxT\0bg\0"
    "fg\0reflectDepth\0refractDepth\0alphaDepth\0"
    "smoothNormals\0changed\0trace"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQRayTrace[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
      13,   26, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       4, QMetaType::Int, 0x00095001,
       5, QMetaType::Int, 0x00095001,
       6, QMetaType::Int, 0x00095103,
       7, QMetaType::Double, 0x00095001,
       8, QMetaType::Double, 0x00095001,
       9, QMetaType::QColor, 0x00095103,
      10, QMetaType::QColor, 0x00095103,
      11, QMetaType::Int, 0x00095103,
      12, QMetaType::Int, 0x00095103,
      13, QMetaType::Int, 0x00095103,
      14, QMetaType::Bool, 0x00095103,
      15, QMetaType::Bool, 0x00095001,
      16, QMetaType::Bool, 0x00095103,

       0        // eod
};

void CQRayTrace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQRayTrace *_t = static_cast<CQRayTrace *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSlot(); break;
        case 1: _t->redrawSlot(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        CQRayTrace *_t = static_cast<CQRayTrace *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->width(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->height(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->numSamples(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->minT(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->maxT(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->bg(); break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->fg(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->reflectDepth(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->refractDepth(); break;
        case 9: *reinterpret_cast< int*>(_v) = _t->alphaDepth(); break;
        case 10: *reinterpret_cast< bool*>(_v) = _t->isSmoothNormals(); break;
        case 11: *reinterpret_cast< bool*>(_v) = _t->isChanged(); break;
        case 12: *reinterpret_cast< bool*>(_v) = _t->isTrace(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CQRayTrace *_t = static_cast<CQRayTrace *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setNumSamples(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setBg(*reinterpret_cast< QColor*>(_v)); break;
        case 6: _t->setFg(*reinterpret_cast< QColor*>(_v)); break;
        case 7: _t->setReflectDepth(*reinterpret_cast< int*>(_v)); break;
        case 8: _t->setRefractDepth(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->setAlphaDepth(*reinterpret_cast< int*>(_v)); break;
        case 10: _t->setSmoothNormals(*reinterpret_cast< bool*>(_v)); break;
        case 12: _t->setTrace(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

const QMetaObject CQRayTrace::staticMetaObject = {
    { &CQMainWindow::staticMetaObject, qt_meta_stringdata_CQRayTrace.data,
      qt_meta_data_CQRayTrace,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQRayTrace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQRayTrace::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQRayTrace.stringdata0))
        return static_cast<void*>(const_cast< CQRayTrace*>(this));
    return CQMainWindow::qt_metacast(_clname);
}

int CQRayTrace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CQMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 13;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_CQRayTraceCamera_t {
    QByteArrayData data[14];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQRayTraceCamera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQRayTraceCamera_t qt_meta_stringdata_CQRayTraceCamera = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CQRayTraceCamera"
QT_MOC_LITERAL(1, 17, 2), // "z1"
QT_MOC_LITERAL(2, 20, 2), // "z2"
QT_MOC_LITERAL(3, 23, 11), // "perspective"
QT_MOC_LITERAL(4, 35, 1), // "x"
QT_MOC_LITERAL(5, 37, 1), // "y"
QT_MOC_LITERAL(6, 39, 1), // "z"
QT_MOC_LITERAL(7, 41, 5), // "lookX"
QT_MOC_LITERAL(8, 47, 5), // "lookY"
QT_MOC_LITERAL(9, 53, 5), // "lookZ"
QT_MOC_LITERAL(10, 59, 3), // "upX"
QT_MOC_LITERAL(11, 63, 3), // "upY"
QT_MOC_LITERAL(12, 67, 3), // "upZ"
QT_MOC_LITERAL(13, 71, 3) // "fov"

    },
    "CQRayTraceCamera\0z1\0z2\0perspective\0x\0"
    "y\0z\0lookX\0lookY\0lookZ\0upX\0upY\0upZ\0fov"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQRayTraceCamera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      13,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Double, 0x00095103,
       2, QMetaType::Double, 0x00095103,
       3, QMetaType::Bool, 0x00095103,
       4, QMetaType::Double, 0x00095103,
       5, QMetaType::Double, 0x00095103,
       6, QMetaType::Double, 0x00095103,
       7, QMetaType::Double, 0x00095103,
       8, QMetaType::Double, 0x00095103,
       9, QMetaType::Double, 0x00095103,
      10, QMetaType::Double, 0x00095103,
      11, QMetaType::Double, 0x00095103,
      12, QMetaType::Double, 0x00095103,
      13, QMetaType::Double, 0x00095103,

       0        // eod
};

void CQRayTraceCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        CQRayTraceCamera *_t = static_cast<CQRayTraceCamera *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->z1(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->z2(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isPerspective(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->x(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->y(); break;
        case 5: *reinterpret_cast< double*>(_v) = _t->z(); break;
        case 6: *reinterpret_cast< double*>(_v) = _t->lookX(); break;
        case 7: *reinterpret_cast< double*>(_v) = _t->lookY(); break;
        case 8: *reinterpret_cast< double*>(_v) = _t->lookZ(); break;
        case 9: *reinterpret_cast< double*>(_v) = _t->upX(); break;
        case 10: *reinterpret_cast< double*>(_v) = _t->upY(); break;
        case 11: *reinterpret_cast< double*>(_v) = _t->upZ(); break;
        case 12: *reinterpret_cast< double*>(_v) = _t->fov(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CQRayTraceCamera *_t = static_cast<CQRayTraceCamera *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setZ1(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setZ2(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setPerspective(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setX(*reinterpret_cast< double*>(_v)); break;
        case 4: _t->setY(*reinterpret_cast< double*>(_v)); break;
        case 5: _t->setZ(*reinterpret_cast< double*>(_v)); break;
        case 6: _t->setLookX(*reinterpret_cast< double*>(_v)); break;
        case 7: _t->setLookY(*reinterpret_cast< double*>(_v)); break;
        case 8: _t->setLookZ(*reinterpret_cast< double*>(_v)); break;
        case 9: _t->setUpX(*reinterpret_cast< double*>(_v)); break;
        case 10: _t->setUpY(*reinterpret_cast< double*>(_v)); break;
        case 11: _t->setUpZ(*reinterpret_cast< double*>(_v)); break;
        case 12: _t->setFov(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CQRayTraceCamera::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CQRayTraceCamera.data,
      qt_meta_data_CQRayTraceCamera,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQRayTraceCamera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQRayTraceCamera::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQRayTraceCamera.stringdata0))
        return static_cast<void*>(const_cast< CQRayTraceCamera*>(this));
    return QObject::qt_metacast(_clname);
}

int CQRayTraceCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 13;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 13;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_CQRayTraceLight_t {
    QByteArrayData data[5];
    char stringdata0[28];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQRayTraceLight_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQRayTraceLight_t qt_meta_stringdata_CQRayTraceLight = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CQRayTraceLight"
QT_MOC_LITERAL(1, 16, 1), // "x"
QT_MOC_LITERAL(2, 18, 1), // "y"
QT_MOC_LITERAL(3, 20, 1), // "z"
QT_MOC_LITERAL(4, 22, 5) // "color"

    },
    "CQRayTraceLight\0x\0y\0z\0color"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQRayTraceLight[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Double, 0x00095103,
       2, QMetaType::Double, 0x00095103,
       3, QMetaType::Double, 0x00095103,
       4, QMetaType::QColor, 0x00095103,

       0        // eod
};

void CQRayTraceLight::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        CQRayTraceLight *_t = static_cast<CQRayTraceLight *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->x(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->y(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->z(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CQRayTraceLight *_t = static_cast<CQRayTraceLight *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setX(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setY(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setZ(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CQRayTraceLight::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CQRayTraceLight.data,
      qt_meta_data_CQRayTraceLight,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQRayTraceLight::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQRayTraceLight::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQRayTraceLight.stringdata0))
        return static_cast<void*>(const_cast< CQRayTraceLight*>(this));
    return QObject::qt_metacast(_clname);
}

int CQRayTraceLight::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_CQRayTraceShape_t {
    QByteArrayData data[8];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQRayTraceShape_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQRayTraceShape_t qt_meta_stringdata_CQRayTraceShape = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CQRayTraceShape"
QT_MOC_LITERAL(1, 16, 2), // "id"
QT_MOC_LITERAL(2, 19, 5), // "alpha"
QT_MOC_LITERAL(3, 25, 7), // "reflect"
QT_MOC_LITERAL(4, 33, 7), // "refract"
QT_MOC_LITERAL(5, 41, 12), // "refractIndex"
QT_MOC_LITERAL(6, 54, 11), // "ignoreLight"
QT_MOC_LITERAL(7, 66, 5) // "color"

    },
    "CQRayTraceShape\0id\0alpha\0reflect\0"
    "refract\0refractIndex\0ignoreLight\0color"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQRayTraceShape[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       7,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095001,
       2, QMetaType::Double, 0x00095103,
       3, QMetaType::Double, 0x00095103,
       4, QMetaType::Double, 0x00095103,
       5, QMetaType::Double, 0x00095103,
       6, QMetaType::Bool, 0x00095103,
       7, QMetaType::QColor, 0x00095103,

       0        // eod
};

void CQRayTraceShape::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        CQRayTraceShape *_t = static_cast<CQRayTraceShape *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->id(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->alpha(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->reflect(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->refract(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->refractIndex(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->ignoreLight(); break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CQRayTraceShape *_t = static_cast<CQRayTraceShape *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setAlpha(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setReflect(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setRefract(*reinterpret_cast< double*>(_v)); break;
        case 4: _t->setRefractIndex(*reinterpret_cast< double*>(_v)); break;
        case 5: _t->setIgnoreLight(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CQRayTraceShape::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CQRayTraceShape.data,
      qt_meta_data_CQRayTraceShape,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQRayTraceShape::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQRayTraceShape::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQRayTraceShape.stringdata0))
        return static_cast<void*>(const_cast< CQRayTraceShape*>(this));
    return QObject::qt_metacast(_clname);
}

int CQRayTraceShape::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
