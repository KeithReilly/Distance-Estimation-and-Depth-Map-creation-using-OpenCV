#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QThread>

// Get current date format is YYYY_MM_DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    // date/time format
    strftime(buf, sizeof(buf), "%Y_%m_%d.%X", &tstruct);

    return buf;
}

// Remove all contents from
// ListOfPics.txt file
void clearListOfPics(){
    std::ofstream toFileTXT("/home/pi/OpenCV_Project/ListOfPics.txt", std::ofstream::out | std::ofstream::trunc);
}

// Remove the current calibration
// files
void clearCalibrationFiles(){
    system("exec sudo rm -rf /home/pi/OpenCV_Project/CameraCalabration/* ");
}

//Removes all the pictures
// that were taken
void clearAllPicsTaken(){
    system("exec sudo rm -rf /home/pi/OpenCV_Project/Images/* ");
}

//Removes all the videos
// that were taken
void clearAllVids(){
    system("exec sudo rm -rf /home/pi/OpenCV_Project/Videos/* ");
}

// Remove all the images
// with errors from the listOfPics
void errImgRemove(){
    system("exec echo HiThere");
}



void errorLog(std::string msg){
    // write to TXT file
    // this will store all
    // the images that could
    // not be calibrated
    std::ofstream toFileTXTError("/home/pi/OpenCV_Project/CalibrationPicsErrors.txt", std::ios_base::app);
    toFileTXTError << msg;
    toFileTXTError << "\n";

}

// Sleep Function (seconds to sleep)
class Sleeper : public QThread{
public:
    static void sleep( unsigned long secs){QThread::sleep(secs);}
};

#endif // FUNCTIONS_H
