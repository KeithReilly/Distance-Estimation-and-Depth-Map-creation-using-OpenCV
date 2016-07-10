/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sat Apr 9 20:14:53 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Keith_Projects_GUI/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   43,   43,   43, 0x08,
      44,   43,   43,   43, 0x08,
      70,   43,   43,   43, 0x08,
      97,   43,   43,   43, 0x08,
     132,   43,   43,   43, 0x08,
     163,   43,   43,   43, 0x08,
     198,   43,   43,   43, 0x08,
     221,   43,   43,   43, 0x08,
     248,   43,   43,   43, 0x08,
     278,   43,   43,   43, 0x08,
     310,  347,   43,   43, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0on_buttonTakePictures_clicked()\0"
    "\0on_takeTestPics_clicked()\0"
    "on_calibrateCams_clicked()\0"
    "on_checkImgRectification_clicked()\0"
    "on_clearAllPicsTaken_clicked()\0"
    "on_clearCalibrationFiles_clicked()\0"
    "on_RecordVid_clicked()\0"
    "on_cearAllVideos_clicked()\0"
    "on_checkVidDistance_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_buttonTakePictures_clicked(); break;
        case 1: _t->on_takeTestPics_clicked(); break;
        case 2: _t->on_calibrateCams_clicked(); break;
        case 3: _t->on_checkImgRectification_clicked(); break;
        case 4: _t->on_clearAllPicsTaken_clicked(); break;
        case 5: _t->on_clearCalibrationFiles_clicked(); break;
        case 6: _t->on_RecordVid_clicked(); break;
        case 7: _t->on_cearAllVideos_clicked(); break;
        case 8: _t->on_checkVidDistance_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
