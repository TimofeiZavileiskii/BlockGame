#include "pch.h"
#include "Model.h"
#include <iostream>

Model::Model(VAO* vao, EBO* ebo, glm::vec3 inPos)
{
	position = inPos;
	vertexAttributes = vao;
	indicies = ebo;

	
}

Model::~Model() 
{
	delete vertexAttributes;
	delete indicies;
}

void Model::SetPosition(glm::vec3 inPos)
{
	position = inPos;
}

glm::vec3 Model::GetPosition()
{
	return position;
}

void Model::Bind()
{
	vertexAttributes->Bind();
	indicies->Bind();
}

void Model::Draw()
{
	glDrawElements(GL_TRIANGLES, indicies->GetSize(), GL_UNSIGNED_INT, 0);
}
