// OpenCVReadImage.cpp : Defines the entry point for the console application.
//
#include "opencv/cv.h"
#include "opencv/highgui.h"

int main()
{
	IplImage* sourceImg;				// Create a new IplImage image data structure
	IplImage* grayImg, *cannyImg;

	// Load a color (3 channel RGB) image
	sourceImg = cvLoadImage("../apple.bmp",1);

	// Create a single channel 1 byte image (grayscale image)
	grayImg = cvCreateImage( cvSize(sourceImg->width, sourceImg->height), IPL_DEPTH_8U, 1 );

	// Convert the original color image to grayscale image
	cvCvtColor( sourceImg, grayImg, CV_BGR2GRAY );

	// Create a grayscale image to store the Canny edge detection result
	cannyImg = cvCreateImage( cvSize(sourceImg->width, sourceImg->height), IPL_DEPTH_8U, 1 );
	
	// Canny Edge Detection
	cvCanny(grayImg, cannyImg, 50, 150, 3);

	cvNamedWindow( "original", 1 );
	cvNamedWindow( "canny", 1 );       
	cvShowImage( "original", sourceImg );
	cvShowImage( "canny", cannyImg );
	cvWaitKey(0);

	return 0;
}

