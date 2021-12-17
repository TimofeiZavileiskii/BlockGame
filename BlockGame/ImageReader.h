#pragma once
#include <string>

struct ImageData
{
	int width;
	int height;
	
	unsigned char* imageData;

	ImageData(unsigned char* data, int inWidth, int inHeight)
	{
		imageData = data;
		width = inWidth;
		height = inHeight;
	}

	ImageData()
	{
	}
};

class ImageReader
{
	//Reads tga file and outputs char array with rgba values
	ImageData ReadTga(const std::string& address);

public:
	ImageReader();

	ImageData ReadImage(const std::string address);

};

