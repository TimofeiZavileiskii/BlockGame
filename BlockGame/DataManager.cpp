#include "pch.h"
#include "DataManager.h"
#include "ImageReader.h"
#include "BlockTextureAtlas.h"
#include "Shader.h"
#include "Model.h"

#include <fstream>
#include <iterator>
#include <filesystem>
#include "ErrorLoger.h"

void DataManager::AddShaders() 
{
    shaders["Test"] = ReadShader("Test");
}

Shader* DataManager::ReadShader(const std::string& shaderName) 
{
    std::ifstream vertShader("Data/Shaders/" + shaderName + "/" + shaderName + ".vert");
    std::ifstream fragShader("Data/Shaders/" + shaderName + "/" + shaderName + ".frag");

    std::string vertText(std::istreambuf_iterator<char>{vertShader}, {});
    std::string fragText(std::istreambuf_iterator<char>{fragShader}, {});

    return new Shader(vertText.c_str(), fragText.c_str());
}

void DataManager::AddTextures() 
{
    ImageReader imReader = ImageReader();
    std::vector<BlockTexture> blockTextures = std::vector<BlockTexture>();

    std::string textureDir = "Data/Textures/";

    for (const auto& entry : std::filesystem::directory_iterator(textureDir)) 
    {
        std::string extension;
        std::string fileName;
        GetFileExtName(entry.path().string(), extension, fileName);

        if (extension == ".tga") 
        {
            ImageData image = imReader.ReadImage(textureDir + fileName + extension);

            textures[fileName.data()] = new Texture(image.imageData, image.width, image.height);
            blockTextures.push_back(BlockTexture(fileName, image));
        }
    }

    atlas = new BlockTextureAtlas(blockTextures);

    for (BlockTexture texture : blockTextures) 
    {
        delete[] texture.texture.imageData;
    }
}

void DataManager::GetFileExtName(const std::string& filePath, std::string& extension, std::string& fileName)
{
    int posLastDot = 0;
    int posLastSlash = 0;
    for (int i = 0; i < filePath.size(); i++)
    {
        if (filePath[i] == '.') 
        {
            posLastDot = i;
        }
        else if (filePath[i] == '/') 
        {
            posLastSlash = i;
        }
    }

    extension = filePath.substr(posLastDot, filePath.size() - posLastDot);
    fileName = filePath.substr(posLastSlash + 1, filePath.size() - posLastSlash - (filePath.size() - posLastDot) - 1);
}

void DataManager::AddMeshes() 
{
    
}

Shader* DataManager::GetShader(const std::string& name)
{
	return shaders[name];
}

Model* DataManager::GetMesh(const std::string& name)
{
	return meshes[name];
}

Texture* DataManager::GetTexture(const std::string& name)
{
    return textures[name];
}

BlockTextureAtlas* DataManager::GetAtlas()
{
    return atlas;
}

DataManager::DataManager() 
{
    shaders = std::map<std::string, Shader*>();
    meshes = std::map<std::string, Model*>();
    textures = std::map<std::string, Texture*>();

    AddMeshes();

    AddShaders();

    AddTextures();
}