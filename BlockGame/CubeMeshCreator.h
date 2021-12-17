#pragma once
#include "pch.h"

class CubeMeshCreator
{
	std::vector<float> vertecies;
	std::vector<unsigned int> indicies;

	int totalVertecies;
	int totalIndicies;

	void AddChunkVertex(std::vector<float>& buffer, float x, float y, float z, float u, float v)
	{
		buffer.push_back(x);
		buffer.push_back(y);
		buffer.push_back(z);
		buffer.push_back(u);
		buffer.push_back(v);
	}

	void AddChunkIndex(std::vector<unsigned int>& buffer, unsigned int i1, unsigned int i2, unsigned int i3)
	{
		buffer.push_back(i1);
		buffer.push_back(i2);
		buffer.push_back(i3);
	}


public:
	float* GetVertexData() 
	{
		return vertecies.data();
	}

	unsigned int* GetIndexData() 
	{
		return indicies.data();
	}

	int GetVertexCount() 
	{
		return totalVertecies;
	}

	int GetIndexCount() 
	{
		return totalIndicies;
	}
	
	CubeMeshCreator() 
	{
		std::vector<float> vertecies = std::vector<float>();
		std::vector<unsigned int> indicies = std::vector<unsigned int>();

		int totalVertecies = 0;
		int totalIndicies = 0;
	}

	void AddFrontFace(float x, float y, float z)
	{
		AddChunkVertex(vertecies, x, y, z, 0.0f, 0.0f);
		AddChunkVertex(vertecies, x + 1, y, z, 0.0f, 1.0f);
		AddChunkVertex(vertecies, x + 1, y, z + 1, 1.0f, 1.0f);
		AddChunkVertex(vertecies, x, y, z + 1, 1.0f, 0.0f);

		AddChunkIndex(indicies, totalVertecies, totalVertecies + 1, totalVertecies + 2);
		AddChunkIndex(indicies, totalVertecies, totalVertecies + 3, totalVertecies + 2);
		totalVertecies += 4;
		totalIndicies += 6;
	}

	void AddTopFace(float x, float y, float z)
	{
		AddChunkVertex(vertecies, x, y, z + 1, 0.0f, 0.0f);
		AddChunkVertex(vertecies, x, y + 1, z + 1, 1.0f, 0.0f);
		AddChunkVertex(vertecies, x + 1, y + 1, z + 1, 1.0f, 1.0f);
		AddChunkVertex(vertecies, x + 1, y, z + 1, 0.0f, 1.0f);

		AddChunkIndex(indicies, totalVertecies, totalVertecies + 1, totalVertecies + 2);
		AddChunkIndex(indicies, totalVertecies, totalVertecies + 3, totalVertecies + 2);
		totalVertecies += 4;
		totalIndicies += 6;
	}

	void AddLeftFace(float x, float y, float z)
	{

		AddChunkVertex(vertecies, x, y, z, 0.0f, 0.0f);
		AddChunkVertex(vertecies, x, y, z + 1, 1.0f, 0.0f);
		AddChunkVertex(vertecies, x, y + 1, z + 1, 1.0f, 1.0f);
		AddChunkVertex(vertecies, x, y + 1, z, 0.0f, 1.0f);

		AddChunkIndex(indicies, totalVertecies, totalVertecies + 1, totalVertecies + 2);
		AddChunkIndex(indicies, totalVertecies, totalVertecies + 3, totalVertecies + 2);
		totalVertecies += 4;
		totalIndicies += 6;
	}

	void AddRightFace(float x, float y, float z)
	{
		AddChunkVertex(vertecies, x + 1, y, z, 0.0f, 0.0f);
		AddChunkVertex(vertecies, x + 1, y, z + 1, 1.0f, 0.0f);
		AddChunkVertex(vertecies, x + 1, y + 1, z + 1, 1.0f, 1.0f);
		AddChunkVertex(vertecies, x + 1, y + 1, z, 0.0f, 1.0f);

		AddChunkIndex(indicies, totalVertecies, totalVertecies + 1, totalVertecies + 2);
		AddChunkIndex(indicies, totalVertecies, totalVertecies + 3, totalVertecies + 2);
		totalVertecies += 4;
		totalIndicies += 6;
	}

	void AddBottomFace(float x, float y, float z)
	{
		AddChunkVertex(vertecies, x, y, z, 0.0f, 0.0f);
		AddChunkVertex(vertecies, x, y + 1, z, 1.0f, 0.0f);
		AddChunkVertex(vertecies, x + 1, y + 1, z, 1.0f, 1.0f);
		AddChunkVertex(vertecies, x + 1, y, z, 0.0f, 1.0f);

		AddChunkIndex(indicies, totalVertecies, totalVertecies + 1, totalVertecies + 2);
		AddChunkIndex(indicies, totalVertecies, totalVertecies + 3, totalVertecies + 2);
		totalVertecies += 4;
		totalIndicies += 6;
	}

	void AddBackFace(float x, float y, float z)
	{
		AddChunkVertex(vertecies, x + 1, y + 1, z, 0.0f, 0.0f);
		AddChunkVertex(vertecies, x + 1, y + 1, z + 1, 1.0f, 0.0f);
		AddChunkVertex(vertecies, x, y + 1, z + 1, 1.0f, 1.0f);
		AddChunkVertex(vertecies, x, y + 1, z, 0.0f, 1.0f);

		AddChunkIndex(indicies, totalVertecies, totalVertecies + 1, totalVertecies + 2);
		AddChunkIndex(indicies, totalVertecies, totalVertecies + 3, totalVertecies + 2);
		totalVertecies += 4;
		totalIndicies += 6;
	}
	
};

