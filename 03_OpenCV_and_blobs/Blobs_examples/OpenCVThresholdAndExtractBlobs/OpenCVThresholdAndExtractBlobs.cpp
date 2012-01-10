// OpenCVThresholdAndExtractBlobs.cpp : Main function demonstrating blobs library usage.
//

// OpenCV functions
#include <opencv/cv.h>
#include <opencv/highgui.h>

// Include Blob Functions
#include "blob.h"
#include "BlobResult.h"

// For writing to cout
#include <iostream>			// For writing to streams (for example the cout stream, which we will discuss)
#include <fstream>			// Also for writing to streams

#include <vector>	// vector
#include <math.h>	// math

using namespace std;

int main(int argc, char* argv[])
{
	if(argc!=3){
		cout << "Usage:\nOpenCVThresholdAndExtractBlobs.exe <input_file> <threshold>" << endl;
		return 0;
	}

	//  Declare 4 IplImages
	IplImage* sourceImg;
	IplImage* colorThresh;
	IplImage* gray;
	IplImage* grayThresh;
	// Declare and set thresholds

	int threshold = 40;
	int maxValue = 255;
	int thresholdType = CV_THRESH_BINARY_INV;
	// Load source image
	sourceImg = cvLoadImage(argv[1], 1);
	
	// Load threshold from user
	threshold = atoi(argv[2]);

	// Clone RGB sourceImg
	colorThresh = cvCloneImage( sourceImg );
	// Initialize gray image, same size as sourceImg
	gray = cvCreateImage( cvSize(sourceImg->width, sourceImg->height), IPL_DEPTH_8U, 1 );
	// Convert RGB image to gray scale
	cvCvtColor( sourceImg, gray, CV_BGR2GRAY );
	// Clone gray scale image
	grayThresh = cvCloneImage( gray );

	// Show RGB and gray scale images
	cvNamedWindow( "source", 0 );
	cvShowImage( "source", sourceImg);
	cvNamedWindow( "gray", 0 );
	cvShowImage( "gray", gray );

	// Threshold RGB image
	cvThreshold( sourceImg, colorThresh, threshold, maxValue, thresholdType );
	// Threshold gray scale image
	cvThreshold( gray, grayThresh, threshold, maxValue, thresholdType );

	IplConvKernel* SE;
	SE = cvCreateStructuringElementEx(5, 7, 0, 0, CV_SHAPE_RECT);

	
	cvNamedWindow( "grayThreshbefore", 0 );
	cvShowImage( "grayThreshbefore", grayThresh );

	// Perform Morphological Ops (This is a "closing" operation)
	cvDilate(grayThresh,grayThresh, SE);
	cvErode(grayThresh,grayThresh, SE);

	cvNamedWindow( "colorThresh", 0 );
	cvShowImage( "colorThresh", colorThresh );
	cvNamedWindow( "grayThresh", 0 ); 
	cvShowImage( "grayThresh", grayThresh );
	cvWaitKey(0);

	cvDestroyWindow( "colorThresh" ); 	
	cvDestroyWindow( "grayThresh" ); 


	// Now let's use the blobs library to analyze our binary image
	//  Image containing binary blob image.
	IplImage *inputBlob = cvCreateImage(cvSize(grayThresh->width+2,grayThresh->height+2),IPL_DEPTH_8U,1);
	IplImage *blobMask = cvCreateImage(cvSize(grayThresh->width, grayThresh->height), IPL_DEPTH_8U, 1);

	//cvCopyMakeBorder(dummy, inputBlob, cvPoint(1,1), IPL_BORDER_CONSTANT);
	cvCopyMakeBorder(grayThresh, inputBlob, cvPoint(1,1), IPL_BORDER_CONSTANT);

	// Declare blob results
	CBlobResult blobs;

	// delare a single blob
	CBlob Blob;

	// Corners of blob and middle of blob
	int iMaxx, iMinx, iMaxy, iMiny, iMeanx, iMeany;

	// get the blobs from the image, with no mask, using a threshold of 100
	blobs = CBlobResult(inputBlob, NULL, 100, true );

	//filter the background and helper external frame
	//see note 3 http://opencv.willowgarage.com/wiki/cvBlobsLib
	blobs.Filter(blobs, B_INCLUDE, CBlobGetArea(),  B_GREATER, 100);
	blobs.Filter(blobs, B_INCLUDE, CBlobGetMean(),  B_GREATER, 1);


	cout << "Number of blobs " << blobs.GetNumBlobs() << "\n";


	// Loop through each blob found
	for  (int blobIndex=0; blobIndex<blobs.GetNumBlobs(); ++blobIndex)
	{

		// get the blob info
		Blob = blobs.GetBlob(blobIndex);

		cvSetZero(blobMask);
		
		CvScalar color = CV_RGB(1,1,1);
		Blob.FillBlob(blobMask,color);		//set all pixels in blob mask =1
		CvScalar numPixels = cvSum(blobMask);	//number of pixels in blob
		
		// multiply input by blob mask
		cvMul(gray, blobMask, blobMask, 1);		//now blob mask should be gray scale image
		
		CvScalar sumIntensity = cvSum(blobMask);



		// Mean value of pixels of blob
		double blobMean = sumIntensity.val[0] / numPixels.val[0];

		//grab the ellipse of it to get the appx size
		CvBox2D ellipse = Blob.GetEllipse();
		CvSize2D32f dim = ellipse.size;
		// major and minor axis of blob (length and width)
		double W = dim.width;
		double L = dim.height;


		// get max, and min co-ordinates
		iMaxx=(int)Blob.MaxX() - 1;
		iMinx=(int)Blob.MinX() - 1;
		iMaxy=(int)Blob.MaxY() - 1;
		iMiny=(int)Blob.MinY() - 1;

		// Area of Blob
		double BlobArea = Blob.Area();

		cout << "area of blob : " << BlobArea << endl;


		// size of full image 
		int height = gray->height;
		int width = gray->width;

		// size of blob bounding rect
		int BlobxSize = iMaxx - iMinx;
		int BlobySize = iMaxy - iMiny;


		cout << "Blobsize : " << BlobxSize << ", " << BlobySize << endl;

		IplImage* blobImg = cvCreateImage(cvSize(BlobxSize,BlobySize),IPL_DEPTH_8U, 1);
		cvSetImageROI(gray,cvRect(iMinx,iMiny,BlobxSize,BlobySize));	
		cvCopy(gray, blobImg);
		cvResetImageROI(gray);

		// Show blobmask
		cvNamedWindow("Window", 0);			// Create a new window
		cvShowImage("Window", blobImg);	// Display the image in the window
		cvWaitKey(0);						// Wait for key to close the window

		cvDestroyWindow( "Window" ); 		// Destroy the window
		cvReleaseImage(&blobImg);			//Free the memory

		// find the average of the blob (i.e. estimate its centre)
		iMeanx=(iMinx+iMaxx)/2;
		iMeany=(iMiny+iMaxy)/2;

		cout << "Blob UL corner : " << iMinx << " , " << iMiny << endl;

	}	// End of blob loop	

	//free all memory that was allocated
	cvReleaseImage(&sourceImg);
	cvReleaseImage(&colorThresh);
	cvReleaseImage(&gray);
	cvReleaseImage(&grayThresh);
	cvReleaseImage(&inputBlob);
	cvReleaseImage(&blobMask);

	return 0;
}
