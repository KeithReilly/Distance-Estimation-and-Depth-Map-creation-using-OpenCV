/*
 *
 *
 Keith Reilly
 C12410532
 DT211/4
 *
 *
 This header file will be used to store OpenCV
 functions calabration tools, this code was taken
 out of the OpenCV Learning Book by Gary Bradski & Adrian Kaebler
 this code can be found on page 446
 
 Edits have been made to the code, it is now saved to XML files, 
 and there is error checking where i get the names of all the images
 that are causing errors, if an error occurs, then the code should
 return to the main menu.
*/

#ifndef OPENCVCALIBRATION_H
#define OPENCVCALIBRATION_H

#include <QMainWindow>
#include <QMessageBox>
#include "functions.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include "cv.h"
#include "cxmisc.h"
#include "highgui.h"
#include "cvaux.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

//
// Given a list of chessboard images, the number of corners (nx, ny)
// on the chessboards, and a flag: useCalibrated for calibrated (0) or
// uncalibrated (1: use cvStereoCalibrate(), 2: compute fundamental
// matrix separately) stereo. Calibrate the cameras and display the
// rectified results along with the computed disparity images.
//
void StereoCalib() {

    int displayCorners = 1;
    int showUndistorted = 1;

    //OpenCV can handle left-right
    //or up-down camera arrangements
    bool isVerticalStereo = false;
    const int maxScale = 1;

    // TXT File with path to imges
    const char* imageList = "/home/pi/OpenCV_Project/ListOfPics.txt";

    // Chessboard settings
    int nx = 9;
    int ny = 6;
    const float squareSize = 2.5; //Chessboard square size in cm
    int useUncalibrated = 0;

    // this will be set to ture if
    // chessboard is not found int image
    bool errorImgFlag = false;

    FILE* f = fopen(imageList, "rt");
    int i, j, lr, nframes, n = nx*ny, N = 0;
    vector<string> imageNames[2];
    vector<CvPoint3D32f> objectPoints;
    vector<CvPoint2D32f> points[2];
    vector<int> npoints;
    vector<uchar> active[2];
    vector<CvPoint2D32f> temp(n);
    CvSize imageSize = {0,0};

    // ARRAY AND VECTOR STORAGE:
    double M1[3][3], M2[3][3], D1[5], D2[5];
    double R[3][3], T[3], E[3][3], F[3][3];
    double Q[4][4];

    CvMat _M1 = cvMat(3, 3, CV_64F, M1 );
    CvMat _M2 = cvMat(3, 3, CV_64F, M2 );
    CvMat _D1 = cvMat(1, 5, CV_64F, D1 );
    CvMat _D2 = cvMat(1, 5, CV_64F, D2 );
    CvMat _R = cvMat(3, 3, CV_64F, R );
    CvMat _T = cvMat(3, 1, CV_64F, T );
    CvMat _E = cvMat(3, 3, CV_64F, E );
    CvMat _F = cvMat(3, 3, CV_64F, F );
    CvMat _Q = cvMat(4,4, CV_64F, Q);

    if( displayCorners )
        cvNamedWindow( "corners", 1 );

    // READ IN THE LIST OF CHESSBOARDS:
    if( !f )
    {
        fprintf(stderr, "can not open file %s\n", imageList );
        return;
    }
    for(i=0;;i++)
    {
        char buf[1024];
        int count = 0, result=0;
        lr = i % 2;
        vector<CvPoint2D32f>& pts = points[lr];
        if( !fgets( buf, sizeof(buf)-3, f ))
            break;
        size_t len = strlen(buf);
        while( len > 0 && isspace(buf[len-1]))
            buf[--len] = '\0';
        if( buf[0] == '#')
            continue;
        IplImage* img = cvLoadImage( buf, 0 );
        if( !img )
            break;

        imageSize = cvGetSize(img);
        imageNames[lr].push_back(buf);

        //FIND CHESSBOARDS AND CORNERS THEREIN:
        for( int s = 1; s <= maxScale; s++ )
        {
            IplImage* timg = img;
            if( s > 1 )
            {
                timg = cvCreateImage(cvSize(img->width*s,img->height*s),
                    img->depth, img->nChannels );
                cvResize( img, timg, CV_INTER_CUBIC );
            }
            result = cvFindChessboardCorners( timg, cvSize(nx, ny),
                &temp[0], &count,
                CV_CALIB_CB_ADAPTIVE_THRESH |
                CV_CALIB_CB_NORMALIZE_IMAGE);
            if( timg != img )
                cvReleaseImage( &timg );
            if( result || s == maxScale )
                for( j = 0; j < count; j++ )
            {
                temp[j].x /= s;
                temp[j].y /= s;
            }

            // Now if there was an error with the
            // iamges and the chessboard was not
            // found, I will create a list of all
            // the images that are causing issues
            if( result )
                break;
            else {
                // name of ppm file >> errorLog
                errorLog(buf);
                // This will cause the programt to stop before calibration
                errorImgFlag = true;
            }
        }
        if( displayCorners )
        {
            printf("%s\n", buf);
            IplImage* cimg = cvCreateImage( imageSize, 8, 3 );
            cvCvtColor( img, cimg, CV_GRAY2BGR );
            cvDrawChessboardCorners( cimg, cvSize(nx, ny), &temp[0],
                count, result );
            cvShowImage( "corners", cimg );
            cvReleaseImage( &cimg );
            cvWaitKey(3000); //wait 3 seconds

        }

        N = pts.size();
        pts.resize(N + n, cvPoint2D32f(0,0));
        active[lr].push_back((uchar)result);

        //assert( result != 0 );
        if( result )
        {
         //Calibration will suffer without subpixel interpolation
            cvFindCornerSubPix( img, &temp[0], count,
                cvSize(11, 11), cvSize(-1,-1),
                cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,
                30, 0.01) );
            copy( temp.begin(), temp.end(), pts.begin() + N );
        }
        cvReleaseImage( &img );
    }
    fclose(f);
    printf("\n");

    // Check if there was an error with the images
    // If there was break out of job
    if (errorImgFlag){
        cout << "There was an error in a image, check the error log..." << endl;
        cvDestroyWindow( "corners" );
        return;
    }

    // HARVEST CHESSBOARD 3D OBJECT POINT LIST:
    nframes = active[0].size();//Number of good chessboads found
    objectPoints.resize(nframes*n);
    for( i = 0; i < ny; i++ )
        for( j = 0; j < nx; j++ )
        objectPoints[i*nx + j] = cvPoint3D32f(i*squareSize, j*squareSize, 0);
    for( i = 1; i < nframes; i++ )
        copy( objectPoints.begin(), objectPoints.begin() + n,
        objectPoints.begin() + i*n );
    npoints.resize(nframes,n);
    N = nframes*n;
    CvMat _objectPoints = cvMat(1, N, CV_32FC3, &objectPoints[0] );
    CvMat _imagePoints1 = cvMat(1, N, CV_32FC2, &points[0][0] );
    CvMat _imagePoints2 = cvMat(1, N, CV_32FC2, &points[1][0] );
    CvMat _npoints = cvMat(1, npoints.size(), CV_32S, &npoints[0] );
    cvSetIdentity(&_M1);
    cvSetIdentity(&_M2);
    cvZero(&_D1);
    cvZero(&_D2);

    // CALIBRATE THE STEREO CAMERAS
    printf("Running stereo calibration ...");
    fflush(stdout);
    cvStereoCalibrate( &_objectPoints, &_imagePoints1,
        &_imagePoints2, &_npoints,
        &_M1, &_D1, &_M2, &_D2,
        imageSize, &_R, &_T, &_E, &_F,
        cvTermCriteria(CV_TERMCRIT_ITER+
        CV_TERMCRIT_EPS, 100, 1e-5),
        CV_CALIB_FIX_ASPECT_RATIO +
        CV_CALIB_ZERO_TANGENT_DIST +
        CV_CALIB_SAME_FOCAL_LENGTH );
    printf("\ndone\n");

    // CALIBRATION QUALITY CHECK
    // because the output fundamental matrix implicitly
    // includes all the output information,
    // we can check the quality of calibration using the
    // epipolar geometry constraint: m2^t*F*m1=0
    vector<CvPoint3D32f> lines[2];

    points[0].resize(N);
    points[1].resize(N);

    _imagePoints1 = cvMat(1, N, CV_32FC2, &points[0][0] );
    _imagePoints2 = cvMat(1, N, CV_32FC2, &points[1][0] );

    lines[0].resize(N);
    lines[1].resize(N);

    CvMat _L1 = cvMat(1, N, CV_32FC3, &lines[0][0]);
    CvMat _L2 = cvMat(1, N, CV_32FC3, &lines[1][0]);

    //Always work in undistorted space
    cvUndistortPoints( &_imagePoints1, &_imagePoints1, &_M1, &_D1, 0, &_M1 );
    cvUndistortPoints( &_imagePoints2, &_imagePoints2, &_M2, &_D2, 0, &_M2 );
    cvComputeCorrespondEpilines( &_imagePoints1, 1, &_F, &_L1 );
    cvComputeCorrespondEpilines( &_imagePoints2, 2, &_F, &_L2 );

    double avgErr = 0;

    for( i = 0; i < N; i++ )
    {
        double err = fabs(points[0][i].x*lines[1][i].x +
            points[0][i].y*lines[1][i].y + lines[1][i].z)
            + fabs(points[1][i].x*lines[0][i].x +
            points[1][i].y*lines[0][i].y + lines[0][i].z);
        avgErr += err;
    }

    printf( "avg err = %g\n", avgErr/(nframes*n) );
    printf("-----------------\n");

    //COMPUTE AND DISPLAY RECTIFICATION
    if( showUndistorted )
    {
        CvMat* mx1 = cvCreateMat( imageSize.height,imageSize.width, CV_32F );
        CvMat* my1 = cvCreateMat( imageSize.height,imageSize.width, CV_32F );
        CvMat* mx2 = cvCreateMat( imageSize.height,imageSize.width, CV_32F );
        CvMat* my2 = cvCreateMat( imageSize.height,imageSize.width, CV_32F );

        double R1[3][3], R2[3][3], P1[3][4], P2[3][4];
        CvMat _R1 = cvMat(3, 3, CV_64F, R1);
        CvMat _R2 = cvMat(3, 3, CV_64F, R2);

        // IF BY CALIBRATED (BOUGUET'S METHOD)
        if( useUncalibrated == 0 )
        {
            CvMat _P1 = cvMat(3, 4, CV_64F, P1);
            CvMat _P2 = cvMat(3, 4, CV_64F, P2);
            cvStereoRectify( &_M1, &_M2, &_D1, &_D2, imageSize,
                &_R, &_T,
                &_R1, &_R2, &_P1, &_P2, &_Q,
                0/*CV_CALIB_ZERO_DISPARITY*/ );
            isVerticalStereo = fabs(P2[1][3]) > fabs(P2[0][3]);

            //Precompute maps for cvRemap()
            cvInitUndistortRectifyMap(&_M1,&_D1,&_R1,&_P1,mx1,my1);
            cvInitUndistortRectifyMap(&_M2,&_D2,&_R2,&_P2,mx2,my2);

            //Save parameters
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/M1.xml",&_M1);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/D1.xml",&_D1);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/R1.xml",&_R1);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/P1.xml",&_P1);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/M2.xml",&_M2);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/D2.xml",&_D2);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/R2.xml",&_R2);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/P2.xml",&_P2);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/Q.xml",&_Q);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/mx1.xml",mx1);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/my1.xml",my1);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/mx2.xml",mx2);
            cvSave("/home/pi/OpenCV_Project/CameraCalabration/my2.xml",my2);

        }
        else
            assert(0);
    }
}


#endif // OPENCVCALIBRATION_H
