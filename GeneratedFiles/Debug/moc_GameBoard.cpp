/****************************************************************************
** Meta object code from reading C++ file 'GameBoard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../GameBoard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameBoard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameBoard_t {
    QByteArrayData data[26];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameBoard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameBoard_t qt_meta_stringdata_GameBoard = {
    {
QT_MOC_LITERAL(0, 0, 9), // "GameBoard"
QT_MOC_LITERAL(1, 10, 14), // "stonesCrushing"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 2), // "hp"
QT_MOC_LITERAL(4, 29, 6), // "damage"
QT_MOC_LITERAL(5, 36, 2), // "mp"
QT_MOC_LITERAL(6, 39, 9), // "fillBoard"
QT_MOC_LITERAL(7, 49, 12), // "clickedStone"
QT_MOC_LITERAL(8, 62, 6), // "Stone*"
QT_MOC_LITERAL(9, 69, 5), // "stone"
QT_MOC_LITERAL(10, 75, 11), // "deleteStone"
QT_MOC_LITERAL(11, 87, 3), // "col"
QT_MOC_LITERAL(12, 91, 3), // "row"
QT_MOC_LITERAL(13, 95, 11), // "changeStone"
QT_MOC_LITERAL(14, 107, 4), // "type"
QT_MOC_LITERAL(15, 112, 10), // "deleteRect"
QT_MOC_LITERAL(16, 123, 5), // "width"
QT_MOC_LITERAL(17, 129, 6), // "height"
QT_MOC_LITERAL(18, 136, 13), // "forceExchange"
QT_MOC_LITERAL(19, 150, 2), // "x1"
QT_MOC_LITERAL(20, 153, 2), // "y1"
QT_MOC_LITERAL(21, 156, 2), // "x2"
QT_MOC_LITERAL(22, 159, 2), // "y2"
QT_MOC_LITERAL(23, 162, 7), // "endMove"
QT_MOC_LITERAL(24, 170, 7), // "gravity"
QT_MOC_LITERAL(25, 178, 15) // "gravityFinished"

    },
    "GameBoard\0stonesCrushing\0\0hp\0damage\0"
    "mp\0fillBoard\0clickedStone\0Stone*\0stone\0"
    "deleteStone\0col\0row\0changeStone\0type\0"
    "deleteRect\0width\0height\0forceExchange\0"
    "x1\0y1\0x2\0y2\0endMove\0gravity\0gravityFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameBoard[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   86,    2, 0x0a /* Public */,
       7,    1,   87,    2, 0x0a /* Public */,
      10,    0,   90,    2, 0x0a /* Public */,
      10,    2,   91,    2, 0x0a /* Public */,
      13,    3,   96,    2, 0x0a /* Public */,
      15,    0,  103,    2, 0x0a /* Public */,
      15,    4,  104,    2, 0x0a /* Public */,
      18,    0,  113,    2, 0x0a /* Public */,
      18,    4,  114,    2, 0x0a /* Public */,
      23,    0,  123,    2, 0x09 /* Protected */,
      24,    0,  124,    2, 0x09 /* Protected */,
      25,    0,  125,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   12,   11,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   11,   12,   16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   19,   20,   21,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GameBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameBoard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stonesCrushing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->fillBoard(); break;
        case 2: _t->clickedStone((*reinterpret_cast< Stone*(*)>(_a[1]))); break;
        case 3: _t->deleteStone(); break;
        case 4: _t->deleteStone((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->changeStone((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->deleteRect(); break;
        case 7: _t->deleteRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 8: _t->forceExchange(); break;
        case 9: _t->forceExchange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 10: _t->endMove(); break;
        case 11: _t->gravity(); break;
        case 12: _t->gravityFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Stone* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameBoard::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameBoard::stonesCrushing)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameBoard::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_GameBoard.data,
    qt_meta_data_GameBoard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameBoard.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GameBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void GameBoard::stonesCrushing(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
