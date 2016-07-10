/*
 *
 *
 Keith Reilly
 C12410532
 DT211/4
 *
 *
 This header file will be used to store OpenCV
 functions for taking pictures
 recording videos and other jobs etc...
*/

#ifndef OPENCVFUNCTIONS_H
#define OPENCVFUNCTIONS_H

#include <QMainWindow>
#include "functions.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

// for calling OpenCV makes is easier
// and mush easier to folloe
using namespace cv;
using namespace std;

// This function will take a pic with
// the left/right camera and display
// the output to the user
void takePic(const std::string& input){

    // Testing OpenCV
    // Open up two cameras (Left and Right)
    VideoCapture rightVidCapight(1); // open the Right camera
    VideoCapture leftVidCapeft(0); // open the Left camera

    // I had to set the height and width
    // as any-thing above 640x480 is unstable
    rightVidCapight.set(CV_CAP_PROP_FRAME_WIDTH,440);
    rightVidCapight.set(CV_CAP_PROP_FRAME_HEIGHT,360);

    leftVidCapeft.set(CV_CAP_PROP_FRAME_WIDTH,440);
    leftVidCapeft.set(CV_CAP_PROP_FRAME_HEIGHT,360);

    // Check that they are both running
    if(!rightVidCapight.isOpened() && !leftVidCapeft.isOpened() ){
        printf("Cameras Failed to Open");
        return;
    }

    // Create two frames for both cameras
    Mat rightVidFrameight;
    Mat leftVidFrameeft;

    // Name of pics, setting up varabiles
    std::ostringstream nameRight;
    std::ostringstream nameLeft;

    // Set Names to test or date
    // also store in the correct directory
    nameRight << "/home/pi/OpenCV_Project/Images/Right_"<< input << "_.ppm";
    nameLeft << "/home/pi/OpenCV_Project/Images/Left_"<< input << "_.ppm";

    // If test is not in input
    // then right names to ListFile
    // This will be used later for calabration
    if( input != "Test" ){
        // write to TXT file
        // Path to results directory
        std::ofstream toFileTXT("/home/pi/OpenCV_Project/ListOfPics.txt", std::ios_base::app);
        toFileTXT << nameLeft.str();
        toFileTXT << "\n";
        toFileTXT << nameRight.str();
        toFileTXT << "\n";
    }

    rightVidCapight >> rightVidFrameight; // get a new frame from camera Right
    leftVidCapeft >> leftVidFrameeft; // get a new frame from camera Left

    // do any processing
    cv::imwrite(nameRight.str(), rightVidFrameight);
    cv::imwrite(nameLeft.str(), leftVidFrameeft);

    // Display the images to the user afer
    // Create windows to display images
    namedWindow( "Left Image", WINDOW_AUTOSIZE );
    namedWindow( "Right Image", WINDOW_AUTOSIZE );

    // now give windows paths to the images
    imshow( "Left Image", leftVidFrameeft);
    imshow( "Right Image",rightVidFrameight);

    // WaitKey allows imshow to work in loops
    waitKey(30);

    // release mem once
    // I am finished with it
    leftVidFrameeft.release();
    rightVidFrameight.release();
    rightVidCapight.release();
    leftVidCapeft.release();

} // end of takePic()

void getRetified(){

    // Set counters
    int j;

    CvSize imageSize = {0,0};
    IplImage* test=cvLoadImage("/home/pi/OpenCV_Project/Images/Right_Test_.ppm",0);
    imageSize = cvGetSize(test);

    // Load the calabration settings
    CvMat *mx1 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/mx1.xml",NULL,NULL,NULL);
    CvMat *my1 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/my1.xml",NULL,NULL,NULL);
    CvMat *mx2 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/mx2.xml",NULL,NULL,NULL);
    CvMat *my2 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/my2.xml",NULL,NULL,NULL);

    // 360/440 image size Height/Width
    CvMat* img1r = cvCreateMat( imageSize.height,imageSize.width, CV_8U );
    CvMat* img2r = cvCreateMat( imageSize.height,imageSize.width, CV_8U );
    CvMat* disp = cvCreateMat( imageSize.height,imageSize.width, CV_16S );
    CvMat* vdisp = cvCreateMat( imageSize.height,imageSize.width, CV_8U );
    CvMat* pair;

    cvNamedWindow( "rectified", 1 );

    pair = cvCreateMat( imageSize.height, imageSize.width*2,CV_8UC3 );

    //Setup for finding stereo corrrespondences
    CvStereoBMState *BMState = cvCreateStereoBMState();
    assert(BMState != 0);
    BMState->preFilterSize=41;
    BMState->preFilterCap=31;
    BMState->SADWindowSize=41;
    BMState->minDisparity=-64;
    BMState->numberOfDisparities=128;
    BMState->textureThreshold=10;
    BMState->uniquenessRatio=15;

    IplImage* img1=cvLoadImage("/home/pi/OpenCV_Project/Images/Left_Test_.ppm",0);
    IplImage* img2=cvLoadImage("/home/pi/OpenCV_Project/Images/Right_Test_.ppm",0);

    CvMat part;
    cvRemap( img1, img1r, mx1, my1 );
    cvRemap( img2, img2r, mx2, my2 );

    cvFindStereoCorrespondenceBM( img1r, img2r, disp,BMState);
    cvNormalize( disp, vdisp, 0, 256, CV_MINMAX );

    // Show the disparity image
    cvNamedWindow( "disparity" );
    cvShowImage( "disparity", vdisp );

    cvGetCols( pair, &part, 0, imageSize.width );
    cvCvtColor( img1r, &part, CV_GRAY2BGR );
    cvGetCols( pair, &part, imageSize.width,imageSize.width*2 );
    cvCvtColor( img2r, &part, CV_GRAY2BGR );
    for( j = 0; j < imageSize.height; j += 16 ) // Draw Lines
        cvLine( pair, cvPoint(0,j),cvPoint(imageSize.width*2,j),CV_RGB(50,255,15));

    // Show with lines
    cvShowImage( "rectified", pair );

    // WaitKey allows imshow to work in loops
    waitKey(30000);


    cvDestroyWindow( "rectified" );

} // end of retified

