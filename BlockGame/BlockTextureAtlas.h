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

enum FaceSide
{
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	FACE_COUNT,
	SIDE,
	ALL
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
class BlockTexturePos;

class BlockTextureAtlas
{
	std::map<std::string, BlockTexturePos> blockCoordinates;
	Texture* atlasTexture;
	
	FaceSide ParseFileName(std::string& name);

public:
	BlockTextureAtlas(std::vector<BlockTexture> textures);

	glm::vec2 GetTextureCoords(const std::string& name, TextureCorners corner, FaceSide side);

	void UseAtlas();
};

