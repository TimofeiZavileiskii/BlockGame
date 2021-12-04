#pragma once
#include "Window.h"
#include "Entity.h"
#include "Camera.h"

class World
{
private:
	Window* window;
	Camera* camera;
	double passedTime;


	void UpdateCamera();

public:
	World(Window* inWindow);

	void Update();

	Camera* GetCamera();
};