void startRecordingCams(){
    // This function will make a
    // small recording 

    // Testing OpenCV
    // Open up two cameras (Left and Right)
    VideoCapture rightVidCapight(0); // open the Right camera
    VideoCapture leftVidCapeft(1); // open the Left camera

    // I had to set the height and width
    // as any-thing above 640x480 is unstable
    rightVidCapight.set(CV_CAP_PROP_FRAME_WIDTH,440);
    rightVidCapight.set(CV_CAP_PROP_FRAME_HEIGHT,360);

    leftVidCapeft.set(CV_CAP_PROP_FRAME_WIDTH,440);
    leftVidCapeft.set(CV_CAP_PROP_FRAME_HEIGHT,360);

    // Check that they are both running
    if(!rightVidCapight.isOpened() && !leftVidCapeft.isOpened() ){
        printf("Cameras Failed to Open");
        return;
    }

    // Create two frames for both cameras
    Mat rightVidFrameight;
    Mat leftVidFrameeft;

    // Name of pics, setting up varabiles
    std::ostringstream nameRight;
    std::ostringstream nameLeft;

    // Set Names to test or date
    // also store in the correct directory
    std::string dateName = currentDateTime(); // getCurrentDateString
    nameRight << "/home/pi/OpenCV_Project/Videos/CamCapture_"<< dateName << "_Right.avi";
    nameLeft << "/home/pi/OpenCV_Project/Videos/CamCapture_"<< dateName << "_Left.avi";

    // Set up video writers
    VideoWriter Rightwriter(nameRight.str(),CV_FOURCC('M','J','P','G'),10,
                            Size(rightVidCapight.get(CV_CAP_PROP_FRAME_WIDTH),
                                 rightVidCapight.get(CV_CAP_PROP_FRAME_HEIGHT)),true);
    VideoWriter Leftwriter(nameLeft.str(),CV_FOURCC('M','J','P','G'),10,
                           Size(leftVidCapeft.get(CV_CAP_PROP_FRAME_WIDTH),
                                leftVidCapeft.get(CV_CAP_PROP_FRAME_HEIGHT)),true);

    for( ;; )
    {
      rightVidCapight >> rightVidFrameight;
      leftVidCapeft >> leftVidFrameeft;

      Rightwriter.write(rightVidFrameight);
      Leftwriter.write(leftVidFrameeft);

      imshow("LeftFrame", leftVidFrameeft);
      imshow("RightFrame", rightVidFrameight);

      char c = (char)waitKey(33);

      if( c == 27 ) break; // once the user clicks q
    }


    cvDestroyWindow( "LeftFrame" );
    cvDestroyWindow( "RightFrame" );

}


