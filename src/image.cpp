#include "image.hpp"
#include "stb_image.h"
#include "font.hpp"

#include <cstdlib>

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
	const int numRows = m_height / font.m_charHeight;
	const int numCols = m_width / font.m_charWidth;
	const int subImageWidth = m_width / numCols;
	const int subImageHeight = m_height / numRows;
	
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			Character c = font.getChar(getAverageBrightnessFromSubImage(col * subImageWidth, row * subImageHeight, subImageWidth, subImageHeight));
			for (int y = 0; y < font.m_charWidth; y++)
			{
				for (int x = 0; x < font.m_charWidth; x++)
				{
					int i1 = col * font.m_charWidth + x + (row * font.m_charHeight) * result.m_width;
					int i2 = c.x + x + (c.y + y) * font.m_charWidth;
					result.m_pixels[i1] =
						font.m_image.m_pixels[i2];
				}
			}
		}
	}

	char *ppm;
	strcpy(ppm, name);
	strcat(ppm, ".ppm");
	result.writeToPPM(ppm);
}

float Image::getAverageBrightnessFromSubImage(int x, int y, int width, int height)
{
	float avg = 0.0f;
	for (int yy = y;  yy < height; yy++)
	{
		for (int xx = x; xx < width; xx++)
		{
			avg += (float) m_pixels[x + xx + (y + yy) * m_width];
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