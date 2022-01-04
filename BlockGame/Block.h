#pragma once
enum BlockId
{
	AIR, STONE, SAND, DIRT, BRICK, GRASS,
	BLOCK_ID_LENGTH
};

struct BlockType
{
	bool transparent;
	std::string texture;

	BlockType(bool inTransparent, const std::string& inTexture)
	{
		transparent = inTransparent;
		texture = inTexture;
	}

	BlockType(bool inTransparent, const char* inTexture)
	{
		transparent = inTransparent;
		texture = std::string(inTexture);
	}

	BlockType() { }
};

struct Block
{
	BlockType* type;

	Block(BlockType* inType)
	{
		type = inType;
	}

	std::string& GetTexture()
	{
		return type->texture;
	}

	bool GetTransperency()
	{
		return type->transparent;
	}

	BlockType* GetType()
	{
		return type;
	}

	Block() { }
};