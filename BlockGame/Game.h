#pragma once

class Window;
class World;
class Renderer;

class Game
{
private:
	Window* window;
	World* world;
	Renderer* renderer;

	bool end;
	int fpsCounter;
	double passedTime;

	void Loop();

public:
	Game();

	void StartLoop();
};

