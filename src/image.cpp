#include "image.hpp"
#include "stb_image.h"
#include "font.hpp"

#include <cstdlib>
#include <deque>

Image::Image(int width, int height)
: m_width(width)
, m_height(height)
{
	m_pixels = new unsigned char[width * height];
}

Image::Image(const char *fileName)
{
	unsigned char *result = stbi_load(fileName, &m_width, &m_height, nullptr, 1);
	m_pixels = new unsigned char[m_width * m_height];
	memcpy(m_pixels, result, m_width * m_height * sizeof(unsigned char));
	stbi_image_free(result);
}

Image::~Image()
{
	delete m_pixels;
}

void Image::convertToASCII(int resX, int resY, const Font &font, const char *name)
{
	Image result(font.m_charWidth * resX, font.m_charHeight * resY);
	const int subImageWidth = m_width / resX;
	const int subImageHeight = m_height / resY;
	const int numCols = m_width / subImageWidth;
	const int numRows = m_height / subImageHeight;
	
	std::deque<Character> chars;
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			chars.push_back(font.getChar(getAverageBrightnessFromSubImage(col * subImageWidth, row * subImageHeight, subImageWidth, subImageHeight)));
		}
	}
	
	for (int y = 0; y < resY; y++)
	{
		for (int x = 0; x < resX; x++)
		{
			Character c = chars.front();
			chars.pop_front();
			for (int yy = 0; yy < font.m_charHeight; yy++)
			{
				for (int xx = 0; xx < font.m_charWidth; xx++)
				{
					result.m_pixels[x * font.m_charWidth + xx + (y * font.m_charHeight + yy) * result.m_width] =
						font.m_image.m_pixels[c.x + xx + (c.y + yy) * font.m_image.m_width];
				}
			}
		}
	}

	result.writeToPPM(name);
}

float Image::getAverageBrightnessFromSubImage(int x, int y, int width, int height)
{
	float avg = 0.0f;
	for (int yy = y;  yy < y + height; yy++)
	{
		for (int xx = x; xx < x + width; xx++)
		{
			avg += (float) m_pixels[xx + yy * m_width];
		}
	}
	return avg / (width * height * 255.0f);
}

void Image::writeToPPM(const char *fileName)
{
	FILE *f = fopen(fileName, "wb");
	fprintf(f, "P5 %d %d 255\n", m_width, m_height);
	fwrite((void *) m_pixels, sizeof(unsigned char) * m_height * m_width, 1, f);
	fclose(f);
}