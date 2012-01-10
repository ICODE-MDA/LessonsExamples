/*---------------------------------------------------------------------------*/
//  Code for performing 2-D Wiener filtering on images
//
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <malloc.h>
#include <math.h>
#include <assert.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "wienerFilter.h"
using namespace std;

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void WienerFilter2D(IplImage* input, IplImage* output)
{
	// Declar window size
	int FSize = 5;

	// Estimate the local mean of the input image
	IplImage* localMean = cvCreateImage(cvSize(input->width,input->height),IPL_DEPTH_32F,1);
	// Estimate of the local variance of the input image
	IplImage* localVar = cvCreateImage(cvSize(input->width,input->height),IPL_DEPTH_32F,1);

	// Create the Filtering kernel.  We will make a square kernel
	CvMat* Kernel = cvCreateMat(FSize, FSize, CV_32FC1);
	CvScalar KernelVal;
	// Now set kernel value to be 1/(FSize*FSize) at each location.
	// What is this filter called???  The Mean Filter!  
	KernelVal.val[0] = 1.0/(FSize*FSize);		// Set the first channel of KernelVal to be 1/(FSize*FSize)
	cvSet( Kernel, KernelVal);		//  This will set all values of Kernel to be KernelVal

	// Perform 2-D filtering of input image with mean filter to estimate the local mean at each pixel location.
	// We would expect localMean to be a smothed version of input

	cvFilter2D( input, localMean, Kernel);	

	// Create image which is input squared (I^2)
	IplImage* inputSQ = cvCreateImage(cvSize(input->width,input->height),IPL_DEPTH_32F,1);	
	//  Multiply the input image by itself to create input^2
	cvMul( input, input, inputSQ);
	
	// Filter I.^2 with kernel and place in localVar image
	cvFilter2D( inputSQ, localVar, Kernel);

	// release inputSQ
	cvReleaseImage(&inputSQ);

	// release kernel
	cvReleaseMat(&Kernel);

	// Declare image to hold local mean squared	
	IplImage* localMeanSQ = cvCreateImage(cvSize(input->width,input->height),IPL_DEPTH_32F,1);
	cvMul( localMean,localMean, localMeanSQ);

	// subtract localMeanSQ from localVar
	cvSub( localVar, localMeanSQ, localVar );
	
	// release localMeanSQ
	cvReleaseImage(&localMeanSQ);

	
	// Estimate the noise power 
	CvScalar mean;			//mean of subimage
	double noisePower;
	mean = cvAvg( localVar);		// Calculated mean of image
	

	noisePower = mean.val[0];
	


	// Compute result
	//
	// Computation is split up to minimize use of memory
	// for temp arrays.

	// temporary image
	IplImage* temp = cvCreateImage(cvSize(input->width,input->height),IPL_DEPTH_32F,1);

	// Copy input into temp
	cvCopy( input, temp);
	
	// subtract localMean from temp and place in output
	cvSub( temp, localMean, output );
	
	// Subtract noisePower from localVar
	CvScalar noiseVal;
	noiseVal.val[0] = noisePower;
	
	// subtract off noise from local variance
	cvSubS( localVar, noiseVal, temp );

	// Make sure we don't have any negative values.
	// cvMaxS keeps max(temp(x,y),0) for each x,y in the image temp
	cvMaxS( temp, 0.0, temp );
	
	// Make sure the local Variance is at least as high as the noise
	cvMaxS( localVar, noisePower, localVar );

	// Normalize the output by local variance.
	cvDiv( output, localVar, output );		//Divide output by localVar at each pixel location
	
	// Now mulitiply the output by the input image
	cvMul( output, temp, output );
	
	// Add the local mean in.
	cvAdd( output , localMean, output );

	cvReleaseImage(&temp);
	cvReleaseImage(&localMean);
	cvReleaseImage(&localVar);

	
}

// Function to show two IplImages.
void showImage(IplImage* src1, IplImage* src2) 
{
	if (src1==NULL || src2==NULL)
		cout << "ERROR ERROR _____ERROR " << endl;

	// create window
	cvNamedWindow("image1", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("image1", 100, 100);
	cvNamedWindow("image2", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("image2", 600, 100);

	// show the image
	cvShowImage("image1", src1);
	cvShowImage("image2", src2);

	// wait for a key
	cvWaitKey(0);

	cvDestroyWindow("image1");
	cvDestroyWindow("image2");

}
