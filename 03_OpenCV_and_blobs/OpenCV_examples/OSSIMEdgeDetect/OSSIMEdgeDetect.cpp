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
	if(argc!=2){
		cout << "./a.out <image_file>" << endl;
		return 0;
	}
	char* input = argv[1];

	ossimInit::instance()->initialize();
	ossimImageHandler *handler = ossimImageHandlerRegistry::instance()->open(ossimFilename(input));

	if(handler)
	{
		ossimRefPtr<ossimImageData> imageSourceData;
		ossimIrect tileRect = handler->getBoundingRect(0);

		imageSourceData = handler->getTile(tileRect);

		IplImage *image = cvCreateImage(cvSize(tileRect.height(), tileRect.width()), IPL_DEPTH_8U, 1);
		CvScalar s;

		ossim_uint8 *inBuf = (ossim_uint8*)imageSourceData->getBuf(0);
		
		for (int i=0; i < tileRect.height(); i++)
		{
			for (int j=0; j < tileRect.width(); j++)
			{
				s.val[0] = (int)(*inBuf);
				cvSet2D(image,i,j,s);
				++inBuf;
			}
		}

		IplImage *cannyImg = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );

		// Canny Edge Detection
		cvCanny(image, cannyImg, 50, 150, 3);

		cvNamedWindow( "original", 1 );
		cvNamedWindow( "canny", 1 );       
		cvShowImage( "original", image );
		cvShowImage( "canny", cannyImg );
		cvWaitKey(0);

		cvDestroyWindow( "original" );
		cvDestroyWindow( "canny" );
		cvReleaseImage(&image);
		cvReleaseImage(&cannyImg);
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
