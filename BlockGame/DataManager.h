#pragma once
class map;
class BlockTextureAtlas;
class Model;
class Shader;
class Texture;

class DataManager
{
private:
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Model*> meshes;
	std::map<std::string, Texture*> textures;
	BlockTextureAtlas* atlas;

	Shader* ReadShader(const std::string& shaderName);

	void AddShaders();
	void AddMeshes();
	void AddTextures();
	void GetFileExtName(const std::string& filePath, std::string& extension, std::string& fileName);

public:
	DataManager();

	Shader* GetShader(const std::string& name);
	Model* GetMesh(const std::string& name);
	Texture* GetTexture(const std::string& name);
	BlockTextureAtlas* GetAtlas();
};

