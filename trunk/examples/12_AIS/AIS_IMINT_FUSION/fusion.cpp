#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/core/cs.hpp>

using namespace boost::geometry;

using namespace boost;

using namespace std;

class AisTip{
public:
	AisTip(){
		name = "";
		callsign = "";
		mmsi = "";
		imo = "";
		vessel_type_int = 0;
		latitude = 0;
		longitude = 0;
		heading = 0;
		speed = 0;
		length = 0;
		width = 0;
	}
	AisTip(string name, string mmsi, string callsign, string imo, int vessel_type_int, double lat, double lon, double heading, double speed, double length, double width){
		this->name = name;
		this->mmsi = mmsi;
		this->callsign = callsign;
		this->imo = imo;
		this->vessel_type_int = vessel_type_int;
		this->latitude = lat;
		this->longitude = lon;
		this->heading = heading;
		this->speed = speed;
		this->length = length;
		this->width = width;
	}
	
	void print(ostream &stream) const{
		stream << 
			this->name << ", " << 
			this->mmsi <<", " << 
			this->callsign <<", " << 
			this->imo <<", " << 
			this->vessel_type_int<<", " << 
			this->latitude <<", " << 
			this->longitude <<", " << 
			this->heading<<", " << 
			this->speed <<", " << 
			this->length <<", " << 
			this->width <<endl;
	}

	string name;
	string mmsi;
	string callsign;
	string imo;
	double latitude;
	double longitude;
	double heading;
	double speed;
	double length;
	double width;
	int vessel_type_int;
};

class ImageTip{
public:
	ImageTip(){
		latitude = 0;
		longitude = 0;
		area = 0;
		heading = 0;
		length = 0;
		width = 0;
	}
	ImageTip(double lat, double lon, double area, double heading, double length, double width){
		this->latitude = lat;
		this->longitude = lon;
		this->heading = heading;
		this->area = area;
		this->length = length;
		this->width = width;
	}
	void print(ostream& stream) const
	{
		stream << 
			latitude << ", " << 
			longitude << ", " << 
			area << ", " << 
			heading << ", " << 
			length << ", " << 
			width << endl;
	}

	double latitude;
	double longitude;
	double area;
	double heading;
	double length;
	double width;
};


void loadTips(vector<AisTip>& aisTips, vector<ImageTip>& imageTips){	
	//load the vectors with some data
	//the tips from the imagery detections and ais messages
	//ofstream out("ais.kml", ios::out);
	//	//write header
	//out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
	//	   "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"
	//	   "<Document>" << endl;
		
	ifstream ais("20110326092524_ais.csv", ios::in);
	if(!ais.good())
	{
		throw std::runtime_error("Can't open AIS csv (20110326092524_ais.csv), please make sure it is in the same directory as the exe");
	}
	
	bool skipFirst = true;
	while(!ais.eof())
	{
		string line;
		getline(ais, line);

		if(skipFirst)
		{
			skipFirst = false;
			continue;
		}
		
		AisTip tip;
		vector<string> parsed_line;
		split(parsed_line,line, is_any_of(","));
		
		for(int i=0; i<parsed_line.size(); i++)
		{
			trim(parsed_line[i]);
			//cout << parsed_line[i] << endl;
		}

		if(parsed_line.size()==10)
		{
			try{
				tip.mmsi = parsed_line[0];
				tip.latitude = lexical_cast<double>(parsed_line[1]);
				tip.longitude = lexical_cast<double>(parsed_line[2]);
				tip.imo = parsed_line[4];
				tip.vessel_type_int = lexical_cast<int>(parsed_line[5]);
				tip.name = parsed_line[6];
				tip.callsign = parsed_line[7];
				tip.length = lexical_cast<double>(parsed_line[8]);
				tip.width = lexical_cast<double>(parsed_line[9]);
			}catch(std::exception &e){
				cerr << e.what() << endl;
				return;
			}
			aisTips.push_back(tip);

		//	///////////////////////////
		//out << "<Placemark>" << endl;
		////out << "<name>" << tip.name << "</name>" << endl;
		//out << "<description>\nAIS:";
		//tip.print(out);
		//out << "</description>"<< endl;
		//out << "<styleUrl>#msn_placemark_circle_med0</styleUrl>"<< endl;
		//out << "<Point>\n<coordinates>" << endl;
		//out.precision(10);
		//out << tip.longitude << "," << tip.latitude << ",0" << endl;
		//out << "</coordinates>\n</Point>" << endl;
		//out << "</Placemark>" << endl;

		/////////////////////////////

		}else{
			//cout << parsed_line.size() << " is not 10" << endl;
			//return;	
		}
	}
	ais.close();
	
	//out << "</Document>\n"
	//	   "</kml>" << endl;

	//out.close();




	//Image Detections
	ifstream image ("20110326092524_image.csv" , ios::in);
	if(!image.good())
	{
		throw std::runtime_error("Can't open IMAGE csv (20110326092524_image.csv), please make sure it is in the same directory as the exe");
	}

	skipFirst = true;
	while(!image.eof())
	{
		string line;
		getline(image, line);

		if(skipFirst)
		{
			skipFirst = false;
			continue;
		}
		
		ImageTip tip;
		vector<string> parsed_line;
		split(parsed_line,line, is_any_of(","));
		
		for(int i=0; i<parsed_line.size(); i++)
		{
			trim(parsed_line[i]);
		//	cout << parsed_line[i] << endl;
		}
		if(parsed_line.size()==20)
		{
			try{
				tip.latitude = lexical_cast<double>(parsed_line[1]);
				tip.longitude = lexical_cast<double>(parsed_line[2]);
				tip.heading = lexical_cast<double>(parsed_line[3]);
				tip.length = lexical_cast<double>(parsed_line[5]);
				tip.width = lexical_cast<double>(parsed_line[6]);
				tip.area = tip.length * tip.width;
			}catch(std::exception &e){
				cerr << e.what() << endl;
				return;
			}
			imageTips.push_back(tip);
		}else{
			//cout << parsed_line.size() << " is not 10" << endl;
			//return;	
		}
	}

	image.close();

}

