#pragma once
#include "EBO.h"
#include "VAO.h"

class Model
{
	EBO* indicies;
	VAO* vertexAttributes;

public:
	Model(VAO* vao, EBO* ebo);

	void Bind();

};

