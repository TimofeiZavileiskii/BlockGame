#pragma once
#include "BlockTextureAtlas.h"
#include "Block.h"
#include <set>

class Model;
class ChunkLoader;

struct Coordinates
{
	int x;
	int y;
	int z;

	inline int HashCoordinates() const
	{
		return x + 100 * y + 1000 * z;
	}

	friend bool operator<(const Coordinates &lhs, const Coordinates &rhs)
	{
		if (lhs.x != rhs.x) 
		{
			return lhs.x < rhs.x;
		}
		else if (lhs.y != rhs.y) 
		{
			return lhs.y < rhs.y;
		}
		else
		{
			return lhs.z < rhs.z;
		}
		
	}

	Coordinates(int inX, int inY, int inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}
};

class Chunk
{
	static const int CHUNK_DIMENSION = 32;
	const int chunkSize = CHUNK_DIMENSION * CHUNK_DIMENSION * CHUNK_DIMENSION;

	static BlockType* blockTypes;
	Model* chunkMesh;
	Block* blocks;
	BlockTextureAtlas* atlas;
	ChunkLoader* chunkLoader;

	Coordinates coordinates = Coordinates(0, 0, 0);

	static void AssignBlockTypes();

	void GenerateTerrain();

	inline int GetArrayPos(Coordinates coordinates);

	inline int GetArrayPos(int x, int y, int z);

public:
	void GenerateChunkMesh();

	Block* GetBlock(Coordinates coords);

	Chunk(Coordinates coord, BlockTextureAtlas* atlas, ChunkLoader* chunkLoader);

	Chunk(int x, int y, int z, BlockTextureAtlas* atlas, ChunkLoader* chunkLoader);

	~Chunk();

	void Update();

	Model* GetChunkModel();

	static int GetChunkDim();

	Coordinates GetCoordinates();
};

