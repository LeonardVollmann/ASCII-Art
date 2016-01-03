#include "image.hpp"
#include "font.hpp"

#include <cstdio>

int main(int argc, char *argv[])
{	
	Image image("/Users/leonard/Desktop/sw2.jpg");
	Font font("/Users/leonard/Desktop/ab.ttf", 32.0f, 256);
	image.convertToASCII(image.getWidth() / 4, image.getHeight() / 4, font, "/Users/leonard/Desktop/result.txt");
	image.writeToPPM("/Users/leonard/Desktop/test.ppm");
	return 0;
}