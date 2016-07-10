#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T19:42:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Keith_Projects_GUI
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_calib3d -lopencv_features2d

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    functions.h \
    openCVCalibration.h \
    openCVFunctions.h

FORMS    += mainwindow.ui
