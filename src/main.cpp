#include "image.hpp"
#include "font.hpp"

int main(int argc, char *argv[])
{
	Image image("/Users/leonard/Desktop/sw2.jpg");
	Font font("/Users/leonard/Desktop/sw2.jpg", 12, 12);
	image.convertToASCII(12, 12, font, "/Users/leonard/Desktop/result");
	image.writeToPPM("/Users/leonard/Desktop/test.ppm");
	return 0;
}