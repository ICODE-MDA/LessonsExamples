#ifndef ossimTileToIplFilter_H_
#define ossimTileToIplFilter_H_

#include <ossim/plugin/ossimSharedObjectBridge.h>
#include <ossim/imaging/ossimImageCombiner.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimRectangleCutFilter.h>
#include <ossim/imaging/ossimEdgeFilter.h>
#include <ossim/init/ossimInit.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimString.h>
//#include <ossim/base/ossimArgumentParser.h>
#include <ossim/base/ossimApplicationUsage.h>
#include <ossim/base/ossimNotifyContext.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimKeyword.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimDms.h>
#include <ossim/base/ossimNotify.h>
#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>
//#include <ossim/support_data/ossimNitfFile.h>
//#include <ossim/support_data/ossimNitfFileHeader.h>
//#include <ossim/support_data/ossimNitfImageHeader.h>
//#include <ossim/support_data/ossimNitfIchipbTag.h>
//#include <ossim/support_data/ossimNitfUse00aTag.h>
//#include <ossim/support_data/ossimNitfStdidcTag.h>
//#include <ossim/support_data/ossimNitfFileHeaderV2_0.h>
//#include <ossim/support_data/ossimNitfFileHeaderV2_1.h>
//#include <ossim/support_data/ossimNitfFileHeaderV2_X.h>
//#include <shapefil.h>
//#include <ossimShapeFile.h>
//#include <ossimShapeDatabase.h>
//#include <ogrsf_frmts.h>
#include <cmath>
#include <iomanip>
#include <time.h>
#include <iomanip>
#include <string>
#include <opencv/cv.h>


// Declare ossimTileToIplFilter class
// This class is based on the ossimImageCombiner class
class ossimTileToIplFilter : public ossimImageCombiner
{
public:
	// Constructors
   ossimTileToIplFilter(ossimObject *owner=NULL);
	// Destructor
   virtual ~ossimTileToIplFilter();
	// Short and long names for filter
   ossimString getShortName()const
      {
         return ossimString("Tile to IplImage Filter");
      }
   
   ossimString getLongName()const
      {
         return ossimString("Tile to IplImage Filter");
      }
   
   // getTile function replaces getTile in ossimImageCombiner
   virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& tileRect, ossim_uint32 resLevel=0);
   
   virtual void initialize();
   
   virtual ossimScalarType getOutputScalarType() const;
   
   ossim_uint32 getNumberOfOutputBands() const;

   double round(double x);

   virtual bool saveState(ossimKeywordlist& kwl,
                          const char* prefix=0)const;
   
   /*!
    * Method to the load (recreate) the state of an object from a keyword
    * list.  Return true if ok or false on error.
    */
   virtual bool loadState(const ossimKeywordlist& kwl,
                          const char* prefix=0);
               
   
	void setScale(double scaleX, double scaleY);

	
	ossimRefPtr<ossimImageData> theBlankTile;
	ossimRefPtr<ossimImageData> theTile;
	

	void showImage(IplImage* src1, IplImage* src2); 

	// Declare class variables


	// Support functions for getting number of tiles, and 
	int GetTotalNumberTiles();

	
private:

	int totalTiles;
	double xScale;
	double yScale;
	int numberOfImageInputs;
	
	template<class T>
	void CopyTileToIplImage(T dummyVariable, ossimRefPtr<ossimImageData> inputTile, IplImage *output, ossimIrect neighborhoodRect);
	
	template<class T>
	void CopyIplImageToTile(T dummyVariable, ossimRefPtr<ossimImageData> inputTile, IplImage *output);


TYPE_DATA
};

#endif
