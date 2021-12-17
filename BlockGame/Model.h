#pragma once
#include "EBO.h"
#include "VAO.h"
#include "Shader.h"
#include "Texture.h"

class Model
{
	EBO* indicies;
	VAO* vertexAttributes;

public:
	Model(VAO* vao, EBO* ebo);

	~Model();

	void Bind();

	void Draw();
};

