#pragma once
#include <string>
#include <vector>
#include "BlockTextureAtlas.h"

class DataManager;
class Camera;
class ErrorLoger;
class Model;

class Renderer
{
private:
	DataManager* dataManager;
	ErrorLoger* errorLoger;

	std::string errorTitle;

	int width;
	int height;

	void ProcessErrors();

public:
	Renderer(int inWidth, int inHeight);

	BlockTextureAtlas* GetAtlas();

	void Draw(Camera* camera, std::vector<Model*> chunks);
};

