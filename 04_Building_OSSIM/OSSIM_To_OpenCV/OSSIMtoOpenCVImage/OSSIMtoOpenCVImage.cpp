// OpenCVReadImage.cpp : Defines the entry point for the console application.
//
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include <iostream>

// within this program ossimCommon is used for ossimGetScalarSizeInBytes.
// This header will have some common globabl inline and non-inline functions
#include "ossim/base/ossimCommon.h"

#include "ossim/base/ossimFilename.h"

// used to get the string name of the scalar type for the handler.  The scalar
// type specifies if its unsigned char, float, double, ...etc
#include "ossim/base/ossimScalarTypeLut.h"

// This is the majic number factory.  All loader are registered to this factory.
// it will lookp through all factories to try to open the passed in image file
#include "ossim/imaging/ossimImageHandlerRegistry.h"

// Base pointer for the passed back object type
#include "ossim/imaging/ossimImageHandler.h"

// this is the most important class and is called as the first line of all applications.
// without this alll the important factories are not created.
#include "ossim/init/ossimInit.h"

using namespace std;

int main(int argc, char** argv)
{
	if(argc != 2){
		cout << "./a.out <input_image>" << endl;
		return 0;
	}
	char* input = argv[1];

	// Initialize OSSIM, must do this every time we want to use it.
	ossimInit::instance()->initialize();
	// Open image using OSSIM, place into image handler
	ossimImageHandler *handler = ossimImageHandlerRegistry::instance()->open(ossimFilename(input));

	// check to see if handler is valid
	if(handler)
	{
		
		// pointer to actual image data values
		ossimRefPtr<ossimImageData> imageSourceData;

		// Initialize tile, set it to equal the entire satellite image
		ossimIrect tileRect = handler->getBoundingRect(0);

		// Get the image data from the handler for the tile, in this case the entire image
		imageSourceData = handler->getTile(tileRect);

		// Declare an IPLImage to place the OSSIM Image values.
		IplImage *image = cvCreateImage(cvSize(tileRect.height(), tileRect.width()), IPL_DEPTH_8U, 1);
		CvScalar s;
		
		// pointer to ossim image data buffer
		ossim_uint8 *inBuf = (ossim_uint8*)imageSourceData->getBuf(0);
		
		// loop through each pixel in ossim data object, place into IplImage object.
		for (int i=0; i < tileRect.height(); i++)
		{
			for (int j=0; j < tileRect.width(); j++)
			{
				s.val[0] = (int)(*inBuf);
				cvSet2D(image,i,j,s);
				++inBuf;
			}
		}

		// Display that image

		cvNamedWindow( "IplImage", CV_WINDOW_AUTOSIZE );
		cvShowImage( "IplImage", image );
		cvWaitKey(0);

		cvDestroyWindow( "IplImage" );
		cvReleaseImage(&image);
		delete handler;
	}
	else
	{
		cout << "Unable to open image = " << input << endl;
	}

	// call the finalize so the ossim can cleanup if needed.
	ossimInit::instance()->finalize();

	return 0;
}	
