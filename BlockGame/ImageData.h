#pragma once
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