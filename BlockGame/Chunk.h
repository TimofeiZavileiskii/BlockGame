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

	Coordinates(int inX, int inY, int inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}
};

class Chunk
{
	const int CHUNK_DIMENSION = 32;
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
};

