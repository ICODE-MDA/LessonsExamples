/*  test.cpp 
*  
*  Description:  Contains the main function for the wienerFilter executable.  
*/

#include <math.h>			// Include standard C++ math library 
#include <string>			// Include stdlibc++ strings
#include <opencv/cv.h>		// Include the OpenCV header
#include <opencv/cxcore.h>	// Include OpenCV core	
#include <opencv/cvaux.h>	// Include OpenCV Aux 
#include <opencv/highgui.h>	// Include OpenCV HighGUI 
#include "wienerFilter.h"	// Include the WinerFiltering functions
#include <iostream>			// For writing to streams (for example the cout stream, which we will discuss)
#include <fstream>			// Also for writing to streams


using namespace std;

// Main function to call Wiener filtering
int main(int argc, char *argv[])
{
	if(argc != 2){
		cout << "./a.out <image_file>" << endl;
		return 0;
	}

	cout << "size of char : " << sizeof(char) << endl;
	cout << "size of int : " << sizeof(int) << endl;
	cout << "size of float : " << sizeof(float) << endl;


	// Write out the number of input arguments
	cout << "argc : " << argc << endl;

	// Declare the IplImage
	IplImage* src;

	// Write out argv[0]

	char* argZero = argv[0];
	cout << "argv[0] : " << argv[0] << endl;

	// Load the IplImage as the first argument to the executable.
    if((src = cvLoadImage(argv[1], 0))!= 0)
    {	
		// Declare a new IplImage, called input, but make it a 32 bit floating point image.
		IplImage* input = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_32F,1);		
		if(src->width%128 != 0 || src->height%128 != 0){
			cout << "image dimensions must be a multiple of 128" << endl;
			return -1;
		}

		// Convert the input image, which is 8-bit unsigned to a 32 bit floating point image
    	cvConvert(src,input);
    	
		int subBlockSize = 128;
		IplImage* input_Sublock = cvCreateImage(cvSize(subBlockSize,subBlockSize),IPL_DEPTH_8U,1);
		for (int i=0; i < input->width; i=i+subBlockSize)
		{
			for (int j=0; j < input->height; j= j+subBlockSize)
			{
				cvSetImageROI(src, cvRect(i,j,subBlockSize,subBlockSize));
				
				cvCopy(src,input_Sublock);
				cvResetImageROI(src);
				showImage(src,input_Sublock);
				// processing on input_SubBlock here
			}
		}
		// Process input_Sublock





		// Declare another IplImage to hold the ouput of the wiener filtering operation.  Make it the same size as the input_img
		IplImage* output =  cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_32F,1);
    	
		// Perform 2-D Wiener filtering of image to remove noise.
		WienerFilter2D(input, output);

		// Convert output from 32 bit floating point to 8 bit unsigned int
		IplImage* out = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);		//store output image
		cvConvert(output,out);
		
		// Display results
		showImage(src, out); 

		// Name of outut image
   	   std::string line = argv[1];    
   	   line.append("out.jpg");    
   	   char *outfile = new char [line.size()+1];
   	   strcpy (outfile, line.c_str());
    	         	 
		//Save output image 
	   if(!cvSaveImage(outfile,out))
   				cout << "Could not save: " << outfile << endl;

	   // Release input and output images
	cvReleaseImage(&src);
	cvReleaseImage(&out);

    }
    else	// Case where we can't open image
    {
    	cout << "ERROR....unable to load image! " << endl;
    }
    

	return 0;
}
