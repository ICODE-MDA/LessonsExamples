#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

void help()
{
	printf("\nThis program demonstrates using features2d detector, descriptor extractor and simple matcher\n"
			"Using the SURF desriptor:\n"
			"\n"
			"Usage:\n matcher_simple <image1> <image2>\n");
}

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		help();
		return -1;
	}

	Mat img1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
	if(img1.empty() || img2.empty())
	{
		printf("Can't read one of the images\n");
		return -1;
	}

	// detecting keypoints
	SurfFeatureDetector detector(400);
	vector<KeyPoint> keypoints1, keypoints2;
	detector.detect(img1, keypoints1);
	detector.detect(img2, keypoints2);

	// computing descriptors
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute(img1, keypoints1, descriptors1);
	extractor.compute(img2, keypoints2, descriptors2);

	// matching descriptors
	BruteForceMatcher<L2<float> > matcher;
    vector<DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

	// drawing the results
	namedWindow("matches", 1);
	Mat img_matches;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
	imshow("matches", img_matches);
	waitKey(0);

	return 0;
}


#if 0
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class AisTip{
public:
	AisTip(){
		name = "";
		mmsi = "0000000";
		latitude = 0;
		longitude = 0;
		heading = 0;
		speed = 0;
	}
	AisTip(string name, string mmsi, double lat, double lon, double heading, double speed){
		this->name = name;
		this->mmsi = mmsi;
		this->latitude = lat;
		this->longitude = lon;
		this->heading = heading;
		this->speed = speed;
	}
	string name;
	string mmsi;
	double latitude;
	double longitude;
	double heading;
	double speed;
};

class ImageTip{
public:
	ImageTip(){
		latitude = 0;
		longitude = 0;
		area = 0;
		heading = 0;
	}
	ImageTip(double lat, double lon, double area, double heading){
		this->latitude = lat;
		this->longitude = lon;
		this->heading = heading;
		this->area = area;
	}
	double latitude;
	double longitude;
	double area;
	double heading;
};


void loadTips(vector<AisTip>& aisTips, vector<ImageTip>& imageTips);

int main(int argc, char** argv){

	vector<AisTip> aisTips;
	vector<ImageTip> imageTips;
	
	//Your software would load these vectors with actual data from
	//imagery and from AIS sources. I will just use fake data.
	loadTips(aisTips, imageTips);

	

	return 0;
}

void loadTips(vector<AisTip>& aisTips, vector<ImageTip>& imageTips){
	//load the vectors with some data
	//I will use some fake data with AIS tips that do NOT exactly match
	//the tips from the imagery detections

	AisTip aisTip1("good ship 1", "123456", 10.001, 17.002, 160.2, 4);
	AisTip aisTip2("good ship 2", "123457", 11.001, 18.002, 165.2, 6);
	AisTip aisTip3("good ship 3", "123458", 12.001, 19.002, 169.2, 8);

	aisTips.push_back(aisTip1);
	aisTips.push_back(aisTip2);
	aisTips.push_back(aisTip3);

	ImageTip imageTip1(10.001, 17.002,1000, 160.2);
	ImageTip imageTip2(11.005, 18.009,108, 165.6); //NOTE: doesn't exactly agree with AIS
	ImageTip imageTip3(12.0, 19.001,1000, 169.3);  //NOTE: doesn't exactly agree with AIS

	imageTips.push_back(imageTip1);
	imageTips.push_back(imageTip2);
	imageTips.push_back(imageTip3);

}

#endif