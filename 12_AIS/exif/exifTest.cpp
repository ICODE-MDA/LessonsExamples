#include <iostream>
#include <libexif/exif-data.h>
#include <libexif/exif-log.h>
#include <libexif/exif-mem.h>

using namespace std;

int main(){
	
	ExifData* exifData = exif_data_new_from_file("photo.jpg");
	if(!exifData){
		cout << "Exif Data was BAD" << endl;
	}else{
		cout << "Exif Data good" << endl;	
	}
	
	exif_data_dump(exifData);

	return 0;
}