void testDistanceInVids(const std::string& Left, std::string& Right){

    printf("\nLoading Calabrations...\n");

    Mat Q;
    Q = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/Q.xml",NULL,NULL,NULL);
    CvMat *mx1 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/mx1.xml",NULL,NULL,NULL);
    CvMat *my1 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/my1.xml",NULL,NULL,NULL);
    CvMat *mx2 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/mx2.xml",NULL,NULL,NULL);
    CvMat *my2 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/my2.xml",NULL,NULL,NULL);

    // Get the names of the last two video files created
    std::string FilenameLeft;
    std::string FilenameRight;
    FilenameLeft = system("exec sudo ls /home/pi/OpenCV_Project/Videos/ | tail -2 | head -1");
    FilenameRight = system("exec sudo ls /home/pi/OpenCV_Project/Videos/ | tail -1 ");
    printf("\nFileLeft: %s - FileRight: %s \n", FilenameLeft.c_str(), FilenameRight.c_str());

    //VideoCapture

    VideoCapture LeftVid("/home/pi/OpenCV_Project/Videos/CamCapture_2016_04_04.17:40:40_Left.avi");
    VideoCapture RightVid("/home/pi/OpenCV_Project/Videos/CamCapture_2016_04_04.17:40:40_Right.avi");

    // Make sure I can openup the vids
    if(!LeftVid.isOpened() || !RightVid.isOpened())
    {
        // Tell the user that the files were not opened(also give the file names)
        printf("\nVideo files where not opned: $s - %s \n", FilenameLeft.c_str(), FilenameRight.c_str() );
        exit(1); // Exit if fail
    }

    // Get two frames ready
    Mat rightVidFrameight;
    Mat leftVidFrameeft;

    CvSize imageSize = {0,0};
    IplImage* test=cvLoadImage("/home/pi/OpenCV_Project/Images/Right_Test_.ppm",0);
    imageSize = cvGetSize(test);

    // get other mats ready for disparty
    CvMat* img1r = cvCreateMat( imageSize.height,imageSize.width, CV_8U );
    CvMat* img2r = cvCreateMat( imageSize.height,imageSize.width, CV_8U );
    CvMat* disp = cvCreateMat( imageSize.height,imageSize.width, CV_16S );
    CvMat* vdisp = cvCreateMat( imageSize.height,imageSize.width, CV_8U );

    //Setup for finding stereo corrrespondences
    CvStereoBMState *BMState = cvCreateStereoBMState();
    assert(BMState != 0);
    BMState->preFilterSize=63;
    BMState->preFilterCap=3;
    BMState->SADWindowSize=41;
    BMState->minDisparity=-64;
    BMState->numberOfDisparities=128;
    BMState->textureThreshold=10;
    BMState->uniquenessRatio=10;
    BMState->speckleWindowSize=100;
    BMState->speckleRange=32;
    BMState->disp12MaxDiff=1;

    while(1)
    {
        LeftVid >> leftVidFrameeft;
        RightVid >> rightVidFrameight;

        // do any processing
        cv::imwrite("rightVidFrameightVid.ppm", rightVidFrameight);
        cv::imwrite("leftVidFrameeftVid.ppm", leftVidFrameeft);

        //CvMat* img1= new CvMat(leftVidFrameeft);
        //CvMat* img2= new CvMat(rightVidFrameight);
        IplImage* img1=cvLoadImage("leftVidFrameeftVid.ppm",0);
        IplImage* img2=cvLoadImage("rightVidFrameightVid.ppm",0);

        if ( !leftVidFrameeft.empty() || !rightVidFrameight.empty() ){

            // In here I will compute
            // the disparity map
            cvRemap( img1, img1r, mx1, my1 );
            cvRemap( img2, img2r, mx2, my2 );

            cvFindStereoCorrespondenceBM( img1r, img2r, disp,BMState);
            cvNormalize( disp, vdisp, 0, 256, CV_MINMAX );

            Mat pointcloud,zdisp;
            zdisp = vdisp;
            // Calculate 3D co-ordinates from disparity image
            reprojectImageTo3D(zdisp, pointcloud, Q, true);

            // Draw red rectangle around 40 px wide square area im image
            int xmin = leftVidFrameeft.cols/2 - 20, xmax = leftVidFrameeft.cols/2 + 20, ymin = leftVidFrameeft.rows/2 - 20,
        ymax = leftVidFrameeft.rows/2 + 20;
            rectangle(leftVidFrameeft, Point(xmin, ymin), Point(xmax, ymax), Scalar(0, 255, 0));

            // Extract depth of 40 px rectangle and print out their mean
            pointcloud = pointcloud(Range(ymin, ymax), Range(xmin, xmax));
            Mat z_roi(pointcloud.size(), CV_32FC1);
            int from_to[] = {2, 0};
            mixChannels(&pointcloud, 1, &z_roi, 1, from_to, 1);

            cout << "Depth: " << mean(z_roi) << "cm" << endl;

            // Show the disparity image
            cvNamedWindow( "disparity" );
            cvShowImage( "disparity", vdisp );

            imshow("LeftImage", leftVidFrameeft);
            waitKey(5000);

        }else{
            destroyWindow("RightImage");
            destroyWindow("LeftImage");
            destroyWindow("disparity");
            break;
        }

    }

}

