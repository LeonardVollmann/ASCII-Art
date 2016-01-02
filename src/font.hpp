#ifndef font_hpp
#define font_hpp

#include "image.hpp"

#include <vector>

struct Character
{
	char symbol;
	int x;
	int y;
	float brightness;
};

class Font
{
friend class Image;
private:
	Image m_image;
	std::vector<Character> m_characters;
	int m_charWidth;
	int m_charHeight;
public:
	Font(const char *fileName, int numX, int numY);
	~Font();
	
	Character getChar(float brightness) const;
};

#endif /* font_hpp */
