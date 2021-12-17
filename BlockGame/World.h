#pragma once
#include "Entity.h"
#include "Camera.h"
#include "Model.h"

class Window;

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

	std::string GetTexture() 
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

enum BlockId
{
	AIR, STONE,
	BLOCK_ID_LENGTH
};

class World
{
private:
	const int CHUNK_DIMENSION = 32;
	const int chunkSize = CHUNK_DIMENSION * CHUNK_DIMENSION * CHUNK_DIMENSION;

	Window* window;
	Camera* camera;
	Model* worldMesh;
	double passedTime;

	Block* blockData;
	BlockType* blockTypes;

	void FillBlockData();

	void AssignBlockTypes();

	void UpdateCamera();

	void GenerateChunkMesh();

	inline int GetCoord(int x, int y, int z);

public:
	World(Window* inWindow);

	void Update();

	Camera* GetCamera();

	Model* GetChunkMesh();
};

