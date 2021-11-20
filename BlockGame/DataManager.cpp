#include "DataManager.h"

void DataManager::AddShaders() 
{
    const char* sourceVert = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char* sourceFrag = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    shaders["test"] = new Shader(sourceVert, sourceFrag);
}

void DataManager::AddMeshes() 
{
    float vertices[] = {
    2.0f, 5.0f, -15.0f, //Back left bottom
    -1.5f, -2.2f, -2.5f, //Back right bottom
    -3.8f, -2.0f, -12.3f, //Back left top
    2.4f, -0.4f, -3.5f, //Back right top
    -1.7f, 3.0f, -7.5f, //Front left bottom
    1.3f, -2.0f, -2.5f, //Front right bottom
    1.5f, 2.0f, -2.5f, //Front left top
    1.5f, 0.2f, -1.5f, //Front right top
    -1.3f, 1.0f, -1.5f 
    };

    unsigned int indices[] = {
        0, 1, 3, //Back
        1, 2, 3,
        2, 6, 0, //Left
        4, 6, 0,
        6, 3, 2, //Top
        6, 3, 7,
        7, 1, 3, //Right
        7, 1, 5,
        4, 7, 5, //Front
        4, 7, 6,
        0, 5, 1, //Bottom
        0, 5, 4,
    };

    Indicies indicesObj = Indicies(indices, 36);

    Vertecies verts = Vertecies(vertices, 8, 3);

    meshes["test"] = new Mesh(verts, indicesObj);
}

Shader* DataManager::GetShader(std::string name) 
{
	return shaders[name];
}

Mesh* DataManager::GetMesh(std::string name)
{
	return meshes[name];
}

DataManager::DataManager() 
{
    AddMeshes();
    AddShaders();
}