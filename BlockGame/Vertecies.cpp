#include "Vertecies.h"

Vertecies::Vertecies(float* data, int count, int size) 
{
	vertecies = data;
	numVertecies = count;
	vertexSize = size;
}

int Vertecies::GetNumber() 
{
	return numVertecies;
}

int Vertecies::GetSize() 
{
	return vertexSize;
}

float* Vertecies::GetData() 
{
	return vertecies;
}