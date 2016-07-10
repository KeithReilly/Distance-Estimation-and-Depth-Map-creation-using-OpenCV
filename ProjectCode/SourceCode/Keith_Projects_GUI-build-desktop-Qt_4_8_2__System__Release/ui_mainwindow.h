/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Apr 9 20:06:43 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *clearAllPicsTaken;
    QLineEdit *lineEditRight;
    QLineEdit *lineEditLeft;
    QLabel *label_3;
    QPushButton *RecordVid;
    QLabel *label_5;
    QSpinBox *spinBoxNumOfPics;
    QPushButton *cearAllVideos;
    QPushButton *takeTestPics;
    QPushButton *clearCalibrationFiles;
    QPushButton *buttonTakePictures;
    QPushButton *checkImgRectification;
    QPushButton *checkVidDistance;
    QPushButton *calibrateCams;
    QLabel *label_2;
    QLabel *label_6;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(796, 325);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 201, 31));
        clearAllPicsTaken = new QPushButton(centralWidget);
        clearAllPicsTaken->setObjectName(QString::fromUtf8("clearAllPicsTaken"));
        clearAllPicsTaken->setGeometry(QRect(600, 100, 161, 41));
        lineEditRight = new QLineEdit(centralWidget);
        lineEditRight->setObjectName(QString::fromUtf8("lineEditRight"));
        lineEditRight->setGeometry(QRect(250, 190, 191, 31));
        lineEditLeft = new QLineEdit(centralWidget);
        lineEditLeft->setObjectName(QString::fromUtf8("lineEditLeft"));
        lineEditLeft->setGeometry(QRect(252, 150, 191, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(250, 10, 131, 31));
        RecordVid = new QPushButton(centralWidget);
        RecordVid->setObjectName(QString::fromUtf8("RecordVid"));
        RecordVid->setGeometry(QRect(250, 50, 121, 41));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(450, 150, 131, 31));
        spinBoxNumOfPics = new QSpinBox(centralWidget);
        spinBoxNumOfPics->setObjectName(QString::fromUtf8("spinBoxNumOfPics"));
        spinBoxNumOfPics->setGeometry(QRect(130, 50, 61, 41));
        cearAllVideos = new QPushButton(centralWidget);
        cearAllVideos->setObjectName(QString::fromUtf8("cearAllVideos"));
        cearAllVideos->setGeometry(QRect(600, 200, 161, 41));
        takeTestPics = new QPushButton(centralWidget);
        takeTestPics->setObjectName(QString::fromUtf8("takeTestPics"));
        takeTestPics->setGeometry(QRect(600, 50, 161, 41));
        clearCalibrationFiles = new QPushButton(centralWidget);
        clearCalibrationFiles->setObjectName(QString::fromUtf8("clearCalibrationFiles"));
        clearCalibrationFiles->setGeometry(QRect(600, 150, 161, 41));
        buttonTakePictures = new QPushButton(centralWidget);
        buttonTakePictures->setObjectName(QString::fromUtf8("buttonTakePictures"));
        buttonTakePictures->setGeometry(QRect(10, 50, 111, 41));
        checkImgRectification = new QPushButton(centralWidget);
        checkImgRectification->setObjectName(QString::fromUtf8("checkImgRectification"));
        checkImgRectification->setGeometry(QRect(10, 150, 161, 41));
        checkVidDistance = new QPushButton(centralWidget);
        checkVidDistance->setObjectName(QString::fromUtf8("checkVidDistance"));
        checkVidDistance->setGeometry(QRect(250, 100, 191, 41));
        calibrateCams = new QPushButton(centralWidget);
        calibrateCams->setObjectName(QString::fromUtf8("calibrateCams"));
        calibrateCams->setGeometry(QRect(10, 100, 161, 41));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(600, 10, 161, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(450, 190, 131, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 796, 24));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">Calabration Options</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        clearAllPicsTaken->setText(QApplication::translate("MainWindow", "Clear All Pics Taken", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Video Options</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        RecordVid->setText(QApplication::translate("MainWindow", "Record Video", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Left Video Name</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        cearAllVideos->setText(QApplication::translate("MainWindow", "Clear All Recordings", 0, QApplication::UnicodeUTF8));
        takeTestPics->setText(QApplication::translate("MainWindow", "Take Test Pics", 0, QApplication::UnicodeUTF8));
        clearCalibrationFiles->setText(QApplication::translate("MainWindow", "Clear Calibration Files", 0, QApplication::UnicodeUTF8));
        buttonTakePictures->setText(QApplication::translate("MainWindow", "Take Pictures", 0, QApplication::UnicodeUTF8));
        checkImgRectification->setText(QApplication::translate("MainWindow", "Image Rectification", 0, QApplication::UnicodeUTF8));
        checkVidDistance->setText(QApplication::translate("MainWindow", "Test Video Distance ", 0, QApplication::UnicodeUTF8));
        calibrateCams->setText(QApplication::translate("MainWindow", "Calabrate Cameras", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Testing &amp; Cleanup</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">Right Video Name</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
