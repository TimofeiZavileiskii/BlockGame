#pragma once
#include "Entity.h"
#include "Camera.h"
#include "Model.h"
#include "Chunk.h"

class Window;

class World
{
private:
	const int CHUNK_DIMENSION = 32;
	const int chunkSize = CHUNK_DIMENSION * CHUNK_DIMENSION * CHUNK_DIMENSION;

	Window* window;
	Camera* camera;
	Chunk* chunk;

	std::vector<Model*> chunkModels;

	double passedTime;

	void UpdateCamera();

public:
	World(Window* inWindow);

	void Update();

	Camera* GetCamera();

	std::vector<Model*>& GetChunkModels();
};

