#pragma once
#include "Block.h"

class Model;

class Chunk
{
	const int CHUNK_DIMENSION = 32;
	const int chunkSize = CHUNK_DIMENSION * CHUNK_DIMENSION * CHUNK_DIMENSION;
	static BlockType* blockTypes;

	Model* chunkMesh;
	Block* blocks;

	static void AssignBlockTypes();

	void GenerateTerrain();

	void GenerateChunkMesh();

	inline int GetCoord(int x, int y, int z);

public:
	Chunk();

	void Update();

	Model* GetChunkModel();

};

