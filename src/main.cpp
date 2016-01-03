#include "image.hpp"
#include "font.hpp"

int main(int argc, char *argv[])
{
	Image image("/Users/leonard/Desktop/sw6.jpg");
	Font font("/Users/leonard/Desktop/gradient.png", 32, 32);
	image.convertToASCII(image.getWidth(), image.getHeight(), font, "/Users/leonard/Desktop/result.ppm");
	image.writeToPPM("/Users/leonard/Desktop/test.ppm");
	return 0;
}