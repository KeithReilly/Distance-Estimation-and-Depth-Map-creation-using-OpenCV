#include "mainwindow.h"
#include "functions.h"
#include "openCVFunctions.h"
#include "openCVCalibration.h"
#include "time.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonTakePictures_clicked()
{
    // Get the number of pics that the user has chosen
    QString spin = ui->spinBoxNumOfPics->text();

    // Only display message if user
    // has increased the spin box
    if ( spin.toInt() != 0 ) {

        //Debug message - checking number of pics being taking
        QMessageBox::information(this,tr("Info"),tr("#Pics: %1").arg(spin));

        // Take number of pics based on users choice
        for( int i = 0 ; i < spin.toInt() ; i = i + 1){
            Sleeper::sleep(3); // Sleep for five seconds
            std::string input = currentDateTime(); // getCurrentDateString
            takePic(input); // pass in dateString
        } // end of for loop

    }

}


void MainWindow::on_takeTestPics_clicked()
{
    // This will allow the user
    // to test the cameras to
    // make sure both are working
    takePic("Test");
}

void MainWindow::on_calibrateCams_clicked()
{
    // This function will use the
    // ListOfPics file to calibrate
    // the cameras
    QMessageBox::StandardButton check;
    check = QMessageBox::question(this,tr("Info"),tr("| You have images ready to be calibrated |"),
                          QMessageBox::Yes|QMessageBox::No);

    if (check == QMessageBox::Yes ){
        check = QMessageBox::question(this,tr("Info"),tr("| Ok calibrating now....|"));
        StereoCalib();
    }else
        check = QMessageBox::question(this,tr("Info"),tr("| Take pictures of chessboard and then calibrate....|"));
}

void MainWindow::on_checkImgRectification_clicked()
{
    // This function will allow
    // the user to check that
    // he calibaration files
    // are working

    QMessageBox::StandardButton check;
    check = QMessageBox::question(this,tr("Info"),tr("| You have test files and calibration results |"),
                          QMessageBox::Yes|QMessageBox::No);

    if (check == QMessageBox::Yes ){
        check = QMessageBox::question(this,tr("Info"),tr("| Ok getting retified image now....|"));
        getRetified();
    }else
        check = QMessageBox::question(this,tr("Info"),tr("| Take pictures of chessboard and then calibrate....|"));

}

void MainWindow::on_clearAllPicsTaken_clicked()
{
    // remove all pic names from list file
    clearListOfPics();
    // remove all images that have been taken
    clearAllPicsTaken();
}

void MainWindow::on_clearCalibrationFiles_clicked()
{
    // This function will clear
    // all the current xml files
    // that contain the calibration
    // results
    clearCalibrationFiles();
}

void MainWindow::on_RecordVid_clicked()
{
    // This function will
    // record a small clip
    // to test that record
    // feature is working
    startRecordingCams();
}

void MainWindow::on_cearAllVideos_clicked()
{
    // This function will
    // remove all the videos
    // from the resutls file
    clearAllVids();
}

void MainWindow::on_checkVidDistance_clicked()
{
    // This will use the last
    // two video files and displace
    // the distance of the object in
    // centre of the screen

    // Get the name of the left vid the user entered
    std::string leftVid = (ui->lineEditLeft->text()).toStdString();

    // Get the name of the Right vid the user entered
    std::string rightVid = (ui->lineEditRight->text()).toStdString();

    if (!leftVid.empty() && !rightVid.empty()){

        //testDistanceInVids(); -> uses StereoBM (does not work)
        //testDistanceTwo(); -> uses StereoSGBM (works)

        QMessageBox::StandardButton check;
        check = QMessageBox::question(this,tr("Info"),tr("| You have Video files and calibration results |"),
                              QMessageBox::Yes|QMessageBox::No);

        if (check == QMessageBox::Yes ){
            check = QMessageBox::question(this,tr("Info"),tr("| Ok getting distance estimation now....|"));
            testDistanceTwo(leftVid,rightVid); // -> uses StereoSGBM (works)
        }else
            check = QMessageBox::question(this,tr("Info"),tr("| Get calibration results and also record a video....|"));

    }else
        QMessageBox::information(this,tr("Info"),tr("You need to enter in the video names..."));

}
