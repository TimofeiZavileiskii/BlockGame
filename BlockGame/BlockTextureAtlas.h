#pragma once
#include "Texture.h"
#include "ImageData.h"

enum TextureCorners
{
	LEFTUP,
	LEFTDOWN,
	RIGHTUP,
	RIGHTDOWN
};

struct BlockTexture
{
	std::string name;
	ImageData texture;

	BlockTexture(const std::string& name, ImageData image)
	{
		this->name = name;
		texture = image;
	}
};

struct TexturePos;

class BlockTextureAtlas
{
	std::map<std::string, TexturePos> blockCoordinates;
	Texture* atlasTexture;
	
public:
	BlockTextureAtlas(std::vector<BlockTexture> textures);

	glm::vec2 GetTextureCoords(const std::string& name, TextureCorners corner);

	void UseAtlas();
};

