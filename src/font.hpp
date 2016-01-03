#ifndef font_hpp
#define font_hpp

#include "image.hpp"

#include <vector>

struct Character
{
	char symbol;
	int x0, x1, y0, y1;
	int x;
	int y;
	float brightness;
};

class Font
{
friend class Image;
private:
	Character m_characters[94];
public:
	Font(const char *fileName, float size, int bitmapSize);
	
	void readFontInfo(const char *fileName);
	void writeFontInfo(const char *fileName);
	
	Character getChar(float brightness) const;
};

#endif /* font_hpp */
