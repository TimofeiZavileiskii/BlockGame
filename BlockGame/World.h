#pragma once
#include "Camera.h"
#include "Model.h"
#include "BlockTextureAtlas.h"

class Window;
class Chunk;
class ChunkLoader;

class World
{
private:
	const int CHUNK_DIMENSION = 32;
	const int chunkSize = CHUNK_DIMENSION * CHUNK_DIMENSION * CHUNK_DIMENSION;

	Window* window;
	Camera* camera;
	ChunkLoader* chunkLoader;
	int worldSeed;

	double passedTime;

	void UpdateCamera();

public:
	World(Window* inWindow, BlockTextureAtlas* atlas, int worldSeed);

	void Update();

	Camera* GetCamera();

	std::vector<Model*>& GetChunkModels();
};

