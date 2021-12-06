#include "Model.h"

Model::Model(VAO* vao, EBO* ebo)
{
	vertexAttributes = vao;
	indicies = ebo;
}

void Model::Bind()
{
	indicies->Bind();
	vertexAttributes->Bind();
}
