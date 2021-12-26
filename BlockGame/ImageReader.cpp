#include "pch.h"
#include "ImageReader.h"

#include <iostream>
#include <fstream>
#include "ErrorLoger.h"

//Spec of tga file taken from: https://en.wikipedia.org/wiki/Truevision_TGA

ImageData ImageReader::ReadTga(const std::string& address)
{
	const int RgbaSize = 4;
	const int headerLen = 18;

	unsigned char* image = nullptr;

	std::ifstream imageFile(address, std::ios::binary);

	char* header = new char[headerLen];

	imageFile.read(header, headerLen);
	
	//Parses the header of the file
	unsigned char idLen = header[0];
	unsigned char colourMapType = header[1]; //0 - if no colour map, 1 - if uses colour map
	unsigned char imageType = header[2];
	char* colourMapSpec = header + 3;
	char* imageSpec = header + 8;

	//Parse image type
	bool isCompressed = (imageType & 8); //extracts 4th bit as it signifies if the image is compressed
	int imageTypeEnum = (imageType & 7); //previous 3 bits are enum for the image 

	//Parse colour mapSpec
	unsigned short firstEntryData = colourMapSpec[0];
	unsigned short colourMapLength = colourMapSpec[2];
	unsigned char colourMapEntryLen = colourMapSpec[4];

	//Parse imageSpec
	unsigned short xOrigin = imageSpec[0];
	unsigned short yOrigin = imageSpec[2];
	unsigned short imageWidth = imageSpec[4];
	unsigned short imageHeight = imageSpec[6];
	unsigned char pixelDepth = imageSpec[8];
	unsigned char alphaChannelDepth = (imageSpec[9] & 31);
	unsigned char direction = (imageSpec[9] & 96);

	image = new unsigned char[RgbaSize * sizeof(unsigned char) * imageWidth * imageHeight];

	if (colourMapType == 0) 
	{
		int pixelSize = pixelDepth / (sizeof(char)*8);

		if (pixelSize == 3) 
		{
			for (int i = 0; i < imageWidth * imageHeight * RgbaSize; i += RgbaSize)
			{
				image[i + 2] = imageFile.get();	 //Gets red colour
				image[i + 1] = imageFile.get();  //Gets blue colour
				image[i] = imageFile.get();		 //Gets green colour
				image[i + 3] = 255;				 //Sets alpha chanell
			}
		}
	}

	delete[] header;

	return ImageData(image, imageWidth, imageHeight);
}

ImageReader::ImageReader()
{
	
}

ImageData ImageReader::ReadImage(std::string address)
{
	int lastDot = address.find_last_of('.');
	std::string_view fileExtension = std::string_view(address.c_str() + lastDot, address.length() - lastDot);
	ImageData image;

	if(fileExtension == ".tga") 
	{     
		image = ReadTga(address);
	}


	return image;
}
