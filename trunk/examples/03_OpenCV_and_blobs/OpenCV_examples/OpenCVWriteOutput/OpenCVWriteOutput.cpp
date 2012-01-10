// OpenCVReadImage.cpp : Defines the entry point for the console application.
//
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <stdio.h>

int main()
{
	IplImage* image;				// Create a new IplImage image data structure
										//  IplImage is the basic image data structure in OpenCV

	image = cvLoadImage("../apple.bmp",1);	// Load the image file into the image data structure
											//  The ‘1’ specifies the image is color (‘0’ to force
											//  grayscale image, and ‘-1’ to leave color information
											//  unchanged from file)

	// This method notifies user of image writing failures

	char *outFileName = "outputimage.jpg";	// Output filename
	if( !cvSaveImage( outFileName, image ) )		//”image” is an existing IplImage
		printf("Could not save: %s\n", outFileName );
	else
		printf("Saved new image output file: %s\n", outFileName );

	cvReleaseImage( &image ); 		// Release the memory for the image

	return 0;
}
