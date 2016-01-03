#include "font.hpp"

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include <cmath>
#include <cstdlib>

Font::Font(const char *fileName, float size, int bitmapSize)
{
	stbtt_bakedchar cdata[96];
	unsigned char ttfBuffer[1<<20];
	Image fontBuffer(bitmapSize, bitmapSize);

	fread(ttfBuffer, 1, 1 << 20, fopen(fileName, "rb"));
	stbtt_BakeFontBitmap(ttfBuffer, 0, size, fontBuffer.m_pixels, bitmapSize, bitmapSize, 32, 96, cdata);
	
	for (int i = 1; i < 95; i++)
	{
		Character c;
		c.symbol = i + 32;
		c.x0 = cdata[i].x0;
		c.x1 = cdata[i].x1;
		c.y0 = cdata[i].y0;
		c.y1 = cdata[i].y1;
		c.brightness = fontBuffer.getAverageBrightnessFromSubImage(c.x0, c.y0, c.x1 - c.x0, c.y1 - c.y0);
		m_characters[i - 1] = c;
	}
}

Character Font::getChar(float brightness) const
{
	brightness = 1.0f - brightness;
	int result = 0;
	for (int i = 0; i < 94; i++)
	{
		if (fabs(m_characters[i].brightness - brightness) < fabs(m_characters[result].brightness - brightness))
		{
			result = i;
		}
	}
	return m_characters[result];
}