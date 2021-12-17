#pragma once
#include <string>
#include <vector>

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

	void Draw(Camera* camera, std::vector<Model*> chunks);
};

