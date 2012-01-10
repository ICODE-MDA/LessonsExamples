// OpenCVReadImage.cpp : Defines the entry point for the console application.
//
#include "opencv/cv.h"
#include "opencv/highgui.h"

int main()
{
	IplImage* sourceImg;
	IplImage* colorThresh;
	IplImage* gray;
	IplImage* grayThresh;

	int threshold = 100, maxValue = 255;
	int thresholdType = CV_THRESH_BINARY;

	sourceImg = cvLoadImage("../apple.bmp", 1);
	colorThresh = cvCloneImage( sourceImg );
	gray = cvCreateImage( cvSize(sourceImg->width, sourceImg->height), IPL_DEPTH_8U, 1 );
	cvCvtColor( sourceImg, gray, CV_BGR2GRAY );
	grayThresh = cvCloneImage( gray );

	cvNamedWindow( "source", 1 );    	cvShowImage( "source", sourceImg);
	cvNamedWindow( "gray", 1 );    	cvShowImage( "gray", gray );

	cvThreshold( sourceImg, colorThresh, threshold, maxValue, thresholdType );
	cvThreshold( gray, grayThresh, threshold, maxValue, thresholdType );

	cvNamedWindow( "colorThresh", 1 );    cvShowImage( "colorThresh", colorThresh );
	cvNamedWindow( "grayThresh", 1 );    cvShowImage( "grayThresh", grayThresh );
	cvWaitKey(0);

	return 0;
}
