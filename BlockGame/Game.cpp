#include "pch.h"
#include "Game.h"
#include "Renderer.h"
#include "Window.h"
#include "World.h"


void Game::Loop()
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

Game::Game()
{
	end = false;
	fpsCounter = 0;
	passedTime = 0.0f;
	int width = 1000;
	int height = 850;

	int seed = 142213;

	window = new Window(width, height, "Game");
	renderer = new Renderer(width, height);
	world = new World(window, renderer->GetAtlas(), seed);
}

void Game::StartLoop()
{
	end = false;

	Loop();
}