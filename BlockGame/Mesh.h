#pragma once
#include <glad/glad.h>
#include <glfw3.h>
#include "Vertecies.h"
#include "Indicies.h"

class Mesh
{
private:
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;
	
	int* vertecies;
	int vertexSize;
	int numVertecies;

public:
	Mesh(Vertecies vertecies, Indicies indicies);
	
	void Bind();

};

