#pragma once

class EBO
{
	int count;
	unsigned int index;

public:
	EBO(unsigned int* indicies, int count);

	~EBO();

	int GetSize() const;

	int GetIndex() const;

	void Bind() const;
};

