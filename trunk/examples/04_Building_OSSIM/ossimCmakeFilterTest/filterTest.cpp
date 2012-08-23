#include <ossim/init/ossimInit.h>
#include <ossim/base/ossimException.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/imaging/ossimImageChain.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageGaussianFilter.h>
#include <ossim/imaging/ossimImageFileWriter.h>
#include <ossim/imaging/ossimImageWriterFactoryRegistry.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/base/ossimStdOutProgress.h>
#include <ossim/base/ossimTimer.h>

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		cout << "need one argument" << endl;
		return 1;
	}
	// Initialize ossim stuff, factories, plugin, etc.
	ossimInit::instance()->initialize();

		// the image name
	ossimFilename image_file = argv[1];

	// Declare ossim ImageHandler and open input image
	ossimRefPtr<ossimImageHandler> ih = ossimImageHandlerRegistry::instance()->open(image_file);

	// Check to see if image handler is valid
	if (ih.valid())
	{
		// Instantiate the rigorous model:
		ossimRefPtr<ossimImageGeometry> geom = ih->getImageGeometry();

		// Now print the geometry information for the file
		cout << "Geometry: " << geom->print(cout) << endl;


		cout << "Connecting handler to TileToIplFilter " << endl;
		ossimRefPtr<ossimImageGaussianFilter> filter = new ossimImageGaussianFilter();
		filter->setGaussStd(5);
		
		filter->connectMyInputTo(0,ih.get());
		cout << "Connected!" << endl;
		
		// Declare writer
		ossimRefPtr<ossimImageFileWriter> writer =
			ossimImageWriterFactoryRegistry::instance()->
			createWriterFromExtension("tiff");

		if ( writer->open( "outputImage.tiff" ) )
		{
			// Add a listener to get percent complete.
			ossimStdOutProgress prog(0, true);
			writer->addListener(&prog);

			writer->connectMyInputTo(0, filter.get());

			// Set the cut rect to the input image.
			writer->setAreaOfInterest(ih->getBoundingRect());

			cout << "Writing the image..." << endl;
			writer->execute();

			cout << "Wrote file: " << "outputImage.tiff"
				<< "\nElapsed time(seconds): "
				<< ossimTimer::instance()->time_s() << "\n";
		}
		else
		{
			cout << "Could not open: " << argv[3] << endl;
		}

		filter->disconnect();
		filter = 0;

	}
	cout << "Done!" << endl;


	return 0;


}