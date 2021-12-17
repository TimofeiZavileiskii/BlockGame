#pragma once
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"

class vec3;

class Model
{
	glm::vec3 position;
	EBO* indicies;
	VAO* vertexAttributes;

public:
	Model(VAO* vao, EBO* ebo, glm::vec3 inPos);

	~Model();

	void SetPosition(glm::vec3 inPos);

	glm::vec3 GetPosition();

	void Bind();

	void Draw();
};

