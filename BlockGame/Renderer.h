#pragma once
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw3.h>

#include "DataManager.h"
#include "ErrorLoger.h"
#include "Camera.h"

class Renderer
{
private:
	DataManager* dataManager;
	ErrorLoger* errorLoger;

	std::string errorTitle;

	int width;
	int height;

	void ProcessErrors();

	void ProcessErrors(std::string error);

public:
	Renderer(int inWidth, int inHeight);

	void Draw(Camera* camera);
};