class Match{
public:
	Match()
	{
		confidence = 0;
		distance = 0;
	}
	AisTip ais;
	ImageTip image;
	double distance;
	double confidence;
};




void findMatches(const vector<AisTip>& aisTips, const vector<ImageTip>& imageTips,  vector<Match> &matches)
{
	typedef boost::geometry::model::point
		<double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree>> spherical_point;
	//double const earth_radius = 3959; // miles
	double const earth_radius = 6371390; //meters

	double DISTANCE_THRESH = 2500; //meters
	//find closest coordinates
	for(int j=0; j<imageTips.size(); j++)
	{
		double minDistance = numeric_limits<double>::max( );
		int minIndex = 0;
		for(int i=0; i<aisTips.size(); i++)
		{
			spherical_point aisPos(aisTips[i].longitude, aisTips[i].latitude);
			spherical_point imagePos(imageTips[j].longitude, imageTips[j].latitude);
			double distance = boost::geometry::distance(aisPos, imagePos)*earth_radius;
			//double distance = sqrt((aisTips[i].latitude - imageTips[j].latitude)*(aisTips[i].latitude - imageTips[j].latitude) + (aisTips[i].longitude-imageTips[j].longitude)*(aisTips[i].longitude-imageTips[j].longitude));
			//cout << "distance: " << distance << endl;
			if(distance < minDistance)
			{
				minDistance = distance;
				minIndex = i;
			}
		}
		//cout << "minDistance: " << minDistance << endl;
		if(minDistance < DISTANCE_THRESH)
		{
			Match match;
			match.ais = aisTips[minIndex];
			match.image = imageTips[j];
			match.distance = minDistance;
			match.confidence = 0.5;
			
			if(sqrt((match.ais.length - match.image.length)*(match.ais.length - match.image.length)) < 10)
			{
				match.confidence += 0.25;
			}
			
			if(sqrt((match.ais.width - match.image.width)*(match.ais.width - match.image.width)) < 10)
			{
				match.confidence += 0.25;
			}

			matches.push_back(match);
		}
	}

}

void writeMatchesKml(const vector<Match> &matches)
{
	ofstream out("fusion.kml", ios::out);

	if(!out.good())
	{
		throw std::runtime_error("Cannot open output file fusion.kml");
	}

	//write header
	out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
		   "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"
		   "<Document>" << endl;

	for(int i=0; i<matches.size(); i++)
	{
		out << "<Placemark>" << endl;
		out << "<name>" << matches[i].ais.name << " confidence: " << matches[i].confidence << "</name>" << endl;
		out << "<LineString>\n<coordinates>" << endl;
		out.precision(10);
		out << matches[i].ais.longitude << "," << matches[i].ais.latitude << ",0" << endl;
		out << matches[i].image.longitude << "," << matches[i].image.latitude << ",0" << endl;
		out << "</coordinates>\n</LineString>" << endl;
		out << "</Placemark>" << endl;
		out << "<Placemark>" << endl;
		out << "<name>" << matches[i].ais.name << " image detection</name>" << endl;
		out << "<description>\nAIS:";
		matches[i].ais.print(out);
		out << "IMAGE:";
		matches[i].image.print(out);
		out << "confidence: " << matches[i].confidence << endl;
		out << "distance: " << matches[i].distance << " meters" << endl;
		out << "</description>"<< endl;
		out << "<Point>\n<coordinates>" << endl;
		out.precision(10);
		out << matches[i].image.longitude << "," << matches[i].image.latitude << ",0" << endl;
		out << "</coordinates>\n</Point>" << endl;
		out << "</Placemark>" << endl;
		out << "<Placemark>" << endl;
		out << "<name>" << matches[i].ais.name << " ais detection</name>" << endl;
		out << "<description>\nAIS:";
		matches[i].ais.print(out);
		out << "IMAGE:";
		matches[i].image.print(out);
		out << "confidence: " << matches[i].confidence << endl;
		out << "distance: " << matches[i].distance << " meters" << endl;
		out << "</description>"<< endl;
		out << "<Point>\n<coordinates>" << endl;
		out.precision(10);
		out << matches[i].ais.longitude << "," << matches[i].ais.latitude << ",0" << endl;
		out << "</coordinates>\n</Point>" << endl;
		out << "</Placemark>" << endl;
	}

	out << "</Document>\n"
		   "</kml>" << endl;

	out.close();
}

int main(int argc, char** argv){

	try
	{
		vector<AisTip> aisTips;
		vector<ImageTip> imageTips;

		//Load in the tips from files (or a database)
		cout << "Loading in ais and imagery detections...";
		loadTips(aisTips, imageTips);
		cout << "Done!" << endl;

		//find matching tips
		vector<Match> matches;
		cout << "Finding matches...";
		findMatches(aisTips, imageTips, matches);
		cout << "Done!" <<endl;

		//write matches to file
		cout << "Writing fusion kml...";
		writeMatchesKml(matches);
		cout << "Done!" << endl;
	}
	catch(std::exception& e)
	{
		cerr << "Error Occured" << endl;
		cerr << e.what() << endl;
	}
	return 0;
}
