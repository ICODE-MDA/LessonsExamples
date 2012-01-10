// OpenCVReadImage.cpp : Defines the entry point for the console application.
//
#include "opencv/cv.h"
#include "opencv/highgui.h"

int main()
{
	IplImage* sourceImg;		// Create a new IplImage image data structure
					//  IplImage is the basic image data structure in OpenCV

	sourceImg = cvLoadImage("../apple.bmp",1);	
	// Load the image file into the image data structure
	//  The ‘1’ specifies the image is color (‘0’ to force
	//  grayscale image, and ‘-1’ to leave color information
	//  unchanged from file)

	cvNamedWindow("Window", 1);			// Create a new window
	cvShowImage("Window", sourceImg);	// Display the image in the window
	cvWaitKey(0);						// Wait for key to close the window

	cvDestroyWindow( "Window" ); 		// Destroy the window
	cvReleaseImage( &sourceImg ); 		// Release the memory for the image

	return 0;
}

