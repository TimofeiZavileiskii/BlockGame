#include "pch.h"
#include "World.h"
#include "Window.h"
#include "CubeMeshCreator.h"
#include <random>

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

World::World(Window* inWindow)
{
	window = inWindow;
	camera = new Camera(glm::vec3(0.0f, 40.0f, 20.0f), glm::vec2(0.0f, 0.0f), 70.0f, window->GetAspectRation());
	chunk = new Chunk();

	chunkModels = std::vector<Model*>();
	chunkModels.push_back(chunk->GetChunkModel());

	Update();
}

void World::Update()
{
	passedTime = window->GetTime();
	chunk->Update();

	UpdateCamera();
}

Camera* World::GetCamera()
{
	return camera;
}

std::vector<Model*>& World::GetChunkModels()
{
	return chunkModels;
}
