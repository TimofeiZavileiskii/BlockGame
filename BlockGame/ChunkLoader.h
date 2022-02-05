#pragma once
#include <map>
#include <vector>

#include "Entity.h"
#include "BlockTextureAtlas.h"

class Chunk;
class Model;
struct Coordinates;

class ChunkLoader
{
	std::map<int, Chunk*> chunks;
	std::vector<Model*> chunkModels;
	BlockTextureAtlas* atlas;
	Entity* observer;

	int HashCoordinates(Coordinates coords);


public:
	ChunkLoader(BlockTextureAtlas* atlas, Entity* observer);

	void Update();

	std::vector<Model*>& GetChunkModels();

	Chunk* GetChunk(Coordinates coords);

	Chunk* GetChunk(int x, int y, int z);

};

