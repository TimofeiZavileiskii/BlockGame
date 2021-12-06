#include "DataManager.h"

void DataManager::AddShaders() 
{
    shaders["Test"] = ReadShader("Test");
}

Shader* DataManager::ReadShader(std::string shaderName) 
{
    std::ifstream vertShader("Data/Shaders/" + shaderName + "/" + shaderName + ".vert");
    std::ifstream fragShader("Data/Shaders/" + shaderName + "/" + shaderName + ".frag");

    std::string vertText(std::istreambuf_iterator<char>{vertShader}, {});
    std::string fragText(std::istreambuf_iterator<char>{fragShader}, {});

    return new Shader(vertText.c_str(), fragText.c_str());
}

void DataManager::AddMeshes() 
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
                            
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
                            
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
                            
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
                            
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
                            
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35,
    };

    EBO* indicesObj = new EBO(indices, 36);

    VBO* verts = new VBO(vertices, 36, 3);

    std::vector<VaoLayoutElement> layout = std::vector<VaoLayoutElement>();
    layout.push_back(VaoLayoutElement(FLOAT, 3, false));
    meshes["Test"] = new Model(new VAO(verts, layout), indicesObj);
}

Shader* DataManager::GetShader(std::string name) 
{
	return shaders[name];
}

Model* DataManager::GetMesh(std::string name)
{
	return meshes[name];
}

DataManager::DataManager() 
{
    AddMeshes();

    AddShaders();
}