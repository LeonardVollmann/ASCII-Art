#ifndef image_hpp
#define image_hpp

class Font;

class Image
{
	friend class Font;
public:
	Image(int width, int height);
	Image(const char *fileName);
	~Image();
	
	void convertToASCII(int xRes, int yRes, const Font &font, const char *name);
	
	float getAverageBrightnessFromSubImage(int x, int y, int width, int height);
	void writeToPPM(const char *fileName);
private:
	int m_width;
	int m_height;
	unsigned char *m_pixels;
};

#endif /* image_hpp */
