#include "VAO.h"

VAO::VAO(VBO* vbo, std::vector<VaoLayoutElement> inLayout)
{
	vertexBuffer = vbo;
	layout = inLayout;

	glGenVertexArrays(1, &index);
	Bind();

	vbo->Bind();

	int totalSize = 0;
	for (int i = 0; i < inLayout.size(); i++)
	{
		totalSize += inLayout[i].GetTotalSize();
	}

	int currOffset = 0;
	for (int i = 0; i < inLayout.size(); i++)
	{
		VaoLayoutElement& element = inLayout[i];
		glVertexAttribPointer(i, element.count, element.GetGLType(), element.normalised, totalSize, (void*)currOffset);
		glEnableVertexAttribArray(i);

		currOffset += element.GetTotalSize();
	}
}

VAO::~VAO() 
{
	glDeleteVertexArrays(1, &index);
}

unsigned int VAO::GetIndex() const
{
	return index;
}

void VAO::Bind() const
{
	glBindVertexArray(index);
}