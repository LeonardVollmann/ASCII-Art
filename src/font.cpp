#include "font.hpp"

#include <cmath>

Font::Font(const char *fileName, int numX, int numY)
: m_image(fileName)
, m_charWidth(m_image.m_width / numX)
, m_charHeight(m_image.m_height / numY)
{
	for (int row = 0; row < numY; row++)
	{
		for (int col = 0; col < numX; col++)
		{
			Character c;
			c.x = col * m_charWidth;
			c.y = row * m_charHeight;
			c.brightness = m_image.getAverageBrightnessFromSubImage(col * m_charWidth, row * m_charHeight, m_charWidth, m_charHeight);
			m_characters.push_back(c);
		}
	}
}

Font::~Font()
{
}

Character Font::getChar(float brightness) const
{
	Character result = m_characters[0];
	for (auto c : m_characters)
	{
		if (fabs(c.brightness - brightness) < fabs(result.brightness - brightness))
		{
			result = c;
		}
	}
	return result;
}