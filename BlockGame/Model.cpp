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
	int size = 0;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	if (indicies->GetSize() * 4 != size && indicies->GetSize() != 0)
		std::cout << "Oh No!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";

	glDrawElements(GL_TRIANGLES, indicies->GetSize(), GL_UNSIGNED_INT, 0);
}
