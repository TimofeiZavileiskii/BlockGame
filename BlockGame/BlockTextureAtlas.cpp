#include "pch.h"
#include "BlockTextureAtlas.h"
#include <cstring>

struct TexturePos
{
	float offset;
	float height;

	TexturePos(float offset, float height)
	{
		this->offset = offset;
		this->height = height;
	}

	TexturePos() {}
};

class BlockTexturePos
{
private:
	TexturePos BlockTextures[FACE_COUNT];

public:
	TexturePos GetFaceTexture(FaceSide side)
	{
		return BlockTextures[side];
	}
	
	void AddTexture(TexturePos text, FaceSide side) 
	{
		switch (side) 
		{
		case ALL:
			BlockTextures[TOP] = text;
			BlockTextures[BOTTOM] = text;
			BlockTextures[LEFT] = text;
			BlockTextures[RIGHT] = text;
			BlockTextures[FRONT] = text;
			BlockTextures[BACK] = text;
			break; 
		case SIDE:
			BlockTextures[LEFT] = text;
			BlockTextures[RIGHT] = text;
			BlockTextures[FRONT] = text;
			BlockTextures[BACK] = text;
			break;
		default:
			BlockTextures[side] = text;
			break;
		}
	}
};

FaceSide BlockTextureAtlas::ParseFileName(std::string& name)
{
	if (name.find('_') != -1)
	{
		int nameStarts = name.find('_');
		std::string face = name.substr(0, nameStarts);
		name = name.substr(nameStarts + 1, name.size() - nameStarts);
		if (face == "Bottom")
		{
			return BOTTOM;
		}
		else if (face == "Top")
		{
			return TOP;
		}
		else if (face == "Side")
		{
			return SIDE;
		}
		else if (face == "Left")
		{
			return LEFT;
		}
		else if (face == "Right")
		{
			return RIGHT;
		}
		else if (face == "Front")
		{
			return FRONT;
		}
		else if (face == "Back")
		{
			return BACK;
		}
	}
	else
	{
		return ALL;
	}
}

BlockTextureAtlas::BlockTextureAtlas(std::vector<BlockTexture> textures)
{
	const int RGBAlen = 4;

	float blockOffset = 0.0f;
	int totalChars = 0;
	int totalHeight = 0;

	for (BlockTexture& texture : textures) 
	{
		totalChars += texture.texture.height * texture.texture.width;
		totalHeight += texture.texture.height;
	}



	for (BlockTexture& texture : textures)
	{
		float relativeHeight = (float)texture.texture.height / (float)totalHeight;

		std::string name = texture.name;
		FaceSide side = ParseFileName(name);
	    
		if (blockCoordinates.find(name) == blockCoordinates.end()) 
		{
			blockCoordinates[name] = BlockTexturePos();
		}

		blockCoordinates[name].AddTexture(TexturePos(blockOffset, relativeHeight), side);

		blockOffset += relativeHeight;
	}


	//Creates one combined texture
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

glm::vec2 BlockTextureAtlas::GetTextureCoords(const std::string& name, TextureCorners corner, FaceSide side)
{
	TexturePos textPos = blockCoordinates[name].GetFaceTexture(side);
	glm::vec2 cornerCoords = glm::vec2(0.0f, textPos.offset);
	float height = textPos.height;

	switch (corner) 
	{
	case LEFTDOWN:
		cornerCoords.y += height;
		break;
	case LEFTUP:
		break;
	case RIGHTDOWN:
		cornerCoords.y += textPos.height;
		cornerCoords.x = 1;
		break;
	case RIGHTUP:
		cornerCoords.x = 1;
		break;
	}
	
	return cornerCoords;
}

void BlockTextureAtlas::UseAtlas()
{
	atlasTexture->Bind();
}