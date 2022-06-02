#pragma once
#include "BlockTextureAtlas.h"
#include "Block.h"
#include "Coordinates.h"
#include <set>

class Model;
class ChunkLoader;
class CubeMeshCreator;

enum ChunkState {
	UNROCESSED,
	TERRAIN_WORKED_ON,
	TERRAIN_GENERATED,
	MODEL_WORKED_ON,
	MODEL_GENERATED,
	FINISHED
};

class Chunk
{
	static const int CHUNK_DIMENSION = 64;
	const int chunkSize = CHUNK_DIMENSION * CHUNK_DIMENSION * CHUNK_DIMENSION;

	static BlockType* blockTypes;
	Model* chunkMesh;
	Block* blocks;
	BlockTextureAtlas* atlas;
	ChunkLoader* chunkLoader;
	CubeMeshCreator* meshCreator;

	ChunkState state;

	Coordinates coordinates;

	static void AssignBlockTypes();

	inline int GetArrayPos(Coordinates coordinates);

	inline int GetArrayPos(int x, int y, int z);

public:
	void GenerateTerrain();

	void GenerateChunkMesh();

	void FiniliseMesh();

	Block* GetBlock(Coordinates coords);

	Block* GetBlock(int x, int y, int z);

	Chunk(Coordinates coord, BlockTextureAtlas* atlas, ChunkLoader* chunkLoader);

	Chunk(int x, int y, int z, BlockTextureAtlas* atlas, ChunkLoader* chunkLoader);

	~Chunk();

	void Update();

	Model* GetChunkModel();

	static int GetChunkDim();

	ChunkState GetState();

	void StartProccessingTerrain();

	void StartProccessingModel();

	Coordinates GetCoordinates();
};

