#ifndef KMLWRITER_H_
#define KMLWRITER_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class kmlWriter{
public:
	kmlWriter(string filename);
	bool isGood();
	~kmlWriter();
	void writePlacemark(string name, string description, double lon, double lat, double height);
	void writePath(string name, string description, vector< vector<double> >& coordinates, int extrude =1, int tessellate =1, string altitude = "absolute");
private:
	void writeHeader();
	void writeFooter();

	string _filename;
	ofstream _stream;
};



#endif /* KMLWRITER_H_ */
