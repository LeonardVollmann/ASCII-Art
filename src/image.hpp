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
	
	void convertToASCII(int xRes, int yRes, const Font &font, const char *fileName);
	
	float getTotalBrightnessFromSubImage(int x, int y, int width, int height);
	float getAverageBrightnessFromSubImage(int x, int y, int width, int height);
	void writeToPPM(const char *fileName);
	
	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
private:
	int m_width;
	int m_height;
	unsigned char *m_pixels;
	float m_brightnessCorrectionBias;
};

#endif /* image_hpp */