// This function works the same way
// as the one above, but it is using
// some code obtained from Pratical OpenCV
// by Samarth Brahmbhatt found on page 168
void testDistanceTwo(const std::string& Left, std::string& Right){
    printf("\nLoading Calabrations...\n");

    Mat Q, mx1,my1,mx2,my2;
    Q = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/Q.xml",NULL,NULL,NULL);
    mx1 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/mx1.xml",NULL,NULL,NULL);
    my1 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/my1.xml",NULL,NULL,NULL);
    mx2 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/mx2.xml",NULL,NULL,NULL);
    my2 = (CvMat *)cvLoad("/home/pi/OpenCV_Project/CameraCalabration/my2.xml",NULL,NULL,NULL);


    // Get the names of the last two video files created
    std::string FilenameLeft = "/home/pi/OpenCV_Project/Videos/" + Left;
    std::string FilenameRight = "/home/pi/OpenCV_Project/Videos/" + Right;

    //VideoCapture
    VideoCapture leftVidCap(FilenameLeft);
    VideoCapture rightVidCap(FilenameRight);
    cout << "LeftVid: " << FilenameLeft << " <|> RightVid:" << FilenameRight << endl;


    //reduce frame size
    CvSize image_size = {320,240};
    //image_size = cvGetSize(test);
    leftVidCap.set(CV_CAP_PROP_FRAME_HEIGHT, image_size.height);
    leftVidCap.set(CV_CAP_PROP_FRAME_WIDTH, image_size.width);
    rightVidCap.set(CV_CAP_PROP_FRAME_HEIGHT, image_size.height);
    rightVidCap.set(CV_CAP_PROP_FRAME_WIDTH, image_size.width);

    // Make sure I can openup the vids
    if(!leftVidCap.isOpened() || !rightVidCap.isOpened())
    {
        cout << "Video files where not opned" << endl;
        return;
    }

    //Setup for finding stereo corrrespondences
    StereoSGBM stereo;
    stereo.preFilterCap = 63;
    stereo.SADWindowSize = 3;
    stereo.P1 = 8 * 3 * stereo.SADWindowSize * stereo.SADWindowSize;
    stereo.P2 = 32 * 3 * stereo.SADWindowSize * stereo.SADWindowSize;
    stereo.uniquenessRatio = 10;
    stereo.speckleWindowSize = 100;
    stereo.speckleRange = 32;
    stereo.disp12MaxDiff = 1;
    stereo.minDisparity=-64;
    stereo.numberOfDisparities=128;
    stereo.fullDP = true;

    namedWindow("Disparity", CV_WINDOW_NORMAL);
    namedWindow("Left", CV_WINDOW_NORMAL);

    while(char(waitKey(1)) != 'q')
    {
        //grab raw frames first
        leftVidCap.grab();
        rightVidCap.grab();
        //decode later so the grabbed frames are less apart in time
        Mat leftVidFrame, leftVidFrame_rect, rightVidFrame, rightVidFrame_rect;
        leftVidCap.retrieve(leftVidFrame);
        rightVidCap.retrieve(rightVidFrame);
        if(leftVidFrame.empty() || rightVidFrame.empty()) break;

        // get the retified images
        remap(leftVidFrame, leftVidFrame_rect, mx1, my2, INTER_LINEAR);
        remap(rightVidFrame, rightVidFrame_rect, mx2, my2, INTER_LINEAR);

        Mat disp, disp_show, disp_compute, pointcloud;
        stereo(leftVidFrame_rect, rightVidFrame_rect, disp);
        disp.convertTo(disp_show, CV_8U, 255/(stereo.numberOfDisparities * 16.));
        disp.convertTo(disp_compute, CV_32F, 1.f/16.f);

        // Calculate 3D co-ordinates from disparity image
        reprojectImageTo3D(disp_compute, pointcloud, Q, true);

        // Draw green rectangle around 40 px wide square area im image
        int xmin = leftVidFrame.cols/2 - 20, xmax = leftVidFrame.cols/2 + 20, ymin = leftVidFrame.rows/2 - 20,
    ymax = leftVidFrame.rows/2 + 20;
        rectangle(leftVidFrame_rect, Point(xmin, ymin), Point(xmax, ymax), Scalar(0, 255, 0));
        waitKey(100);

        // Extract depth of 40 px rectangle and print out their mean
        pointcloud = pointcloud(Range(ymin, ymax), Range(xmin, xmax));
        Mat z_roi(pointcloud.size(), CV_32FC1);
        int from_to[] = {2, 0};
        mixChannels(&pointcloud, 1, &z_roi, 1, from_to, 1);

        cout << "Depth: " << mean(z_roi) << " CM" << endl;

        imshow("Disparity", disp_show);
        imshow("Left", leftVidFrame_rect);
        waitKey(100);

        }

}

#endif // OPENCVFUNCTIONS_H
