/****************************************************************************
** Meta object code from reading C++ file 'jiaohao.h'
**
** Created: Wed Feb 1 16:50:09 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "jiaohao.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jiaohao.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JIAOHAO[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      18,    8,    8,    8, 0x0a,
      27,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_JIAOHAO[] = {
    "JIAOHAO\0\0a_slot()\0b_slot()\0c_slot()\0"
};

const QMetaObject JIAOHAO::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_JIAOHAO,
      qt_meta_data_JIAOHAO, 0 }
};

const QMetaObject *JIAOHAO::metaObject() const
{
    return &staticMetaObject;
}

void *JIAOHAO::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JIAOHAO))
        return static_cast<void*>(const_cast< JIAOHAO*>(this));
    return QDialog::qt_metacast(_clname);
}

int JIAOHAO::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: a_slot(); break;
        case 1: b_slot(); break;
        case 2: c_slot(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
