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
		c.width = cdata[i].x1 - cdata[i].x0;
		c.height  = cdata[i].y1 - cdata[i].y0;
		c.symbol = i + 32;
		c.brightness = fontBuffer.getTotalBrightnessFromSubImage(cdata[i].x0, cdata[i].y0, c.width, c.height);
		m_characters.push_back(c);
		
		m_avgWidth += c.width;
		m_avgHeight += c.height;
	}
	m_avgWidth /= 94.0f;
	m_avgHeight /= 94.0f;
	
	for (Character &c : m_characters)
	{
		c.brightness = c.brightness / (m_avgWidth * m_avgHeight);
	}
}

Font::Font(const char *fileName)
{
	char buffer[1 << 12];
	fread(buffer, 1, 1 << 12, fopen(fileName, "rb"));
	
	char *save_line;
	char *line = strtok_r(buffer, "\n", &save_line);
	int i;
	while (line)
	{
		char *save_token;
		char symbol = *strtok_r(line, " ", &save_token);
		float brightness = atof(strtok_r(nullptr, " ", &save_token));
		
		Character c;
		c.symbol = symbol;
		c.brightness = brightness;
		m_characters.push_back(c);
		i++;
		
		line = strtok_r(nullptr, "\n", &save_line);
	}
}

void Font::writeFontInfo(const char *fileName)
{
	FILE *f = fopen(fileName, "wb");
	
	for (int i = 0; i < 94; i++)
	{
		fprintf(f, "%c %f\n", m_characters[i].symbol, m_characters[i].brightness);
	}
	
	fclose(f);
}

Character Font::getChar(float brightness) const
{
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