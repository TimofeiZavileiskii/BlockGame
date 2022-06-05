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
	
	//std::cout << glm::to_string(camera->GetPosition()) << "\n";

	if (window->GetInput(W))
		camera->Move(window->GetTime());
	if (window->GetInput(S))
		camera->Move(-window->GetTime());
	if (window->GetInput(D))
		camera->Strafe(window->GetTime());
	if (window->GetInput(A))
		camera->Strafe(-window->GetTime());
}

World::World(Window* inWindow, BlockTextureAtlas* atlas, int worldSeed)
{
	window = inWindow;
	this->worldSeed = worldSeed;

	camera = new Camera(glm::vec3(5.0f, 20.0f, 10.0f), glm::vec2(0.0f, 20.0f), 90.0f, window->GetAspectRation());
	chunkLoader = new ChunkLoader(atlas, (Entity*)camera, worldSeed);
	chunkLoader->GenerateChunk(0, 0, 0);


	Update();
}

void World::Update()
{
	//Commented out - Code which prints position of camera in block/chunck coordinates along with block type where camera is
	/*
	glm::vec3 pos = camera->GetPosition();
	
	int x = (int)floor(pos.x / 64.0f);
	int y = (int)floor(pos.y / 64.0f);
	int z = (int)floor(pos.z / 64.0f);
	int locx = 64 * (pos.x < 0) + (int)floor(pos.x) % 64;
	int locy = 64 * (pos.y < 0) + (int)floor(pos.y) % 64;
	int locz = 64 * (pos.z < 0) + (int)floor(pos.z) % 64;
	*/

	passedTime = window->GetTime();
	chunkLoader->Update();

	/*
	Chunk* testChunk = chunkLoader->GetChunk(x, y, z);
	if (testChunk != nullptr) {

		if (testChunk->GetState() >= TERRAIN_GENERATED) {
			Block* block = testChunk->GetBlock(locx, locy, locz);
			if (block != nullptr) {
				std::cout << "Chunk: " << x << ", " << y << ", " << z << " Block: " << locx << ", " << locy << ", " << locz << " Type: " << block->GetType()->texture << "\n";
			}
		}
	}
	*/


	UpdateCamera();
}

Camera* World::GetCamera()
{
	return camera;
}

std::vector<Model*>& World::GetChunkModels()
{
	return chunkLoader->GetChunkModels(camera);
}
