#pragma once
#include <glad/glad.h>

class EBO
{
	int bufferSize;
	unsigned int index;

public:
	EBO(unsigned int* indicies, int count);

	~EBO();

	int GetSize() const;

	int GetIndex() const;

	void Bind() const;
};

