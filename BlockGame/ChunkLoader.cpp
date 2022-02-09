#include "pch.h"
#include "ChunkLoader.h"
#include "Chunk.h"
#include "Model.h"
#include "Camera.h"

#include <iostream>

bool ChunkLoader::ChunkExists(Coordinates coords)
{
	return chunks.find(coords) != chunks.end();
}

bool ChunkLoader::ChunkExists(int x, int y, int z)
{
	ChunkExists(Coordinates(x, y, z));
}

ChunkLoader::ChunkLoader(BlockTextureAtlas* atlas, Entity* observer)
{
	chunks = std::map<Coordinates, Chunk*>();
	chunkModels = std::vector<Model*>();
	this->atlas = atlas;
	this->observer = observer;
}

void ChunkLoader::Update()
{
	const float chunk_dim = 32.0f;
	const int chunkGenRadious = 12;

	glm::vec3 position = observer->GetPosition();
	Coordinates currentChunkPos = Coordinates((int)floor(position.x / chunk_dim), (int)floor(position.y / chunk_dim), (int)floor(position.z / chunk_dim));
	
	for (int i = -chunkGenRadious; i < chunkGenRadious + 1; i++)
		for (int ii = -chunkGenRadious; ii < chunkGenRadious + 1; ii++)
			for (int iii = -chunkGenRadious; iii < chunkGenRadious + 1; iii++)
				GenerateChunk(Coordinates(currentChunkPos.x + i, currentChunkPos.y + iii, currentChunkPos.z + ii));

	for(const auto& [key, value] : chunks) 
	{
		value->Update();
	}
}

std::vector<Model*>& ChunkLoader::GetChunkModels(Camera* camera)
{
	chunkModels.clear();
	
	const float degreeToRadians = 3.1415926f / 180.0f;

	glm::vec3 pos = camera->GetPosition();
	glm::vec3 dir = camera->GetDirection();
	float aspect = camera->GetAspectRatio();
	float fov = camera->GetFov();
	float distance = camera->GetViewDistance();
	float near = camera->GetNearDistance();

	glm::vec3 nearCenter = pos + dir * near;
	glm::vec3 farCenter = pos + dir * distance;

	float nearHeight = 2 * tan(fov * degreeToRadians / 2) * near;
	float farHeight = 2 * tan(fov * degreeToRadians / 2) * distance;
	float nearWidth = nearHeight * aspect;
	float farWidth = farHeight * aspect;

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 camRight = glm::normalize(glm::cross(dir, up));
	glm::vec3 camUp = glm::normalize(glm::cross(dir, camRight));

	glm::vec3 farTopLeft = farCenter + camUp * (farHeight * 0.5f) - camRight * (farWidth * 0.5f);
	glm::vec3 farTopRight = farCenter + camUp * (farHeight * 0.5f) + camRight * (farWidth * 0.5f);
	glm::vec3 farBottomLeft = farCenter - camUp * (farHeight * 0.5f) - camRight * (farWidth * 0.5f);
	glm::vec3 farBottomRight = farCenter - camUp * (farHeight * 0.5f) + camRight * (farWidth * 0.5f);

	glm::vec3 nearTopLeft = nearCenter + camUp * (nearHeight * 0.5f) - camRight * (nearWidth * 0.5f);
	glm::vec3 nearTopRight = nearCenter + camUp * (nearHeight * 0.5f) + camRight *(nearWidth * 0.5f);
	glm::vec3 nearBottomLeft = nearCenter - camUp * (nearHeight * 0.5f) - camRight * (nearWidth * 0.5f);
	glm::vec3 nearBottomRight = nearCenter - camUp * (nearHeight * 0.5f) + camRight * (nearWidth * 0.5f);
	
	//First find the rectanle of possible chunks	
	float mostLeft = std::min({ nearTopLeft.x, farTopLeft.x, nearTopRight.x, farTopRight.x, 
		nearBottomLeft.x, farBottomLeft.x, nearBottomRight.x, farBottomRight.x, }) / 32.0f;
	float mostRight = std::max({ nearTopLeft.x, farTopLeft.x, nearTopRight.x, farTopRight.x,
		nearBottomLeft.x, farBottomLeft.x, nearBottomRight.x, farBottomRight.x, }) / 32.0f;
	float mostHigh = std::max({ nearTopLeft.y, farTopLeft.y, nearTopRight.y, farTopRight.y,
		nearBottomLeft.y, farBottomLeft.y, nearBottomRight.y, farBottomRight.y, }) / 32.0f;
	float mostLow = std::min({ nearTopLeft.y, farTopLeft.y, nearTopRight.y, farTopRight.y,
		nearBottomLeft.y, farBottomLeft.y, nearBottomRight.y, farBottomRight.y, }) / 32.0f;
	float mostFar = std::max({ nearTopLeft.z, farTopLeft.z, nearTopRight.z, farTopRight.z,
		nearBottomLeft.z, farBottomLeft.z, nearBottomRight.z, farBottomRight.z, }) / 32.0f;
	float mostClose = std::min({ nearTopLeft.z, farTopLeft.z, nearTopRight.z, farTopRight.z,
		nearBottomLeft.z, farBottomLeft.z, nearBottomRight.z, farBottomRight.z, }) / 32.0f;
	
	for (int i = (int)floor(mostLeft); i < (int)ceil(mostRight); i++) 
	{
		for (int ii = (int)floor(mostLow); ii < (int)ceil(mostHigh); ii++)
		{
			for (int iii = (int)floor(mostClose); iii < (int)ceil(mostFar); iii++)
			{
				if(ChunkExists(Coordinates(i, ii, iii)))
					chunkModels.push_back(GetChunk(i, ii, iii)->GetChunkModel());
			}
		}
	}
	
	/*for (const std::pair<Coordinates, Chunk*>& chunkPair : chunks)
	{
		chunkModels.push_back(chunkPair.second->GetChunkModel());
	}*/

	return chunkModels;
}

Chunk* ChunkLoader::GetChunk(Coordinates coords)
{	
	if (chunks.find(coords) != chunks.end())
	{
		return chunks[coords];
	}
	else
	{
		return nullptr;
	}
}

Chunk* ChunkLoader::GetChunk(int x, int y, int z)
{
	return GetChunk(Coordinates(x, y, z));
}

bool ChunkLoader::GenerateChunk(int x, int y, int z)
{
	return GenerateChunk(Coordinates(x, y, z));
}

bool ChunkLoader::GenerateChunk(Coordinates coords)
{
	bool output = false;
	if (output = chunks.find(coords) == chunks.end())
	{
		chunks[coords] = new Chunk(coords, atlas, this);
	}
	return output;
}
