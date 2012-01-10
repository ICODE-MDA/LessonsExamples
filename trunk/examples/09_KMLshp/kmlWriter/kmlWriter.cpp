#include "kmlWriter.h"

	kmlWriter::kmlWriter(string filename){
		_filename = filename;
		_stream.open(_filename.c_str());
		if(isGood()){
			writeHeader();
		}
	}
	bool kmlWriter::isGood(){
		return _stream.good();
	}

	kmlWriter::~kmlWriter(){
		if(_stream.is_open()){
			writeFooter();
			_stream.close();
		}
	}


	void kmlWriter::writePlacemark(string name, string description, double lon, double lat, double height){
		_stream << "	<Placemark>" << endl;
		_stream << "		<name>" << name << "</name>" << endl;
		_stream << "		<description>" << description << "</description>" <<endl;
		_stream << "		<Point>" << endl;
		_stream << "			<coordinates>"<< lon << "," << lat << "," << height << "</coordinates>" << endl;
		_stream << "		</Point>" << endl;
		_stream << "	</Placemark>" << endl;
	}

	void kmlWriter::writePath(string name, string description, vector< vector<double> >& coordinates, int extrude, int tessellate, string altitude){
		_stream << "	<Placemark>" << endl;
		_stream << "		<name>" << name << "</name>" << endl;
		_stream << "		<description>" << description << "</description>" << endl;
		_stream << "		<LineString>" << endl;
		_stream << "			<extrude>" << extrude << "</extrude>" << endl;
		_stream << "			<tessellate>" << tessellate << "</tessellate>" << endl;
		_stream << "			<altitudeMode>" << altitude << "</altitudeMode>" << endl;
		_stream << "			<coordinates>" << endl;
		for(int i = 0; i< coordinates.size(); i++){
			if(coordinates[i].size() == 3){
			_stream << "				" << coordinates[i][0] << "," << coordinates[i][1] << "," <<coordinates[i][2] << endl;
			}else{
				cout << "kmlWriter::writePath coordinates must be size Nx3" << endl;
			}
		}
		_stream << "			</coordinates>" << endl;
		_stream << "		</LineString>" << endl;
		_stream << "	</Placemark>" << endl;

	}

	void kmlWriter::writeHeader(){
		_stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
		_stream << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">" << endl;
		_stream << "<Document>" << endl;
	}

	void kmlWriter::writeFooter(){
		_stream << "</Document>" << endl;
		_stream << "</kml>" << endl;
	}

