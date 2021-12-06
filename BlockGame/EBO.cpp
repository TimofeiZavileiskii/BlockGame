#include "EBO.h"

EBO::EBO(unsigned int* input, int count)
{
	bufferSize = count * sizeof(unsigned int);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, input, GL_STATIC_DRAW);
}

EBO::~EBO() 
{
	glDeleteBuffers(1, &index);
}

int EBO::GetSize() const
{
	return bufferSize;
}

int EBO::GetIndex() const
{
	return index;
}

void EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
}