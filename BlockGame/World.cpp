#include "pch.h"
#include "World.h"
#include "Window.h"
#include "CubeMeshCreator.h"
#include "ChunkLoader.h"
#include "Chunk.h"


void World::UpdateCamera()
{
	float rotationSpeed = 50.0f * window->GetTime();
	glm::vec2 offset = window->GetCursorOffset();
	camera->Rotate(glm::vec2(offset.x *= rotationSpeed, offset.y *= rotationSpeed));

	if (window->GetInput(W))
		camera->Move(window->GetTime());
	if (window->GetInput(S))
		camera->Move(-window->GetTime());
	if (window->GetInput(D))
		camera->Strafe(window->GetTime());
	if (window->GetInput(A))
		camera->Strafe(-window->GetTime());
}

World::World(Window* inWindow, BlockTextureAtlas* atlas)
{
	window = inWindow;
	camera = new Camera(glm::vec3(0.0f, 20.0f, 10.0f), glm::vec2(0.0f, 20.0f), 70.0f, window->GetAspectRation());
	chunkLoader = new ChunkLoader(atlas);
	chunkLoader->GetChunk(0, 0, 0);
	chunkLoader->GetChunk(1, 0, 0);
	chunkLoader->GetChunk(0, 0, 1);
	chunkLoader->GetChunk(0, 0, -1);
	chunkLoader->GetChunk(-1, 0, 0);
	chunkLoader->GetChunk(1, 0, 1);
	chunkLoader->GetChunk(-1, 0, 1);
	chunkLoader->GetChunk(1, 0, -1);
	chunkLoader->GetChunk(-1, 0, -1);

	Update();
}

void World::Update()
{
	passedTime = window->GetTime();
	chunkLoader->Update();

	UpdateCamera();
}

Camera* World::GetCamera()
{
	return camera;
}

std::vector<Model*>& World::GetChunkModels()
{
	return chunkLoader->GetChunkModels();
}
