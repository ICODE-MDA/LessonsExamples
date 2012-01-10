#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace std;
using namespace cv;

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

	void print(){
		cout << this->name << " " << this->mmsi << " " << 
			this->latitude<< " "  << this->longitude<< " " << 
			this->heading<< " "  << this->speed << endl;
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

	void print(){
		cout << this->latitude<< " "  << this->longitude<< " " << 
			this->heading<< " "  << this->area << endl;
	}

	double latitude;
	double longitude;
	double area;
	double heading;
};


void loadTips(vector<AisTip>& aisTips, vector<ImageTip>& imageTips);
void loadDescriptors(vector<AisTip>& aisTips, vector<ImageTip>& imageTips, Mat& aisDescriptors, Mat& imageDescriptors);

int main(int argc, char** argv){

	vector<AisTip> aisTips;
	vector<ImageTip> imageTips;
	
	//Your software would load these vectors with actual data from
	//imagery and from AIS sources. I will just use fake data.
	loadTips(aisTips, imageTips);

	Mat aisDescriptors;
	Mat imageDescriptors;

	loadDescriptors(aisTips, imageTips, aisDescriptors, imageDescriptors);

	cout << aisDescriptors.type() << endl;

	// matching descriptors
	BruteForceMatcher<L2<double> > matcher;
    vector<DMatch> matches;
    matcher.match(aisDescriptors, imageDescriptors, matches);

	for(int i = 0; i < matches.size(); i++){
		cout << "===========================" << endl;
		cout << "matches[i].distance: " << matches[i].distance << endl;
		cout << "matches[i].imgIdx: " << matches[i].imgIdx << endl;
		cout << "matches[i].queryIdx: " << matches[i].queryIdx << endl;
		cout << "matches[i].trainIdx: " << matches[i].trainIdx << endl;
		cout << "IMINT" << endl;
		imageTips[matches[i].trainIdx].print();
		cout << "AIS" << endl;
		aisTips[matches[i].queryIdx].print();
		cout << "===========================" << endl;
	}
	
	return 0;
}

void loadTips(vector<AisTip>& aisTips, vector<ImageTip>& imageTips){
	//load the vectors with some data
	//I will use some fake data with AIS tips that do NOT exactly match
	//the tips from the imagery detections

	AisTip aisTip1("matches to imint 1", "123456", 10.001, 17.002, 160.2, 4);
	AisTip aisTip2("matches to imint 3", "123457", 11.001, 18.002, 165.2, 6);
	AisTip aisTip3("matches to imint 2", "123458", 12.001, 19.002, 169.2, 8);

	aisTips.push_back(aisTip1);
	aisTips.push_back(aisTip2);
	aisTips.push_back(aisTip3);

	ImageTip imageTip1(10.001, 17.002,1000, 160.2);
	ImageTip imageTip2(12.0, 19.001,1000, 169.3);  //NOTE: doesn't exactly agree with AIS
	ImageTip imageTip3(11.005, 18.009,108, 165.6); //NOTE: doesn't exactly agree with AIS
	

	imageTips.push_back(imageTip1);
	imageTips.push_back(imageTip2);
	imageTips.push_back(imageTip3);

}

void loadDescriptors(vector<AisTip>& aisTips, vector<ImageTip>& imageTips, Mat& aisDescriptors, Mat& imageDescriptors){
	aisDescriptors.create(aisTips.size(), 3, CV_64F);
	imageDescriptors.create(imageTips.size(), 3, CV_64F);

	for(int i=0; i<aisTips.size(); i++){
		aisDescriptors.at<double>(i,0) = aisTips[i].latitude;
		aisDescriptors.at<double>(i,1) = aisTips[i].longitude;
		aisDescriptors.at<double>(i,2) = aisTips[i].heading;
	}

	for(int i=0; i<imageTips.size(); i++){
		imageDescriptors.at<double>(i,0) = imageTips[i].latitude;
		imageDescriptors.at<double>(i,1) = imageTips[i].longitude;
		imageDescriptors.at<double>(i,2) = imageTips[i].heading;
	}
}

