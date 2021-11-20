#pragma once


class Vertecies
{
private:
	float* vertecies;
	int numVertecies;
	int vertexSize;

public:
	Vertecies(float* input, int number, int size);

	int GetNumber();

	int GetSize();

	float* GetData();
};

