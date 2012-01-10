#include <cv.h>
#include <highgui.h>
#include <stdio.h>
using namespace cv;
int main( int argc, char** argv )
{
Mat image;
image = imread( argv[1], 1 );
if( argc != 2 || !image.data )
{
printf( "Sin datos de Imagen \n" );
return -1;
}
namedWindow( "Muestra Imagen", CV_WINDOW_AUTOSIZE );
imshow( "Imagen Mostrada", image );
waitKey(0);
return 0;
}
