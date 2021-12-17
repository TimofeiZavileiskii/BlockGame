#pragma once

class VBO
{
private:
	int bufferSize;
	unsigned int index;

public:
	VBO(float* input, int vertexNumber, int vertexSize);

	~VBO();

	int GetSize() const;

	int GetIndex() const;

	void Bind() const;
};

