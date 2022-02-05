#pragma once
#include <map>
#include <vector>

#include "Entity.h"
#include "BlockTextureAtlas.h"

class Chunk;
class Model;
struct Coordinates;
class Camera;

class ChunkLoader
{
	std::map<Coordinates, Chunk*> chunks;
	std::vector<Model*> chunkModels;
	BlockTextureAtlas* atlas;
	Entity* observer;



public:
	ChunkLoader(BlockTextureAtlas* atlas, Entity* observer);

	void Update();

	std::vector<Model*>& GetChunkModels(Camera* camera);

	Chunk* GetChunk(Coordinates coords);

	Chunk* GetChunk(int x, int y, int z);

	bool GenerateChunk(Coordinates coords);

	bool GenerateChunk(int x, int y, int z);
};

