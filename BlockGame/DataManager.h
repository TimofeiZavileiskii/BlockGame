#pragma once
#include "iostream"
#include "Shader.h"
#include "Mesh.h"
#include <map>

class DataManager
{
private:
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Mesh*> meshes;

	void AddShaders();
	void AddMeshes();

public:
	DataManager();

	Shader* GetShader(std::string name);
	Mesh* GetMesh(std::string name);
};

