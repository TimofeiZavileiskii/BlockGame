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
	std::map<std::string, Texture*> textures;

	Shader* ReadShader(const std::string& shaderName);

	void AddShaders();
	void AddMeshes();
	void AddTextures();

public:
	DataManager();

	Shader* GetShader(const std::string& name);
	Model* GetMesh(const std::string& name);
	Texture* GetTexture(const std::string& name);
};

