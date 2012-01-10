#include "kmlWriter.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv){

	kmlWriter writer("test.kml");

	if(!writer.isGood()){
		return -1;
	}

	writer.writePlacemark("test name", "test description", -174.12421, 33.21312321, 0);
	writer.writePlacemark("test name1", "test description1", -175.12421, 34.21312321, 0);
	writer.writePlacemark("test name2", "test description2", -176.12421, 35.21312321, 0);

	vector< vector<double> > coordinates;
	vector<double> points;
	points.push_back(-170.12321);
	points.push_back(32.12321);
	points.push_back(1.12321);
	coordinates.push_back(points);
	points.clear();
	points.push_back(-174.12321);
	points.push_back(35.12321);
	points.push_back(10.12321);
	coordinates.push_back(points);
 	writer.writePath("test path", "test path description", coordinates);

	return 0;
}
