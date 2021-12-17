#pragma once
#include "Renderer.h"
#include "Window.h"
#include "World.h"
#include <iostream>

class Game
{
private:
	Window* window;
	World* world;
	Renderer* renderer;

	bool end;
	int fpsCounter;
	double passedTime;

	void Loop() 
	{
		while (!end)
		{
			window->ProcessEvents();
			
			world->Update();
			renderer->Draw(world->GetCamera(), world->GetChunkModels());

			window->Update();

			if (window->GetInput(ESC))
			{
				end = true;
			}

			fpsCounter++;
			passedTime += window->GetTime();
			if (passedTime > 1.0f)
			{
				std::cout << "FPS: " << fpsCounter << "\n";
				passedTime = 0.0f;
				fpsCounter = 0;
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
		world = new World(window);
	}

	void StartLoop() 
	{
		end = false;

		Loop();
	}
};

