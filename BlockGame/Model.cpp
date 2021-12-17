#include "pch.h"
#include "Model.h"

Model::Model(VAO* vao, EBO* ebo)
{
	vertexAttributes = vao;
	indicies = ebo;
}

Model::~Model() 
{
	delete vertexAttributes;
	delete indicies;
}

void Model::Bind()
{
	indicies->Bind();
	vertexAttributes->Bind();
}

void Model::Draw()
{
	glDrawElements(GL_TRIANGLES, indicies->GetSize(), GL_UNSIGNED_INT, 0);
}
