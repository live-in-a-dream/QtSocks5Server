/****************************************************************************
** Meta object code from reading C++ file 'Socks5Connected.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../socks5/Socks5Connected.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Socks5Connected.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Socks5Connected_t {
    QByteArrayData data[8];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Socks5Connected_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Socks5Connected_t qt_meta_stringdata_Socks5Connected = {
    {
QT_MOC_LITERAL(0, 0, 15), // "Socks5Connected"
QT_MOC_LITERAL(1, 16, 20), // "remtoSocketConnected"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 20), // "remtoSocketReadyRead"
QT_MOC_LITERAL(4, 59, 30), // "connectRemtoSocks5Disconnected"
QT_MOC_LITERAL(5, 90, 16), // "remtoSocketError"
QT_MOC_LITERAL(6, 107, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(7, 136, 22) // "connectSocks5ReadyRead"

    },
    "Socks5Connected\0remtoSocketConnected\0"
    "\0remtoSocketReadyRead\0"
    "connectRemtoSocks5Disconnected\0"
    "remtoSocketError\0QAbstractSocket::SocketError\0"
    "connectSocks5ReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Socks5Connected[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,

       0        // eod
};

void Socks5Connected::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Socks5Connected *_t = static_cast<Socks5Connected *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->remtoSocketConnected(); break;
        case 1: _t->remtoSocketReadyRead(); break;
        case 2: _t->connectRemtoSocks5Disconnected(); break;
        case 3: _t->remtoSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->connectSocks5ReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject Socks5Connected::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Socks5Connected.data,
      qt_meta_data_Socks5Connected,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Socks5Connected::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Socks5Connected::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Socks5Connected.stringdata0))
        return static_cast<void*>(const_cast< Socks5Connected*>(this));
    return QObject::qt_metacast(_clname);
}

int Socks5Connected::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
