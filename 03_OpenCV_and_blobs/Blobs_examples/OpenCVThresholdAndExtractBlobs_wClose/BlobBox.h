#ifndef BLOBBOX_H_
#define BLOBBOX_H_
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimIrect.h>
#include <ostream>
using namespace std;

class BlobBox
{
	friend ostream& operator<<(ostream& output, const BlobBox& box);
	public:
	BlobBox(){}
	//BlobBox(ossimIpt &ul, ossimIpt &lr) {_ul = ul; _lr = lr; active = true;}
	BlobBox(ossimIrect &rect) {_rect = rect; isFromCloudyTile=false; SARSNR =0; SARLength=0; SARWidth=0; SARHeading=0; SARConf=100; active = true;}
	void setFilename(string filename) { _filename = filename; }
	string getFilename() {return _filename;}
	
	ossimIrect _rect;
	bool isFromCloudyTile;
	bool IsFromNoisyTile;
	float SARSNR;
	float SARLength;
	float SARWidth;
	float SARHeading;
	float SARConf;
	bool active;
	string _filename;
	
};
#endif /*BLOBBOX_H_*/
