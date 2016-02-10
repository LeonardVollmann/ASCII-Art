#include "font.cpp"
#include "image.cpp"
#include "stb_image.c"

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		std::cout << "Invalid arguments." << std::endl;
		return 1;
	}

	std::string name(argv[1]);
	Image image(name.c_str());

	int width = atoi(argv[2]);
	int height = atoi(argv[3]);

	Font font = argc > 4 ? Font(argv[4]) : Font("default.fontinfo");

	std::string imageName = name.substr(0, name.find(".")) + ".txt";

	image.convertToASCII(width, height, font, imageName.c_str());

	return 0;
}
