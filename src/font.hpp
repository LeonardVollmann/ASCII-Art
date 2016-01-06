#ifndef font_hpp
#define font_hpp

#include "image.hpp"

#include <vector>

struct Character
{
	char symbol;
	float brightness;
	int width;
	int height;
};

class Font
{
friend class Image;
private:
	std::vector<Character> m_characters;
	float m_avgWidth;
	float m_avgHeight;
public:
	Font(const char *fileName, float size, int bitmapSize);
	Font(const char *fileName);
	
	void readFontInfo(const char *fileName);
	void writeFontInfo(const char *fileName);
	
	Character getChar(float brightness) const;
};

#endif /* font_hpp */
