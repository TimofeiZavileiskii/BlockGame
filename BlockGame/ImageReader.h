#pragma once
#include <string>
#include "ImageData.h"

class ImageReader
{
	//Reads tga file and outputs char array with rgba values
	ImageData ReadTga(const std::string& address);

public:
	ImageReader();

	ImageData ReadImage(const std::string address);

};

