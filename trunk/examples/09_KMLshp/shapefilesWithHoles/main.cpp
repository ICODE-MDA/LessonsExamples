#include <iostream>
#include <string>
#include <vector>

#include <shapelib/shapefil.h>

using namespace std;

class Point
{
public:
	double x;
	double y;

	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
};

class Contour
{
public:
	vector<Point> points;
};

class Blob
{
public:
	vector<Contour> contours;
};

void writeBlobs(vector<Blob> &blobs)
{
	string outputName = "blobsWithHoles.shp";

	SHPHandle hSHP = SHPCreate(outputName.c_str(), SHPT_POLYGON);
	if (hSHP == NULL) {
		cout << "Unable to create: " << outputName << ".shp" << endl;
		return;
	} 

	DBFHandle hDBF = DBFCreate(outputName.c_str());
	if (hDBF == NULL) {
		cout << "Unable to create: " << outputName << ".dbf" << endl;
		return;
	} 

	// Add fields.
	DBFAddField(hDBF, "ID", FTInteger, 10, 0);

	for (unsigned int currentBlob =0; currentBlob < blobs.size(); currentBlob++){
		vector<int> panPartsStart;
		vector<double> padfX;
		vector<double> padfY;

		cerr << "currentBlob: " << currentBlob << endl;
		DBFWriteIntegerAttribute(hDBF, currentBlob, 0, currentBlob+1);

		int nParts = blobs[currentBlob].contours.size();
		int partIdx = 0;
		for (unsigned int currentContour = 0; currentContour < blobs[currentBlob].contours.size(); currentContour++){	
			int numPointsInContour = blobs[currentBlob].contours[currentContour].points.size();
			panPartsStart.push_back(partIdx);

			cerr << "currentContour: " << currentContour << endl;
			
			for(unsigned int currentPoint = 0; currentPoint <numPointsInContour; currentPoint++)
			{
				padfX.push_back(blobs[currentBlob].contours[currentContour].points[(numPointsInContour-1) - currentPoint].x);
				padfY.push_back(blobs[currentBlob].contours[currentContour].points[(numPointsInContour-1) - currentPoint].y);
			}
			//Re-write the first point to finish the polygon
			padfX.push_back(blobs[currentBlob].contours[currentContour].points[numPointsInContour-1].x);
			padfY.push_back(blobs[currentBlob].contours[currentContour].points[numPointsInContour-1].y);
		
			partIdx = partIdx + numPointsInContour+1;
		}

		SHPObject *psObject = SHPCreateObject(SHPT_POLYGON, -1, nParts, panPartsStart.data(), NULL, partIdx, padfX.data(), padfY.data(), NULL, NULL);
		SHPWriteObject(hSHP, -1, psObject);
		SHPDestroyObject(psObject);
	}

	SHPClose(hSHP);
	DBFClose(hDBF);
}

int main(int argc, char** argv)
{
	vector<Blob> blobs;

	for(int x=0; x<75; x = x+25)
	{
		for(int y=0; y<75; y=y+25)
		{
			Blob blob;
			Contour outerContour;
			outerContour.points.push_back(Point(-10+x, y+ 10)); 
			outerContour.points.push_back(Point(10+x, y+ 10));
			outerContour.points.push_back(Point(10+x, y+ -10));
			outerContour.points.push_back(Point(-10+x, y+ -10));
			blob.contours.push_back(outerContour);

			Contour innerContour;
			innerContour.points.push_back(Point(1+x, y+ 6)); 
			innerContour.points.push_back(Point(1+x, y+ 1));
			innerContour.points.push_back(Point(6+x, y+ 1));
			innerContour.points.push_back(Point(6+x, y+ 6));
			blob.contours.push_back(innerContour);

			innerContour.points.clear();
			innerContour.points.push_back(Point(2+x, y+ 5)); 
			innerContour.points.push_back(Point(2+x, y+ 2));
			innerContour.points.push_back(Point(5+x, y+ 2));
			innerContour.points.push_back(Point(5+x, y+ 5));
			blob.contours.push_back(innerContour);

			innerContour.points.clear();
			innerContour.points.push_back(Point(3+x, y+ 4)); 
			innerContour.points.push_back(Point(3+x, y+ 3));
			innerContour.points.push_back(Point(4+x, y+ 3));
			innerContour.points.push_back(Point(4+x, y+ 4));
			blob.contours.push_back(innerContour);
			
			innerContour.points.clear();
			innerContour.points.push_back(Point(-2+x, y+ -5)); 
			innerContour.points.push_back(Point(-2+x, y+ -2));
			innerContour.points.push_back(Point(-5+x, y+ -2));
			innerContour.points.push_back(Point(-5+x, y+ -5));
			blob.contours.push_back(innerContour);

			blobs.push_back(blob);
		}
	}
	
	writeBlobs(blobs);

	return 0;
}
