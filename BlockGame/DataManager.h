#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>

#include "ErrorLoger.h"
#include "Shader.h"
#include "Model.h"


class DataManager
{
private:
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Model*> meshes;

	Shader* ReadShader(std::string shaderName);

	void AddShaders();
	void AddMeshes();

public:
	DataManager();

	Shader* GetShader(std::string name);
	Model* GetMesh(std::string name);
};

