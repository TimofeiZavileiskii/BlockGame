#pragma once
#include <glad/glad.h>

class Texture
{
	unsigned int index;
	int textureSize;

public:
	Texture(unsigned char* image, int width, int height);

	void Bind() const;

};

