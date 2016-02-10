#include "font.cpp"
#include "image.cpp"
#include "stb_image.c"

#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments." << std::endl;
		return 1;
	}

	Font font(argv[1], atof(argv[2]), 16 * atof(argv[2]));

	std::string name(argv[1]);
	name = name.substr(0, name.find(".")) + ".fontinfo";
	font.writeFontInfo(name.c_str());

	return 0;
}