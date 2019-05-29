/****************************************************************************
** Meta object code from reading C++ file 'GameLogic.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../GameLogic.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameLogic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameLogic_t {
    QByteArrayData data[31];
    char stringdata0[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameLogic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameLogic_t qt_meta_stringdata_GameLogic = {
    {
QT_MOC_LITERAL(0, 0, 9), // "GameLogic"
QT_MOC_LITERAL(1, 10, 14), // "stonesCrushing"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 2), // "hp"
QT_MOC_LITERAL(4, 29, 6), // "damage"
QT_MOC_LITERAL(5, 36, 2), // "mp"
QT_MOC_LITERAL(6, 39, 7), // "account"
QT_MOC_LITERAL(7, 47, 8), // "useSkill"
QT_MOC_LITERAL(8, 56, 5), // "skill"
QT_MOC_LITERAL(9, 62, 9), // "fillBoard"
QT_MOC_LITERAL(10, 72, 12), // "clickedStone"
QT_MOC_LITERAL(11, 85, 6), // "Stone*"
QT_MOC_LITERAL(12, 92, 5), // "stone"
QT_MOC_LITERAL(13, 98, 11), // "deleteStone"
QT_MOC_LITERAL(14, 110, 3), // "col"
QT_MOC_LITERAL(15, 114, 3), // "row"
QT_MOC_LITERAL(16, 118, 11), // "changeStone"
QT_MOC_LITERAL(17, 130, 4), // "type"
QT_MOC_LITERAL(18, 135, 10), // "deleteRect"
QT_MOC_LITERAL(19, 146, 5), // "width"
QT_MOC_LITERAL(20, 152, 6), // "height"
QT_MOC_LITERAL(21, 159, 13), // "forceExchange"
QT_MOC_LITERAL(22, 173, 2), // "x1"
QT_MOC_LITERAL(23, 176, 2), // "y1"
QT_MOC_LITERAL(24, 179, 2), // "x2"
QT_MOC_LITERAL(25, 182, 2), // "y2"
QT_MOC_LITERAL(26, 185, 4), // "heal"
QT_MOC_LITERAL(27, 190, 10), // "bladeSlash"
QT_MOC_LITERAL(28, 201, 7), // "endMove"
QT_MOC_LITERAL(29, 209, 7), // "gravity"
QT_MOC_LITERAL(30, 217, 15) // "gravityFinished"

    },
    "GameLogic\0stonesCrushing\0\0hp\0damage\0"
    "mp\0account\0useSkill\0skill\0fillBoard\0"
    "clickedStone\0Stone*\0stone\0deleteStone\0"
    "col\0row\0changeStone\0type\0deleteRect\0"
    "width\0height\0forceExchange\0x1\0y1\0x2\0"
    "y2\0heal\0bladeSlash\0endMove\0gravity\0"
    "gravityFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameLogic[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,  108,    2, 0x0a /* Public */,
       9,    0,  113,    2, 0x0a /* Public */,
      10,    1,  114,    2, 0x0a /* Public */,
      13,    0,  117,    2, 0x0a /* Public */,
      13,    2,  118,    2, 0x0a /* Public */,
      16,    3,  123,    2, 0x0a /* Public */,
      18,    0,  130,    2, 0x0a /* Public */,
      18,    4,  131,    2, 0x0a /* Public */,
      21,    0,  140,    2, 0x0a /* Public */,
      21,    4,  141,    2, 0x0a /* Public */,
       4,    1,  150,    2, 0x0a /* Public */,
      26,    1,  153,    2, 0x0a /* Public */,
      27,    0,  156,    2, 0x0a /* Public */,
      28,    0,  157,    2, 0x09 /* Protected */,
      29,    0,  158,    2, 0x09 /* Protected */,
      30,    0,  159,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString,    3,    4,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   15,   14,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   14,   15,   19,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   24,   25,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GameLogic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameLogic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stonesCrushing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->useSkill((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->fillBoard(); break;
        case 3: _t->clickedStone((*reinterpret_cast< Stone*(*)>(_a[1]))); break;
        case 4: _t->deleteStone(); break;
        case 5: _t->deleteStone((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->changeStone((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->deleteRect(); break;
        case 8: _t->deleteRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 9: _t->forceExchange(); break;
        case 10: _t->forceExchange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 11: _t->damage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->heal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->bladeSlash(); break;
        case 14: _t->endMove(); break;
        case 15: _t->gravity(); break;
        case 16: _t->gravityFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
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
            using _t = void (GameLogic::*)(int , int , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameLogic::stonesCrushing)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameLogic::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_GameLogic.data,
    qt_meta_data_GameLogic,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameLogic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameLogic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameLogic.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GameLogic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void GameLogic::stonesCrushing(int _t1, int _t2, int _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
