#pragma once
#include <map>
#include <vector>

#include "BlockTextureAtlas.h"

class Chunk;
class Model;
struct Coordinates;

class ChunkLoader
{
	std::map<int, Chunk*> chunks;
	std::vector<Model*> chunkModels;
	BlockTextureAtlas* atlas;

	int HashCoordinates(Coordinates coords);


public:
	ChunkLoader(BlockTextureAtlas* atlas);

	void Update();

	std::vector<Model*>& GetChunkModels();

	Chunk* GetChunk(Coordinates coords);

	Chunk* GetChunk(int x, int y, int z);

};

