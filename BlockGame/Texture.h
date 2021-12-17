#pragma once

class Texture
{
	unsigned int index;

public:
	Texture(unsigned char* image, int width, int height);

	void Bind() const;

};

