#pragma once
#include "pch.h"
#include "BlockTextureAtlas.h"

class CubeMeshCreator
{
	std::vector<float> vertecies;
	std::vector<unsigned int> indicies;

	BlockTextureAtlas* atlas;

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
	
	CubeMeshCreator(BlockTextureAtlas* atlas) 
	{
		std::vector<float> vertecies = std::vector<float>();
		std::vector<unsigned int> indicies = std::vector<unsigned int>();

		this->atlas = atlas;

		totalVertecies = 0;
		totalIndicies = 0;
	}

	void AddChunkIndexFront(std::vector<unsigned int>& buffer, int totalVertecies)
	{

		AddChunkIndex(indicies, totalVertecies, totalVertecies + 1, totalVertecies + 2);
		AddChunkIndex(indicies, totalVertecies, totalVertecies + 2, totalVertecies + 3);
	}

	void AddChunkIndexBack(std::vector<unsigned int>& buffer, int totalVertecies)
	{

		AddChunkIndex(indicies, totalVertecies, totalVertecies + 2, totalVertecies + 1);
		AddChunkIndex(indicies, totalVertecies, totalVertecies + 3, totalVertecies + 2);
	}

	glm::vec2 TexCoordinates(std::string& name, TextureCorners corners) 
	{
		return atlas->GetTextureCoords(name, corners);
	}

	void AddFrontFace(float x, float y, float z, std::string& name)
	{
		AddChunkVertex(vertecies, x, y, z, TexCoordinates(name, LEFTDOWN).x, TexCoordinates(name, LEFTDOWN).y);
		AddChunkVertex(vertecies, x + 1, y, z, TexCoordinates(name, RIGHTDOWN).x, TexCoordinates(name, RIGHTDOWN).y);
		AddChunkVertex(vertecies, x + 1, y + 1, z, TexCoordinates(name, RIGHTUP).x, TexCoordinates(name, RIGHTUP).y);
		AddChunkVertex(vertecies, x, y + 1, z, TexCoordinates(name, LEFTUP).x, TexCoordinates(name, LEFTUP).y);

		AddChunkIndexBack(indicies, totalVertecies);

		totalVertecies += 4;
		totalIndicies += 6;
	}

	void AddBackFace(float x, float y, float z, std::string& name)
	{
		AddChunkVertex(vertecies, x, y, z + 1, TexCoordinates(name, LEFTDOWN).x, TexCoordinates(name, LEFTDOWN).y);
		AddChunkVertex(vertecies, x + 1, y, z + 1, TexCoordinates(name, RIGHTDOWN).x, TexCoordinates(name, RIGHTDOWN).y);
		AddChunkVertex(vertecies, x + 1, y + 1, z + 1, TexCoordinates(name, RIGHTUP).x, TexCoordinates(name, RIGHTUP).y);
		AddChunkVertex(vertecies, x, y + 1, z + 1, TexCoordinates(name, LEFTUP).x, TexCoordinates(name, LEFTUP).y);

		AddChunkIndexFront(indicies, totalVertecies);

		totalVertecies += 4;
		totalIndicies += 6;
	}

	void AddTopFace(float x, float y, float z, std::string& name)
	{
		AddChunkVertex(vertecies, x, y + 1, z, TexCoordinates(name, LEFTDOWN).x, TexCoordinates(name, LEFTDOWN).y);
		AddChunkVertex(vertecies, x + 1, y + 1, z, TexCoordinates(name, RIGHTDOWN).x, TexCoordinates(name, RIGHTDOWN).y);
		AddChunkVertex(vertecies, x + 1, y + 1, z + 1, TexCoordinates(name, RIGHTUP).x, TexCoordinates(name, RIGHTUP).y);
		AddChunkVertex(vertecies, x, y + 1, z + 1, TexCoordinates(name, LEFTUP).x, TexCoordinates(name, LEFTUP).y);

		AddChunkIndexBack(indicies, totalVertecies);
		totalVertecies += 4;
		totalIndicies += 6;
	}

	void AddBottomFace(float x, float y, float z, std::string& name)
	{
		AddChunkVertex(vertecies, x, y, z, TexCoordinates(name, LEFTDOWN).x, TexCoordinates(name, LEFTDOWN).y);
		AddChunkVertex(vertecies, x + 1, y, z, TexCoordinates(name, RIGHTDOWN).x, TexCoordinates(name, RIGHTDOWN).y);
		AddChunkVertex(vertecies, x + 1, y, z + 1, TexCoordinates(name, RIGHTUP).x, TexCoordinates(name, RIGHTUP).y);
		AddChunkVertex(vertecies, x, y, z + 1, TexCoordinates(name, LEFTUP).x, TexCoordinates(name, LEFTUP).y);

		AddChunkIndexFront(indicies, totalVertecies);

		totalVertecies += 4;
		totalIndicies += 6;
	}

	void AddLeftFace(float x, float y, float z, std::string& name)
	{

		AddChunkVertex(vertecies, x, y, z, TexCoordinates(name, LEFTDOWN).x, TexCoordinates(name, LEFTDOWN).y);
		AddChunkVertex(vertecies, x, y + 1, z, TexCoordinates(name, RIGHTDOWN).x, TexCoordinates(name, RIGHTDOWN).y);
		AddChunkVertex(vertecies, x, y + 1, z + 1, TexCoordinates(name, RIGHTUP).x, TexCoordinates(name, RIGHTUP).y);
		AddChunkVertex(vertecies, x, y, z + 1, TexCoordinates(name, LEFTUP).x, TexCoordinates(name, LEFTUP).y);

		AddChunkIndexBack(indicies, totalVertecies);

		totalVertecies += 4;
		totalIndicies += 6;
	}


	void AddRightFace(float x, float y, float z, std::string& name)
	{
		AddChunkVertex(vertecies, x + 1, y, z, TexCoordinates(name, LEFTDOWN).x, TexCoordinates(name, LEFTDOWN).y);
		AddChunkVertex(vertecies, x + 1, y + 1, z, TexCoordinates(name, RIGHTDOWN).x, TexCoordinates(name, RIGHTDOWN).y);
		AddChunkVertex(vertecies, x + 1, y + 1, z + 1, TexCoordinates(name, RIGHTUP).x, TexCoordinates(name, RIGHTUP).y);
		AddChunkVertex(vertecies, x + 1, y, z + 1, TexCoordinates(name, LEFTUP).x, TexCoordinates(name, LEFTUP).y);

		AddChunkIndexFront(indicies, totalVertecies);

		totalVertecies += 4;
		totalIndicies += 6;
	}


	
};

