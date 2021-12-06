#pragma once
#include <glad/glad.h>
#include <vector>

#include "VBO.h"

enum DataType
{
	FLOAT, INT, UNSIGNED_INT,
	DOUBLE,
};

struct VaoLayoutElement 
{

public:
	DataType type;
	int count;
	bool normalised;

	int GetTypeSize() const
	{
		int output = -1;
		switch (type)
		{
		case FLOAT:
			output = sizeof(float);
			break;
		case INT:
			output = sizeof(int);
			break;
		case UNSIGNED_INT:
			output = sizeof(unsigned int);
			break;
		case DOUBLE:
			output = sizeof(double);
			break;
		}

		return output;
	}

	unsigned int GetGLType() const
	{
		int output = -1;
		switch (type)
		{
		case FLOAT:
			output = GL_FLOAT;
			break;
		case INT:
			output = GL_INT;
			break;
		case UNSIGNED_INT:
			output = GL_UNSIGNED_INT;
			break;
		case DOUBLE:
			output = GL_DOUBLE;
			break;
		}

		return output;
	}

	int GetTotalSize() const
	{
		return GetTypeSize() * count;
	}

	VaoLayoutElement(DataType inType, int inCount, bool inNormalised)
	{
		type = inType;
		count = inCount;
		normalised = inNormalised;
	}
};


class VAO
{
private:
	VBO* vertexBuffer;
	
	unsigned int index;
	std::vector<VaoLayoutElement> layout;

public:
	VAO(VBO* vbo, std::vector<VaoLayoutElement> inLayout);
	
	~VAO();

	unsigned int GetIndex() const;

	void Bind() const;
};

