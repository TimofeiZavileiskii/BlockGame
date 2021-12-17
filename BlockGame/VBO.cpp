#include "pch.h"
#include "VBO.h"
#include <glad/glad.h>

VBO::VBO(float* input, int vertexNumber, int vertexSize)
{
	bufferSize = vertexNumber * vertexSize * sizeof(float);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, input, GL_STATIC_DRAW);

}

VBO::~VBO()
{
	glDeleteBuffers(1, &index);
}

int VBO::GetSize() const
{
	return bufferSize;
}

int VBO::GetIndex() const 
{
	return index;
}

void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, index);
}