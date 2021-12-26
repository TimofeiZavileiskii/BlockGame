#include "pch.h"
#include "BlockTextureAtlas.h"
#include <cstring>

struct TexturePos 
{
	float offset;
	float height;
	float width;

	TexturePos(float offset, float height) 
	{
		this->offset = offset;
		this->height = height;
		this->width = width;
	}

	TexturePos() {

	}
};

BlockTextureAtlas::BlockTextureAtlas(std::vector<BlockTexture> textures)
{
	const int RGBAlen = 4;

	float blockOffset = 0.0f;
	int totalChars = 0;
	int totalHeight = 0;

	for (BlockTexture &texture : textures) 
	{
		totalChars += texture.texture.height * texture.texture.width;
		totalHeight += texture.texture.height;
	}

	for (BlockTexture& texture : textures)
	{
		float relativeHeight = (float)texture.texture.height / (float)totalHeight;
		blockCoordinates[texture.name] =  TexturePos(blockOffset, relativeHeight);
		blockOffset += relativeHeight;
	}

	unsigned char* atlasTexturePixels = new unsigned char[totalChars * RGBAlen];
	
	int index = 0;
	for (BlockTexture& texture : textures)
	{
		int bytesInTexture = texture.texture.height * texture.texture.width * RGBAlen;
		memcpy((void*)(atlasTexturePixels + index), texture.texture.imageData, bytesInTexture);
		index += bytesInTexture;
	}

	const int indexFirstTexture = 0;

	atlasTexture = new Texture(atlasTexturePixels, textures[indexFirstTexture].texture.width, totalHeight);

	delete[] atlasTexturePixels;
}

glm::vec2 BlockTextureAtlas::GetTextureCoords(const std::string& name, TextureCorners corner)
{
	glm::vec2 cornerCoords = glm::vec2(0.0f, blockCoordinates[name].offset);
	float offset = blockCoordinates[name].offset;
	float height = blockCoordinates[name].height;

	switch (corner) 
	{
	case LEFTDOWN:
		break;
	case LEFTUP:
		cornerCoords.y += height;
		break;
	case RIGHTDOWN:
		cornerCoords.x = 1;
		break;
	case RIGHTUP:
		cornerCoords.x = 1;
		cornerCoords.y += blockCoordinates[name].height;
		break;
	}

	return cornerCoords;
}

void BlockTextureAtlas::UseAtlas()
{
	atlasTexture->Bind();
}