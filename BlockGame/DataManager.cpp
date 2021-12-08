#include "DataManager.h"

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
    unsigned char text[] =
    {
        144,  80, 200, 255, 144, 80,  200, 255, 144, 80,  200, 255, 144, 80,  200, 255,
        144, 80,  200, 255,   0,   0,   0, 255,   0,   0,   0, 255, 144, 80,  200, 255,
        144, 80,  200, 255,   0,   0,   0, 255,   0,   0,   0, 255, 144, 80,  200, 255,
        144, 80,  200, 255, 144, 80,  200, 255, 144, 80,  200, 255, 144, 80,  200, 255,
    };

    textures["Test"] = new Texture(text, 4, 4);
}

void DataManager::AddMeshes() 
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

    VBO* verts = new VBO(vertices, 36, 5);

    std::vector<VaoLayoutElement> layout = std::vector<VaoLayoutElement>();
    layout.push_back(VaoLayoutElement(FLOAT, 3, false));
    layout.push_back(VaoLayoutElement(FLOAT, 2, false));
    meshes["Test"] = new Model(new VAO(verts, layout), indicesObj);
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

DataManager::DataManager() 
{
    shaders = std::map<std::string, Shader*>();
    meshes = std::map<std::string, Model*>();
    textures = std::map<std::string, Texture*>();

    AddMeshes();

    AddShaders();

    AddTextures();
}