#pragma once
#include <glad/glad.h>
#include "DataManager.h"
#include "ErrorLoger.h"

class Renderer
{
private:
	DataManager* dataManager;
	ErrorLoger* errorLoger;

	std::string errorTitle;

	void ProcessErrors();

public:
	Renderer(int width, int height);

	void Draw();
};

