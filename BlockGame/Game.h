#pragma once
#include "Renderer.h"
#include "Window.h"
#include "World.h"


class Game
{
private:
	Window* window;
	World* world;
	Renderer* renderer;

	bool end;

	void Loop() 
	{
		while (!end)
		{
			window->ProcessInputs();
			
			world->Update();
			renderer->Draw();

			window->Update();

			if (window->GetInput(ESC)) {
				end = true;
			}
		}
	}

public:
	Game() 
	{
		end = false;
		int width = 1000;
		int height = 850;

		window = new Window(width, height, "Game");
		renderer = new Renderer(width, height);
		world = new World();
	}

	void StartLoop() 
	{
		end = false;

		Loop();
	}
};

