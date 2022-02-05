#include "pch.h"
#include "ChunkLoader.h"
#include "Chunk.h"
#include "Model.h"
#include "Camera.h"

int ChunkLoader::HashCoordinates(Coordinates coords)
{
	return coords.x + coords.y * 100 + coords.z * 1000;
}

ChunkLoader::ChunkLoader(BlockTextureAtlas* atlas, Entity* observer)
{
	chunks = std::map<int, Chunk*>();
	chunkModels = std::vector<Model*>();
	this->atlas = atlas;
	this->observer = observer;
}

void ChunkLoader::Update()
{
	const float chunk_dim = 32.0f;
	const int chunkGenRadious = 2;

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

	glm::vec3 dir = camera->GetDirection();
	float aspect = camera->GetAspectRatio();
	float fov = camera->GetFov();

	for (const std::pair<int, Chunk*>& chunkPair : chunks)
	{
		chunkModels.push_back(chunkPair.second->GetChunkModel());
	}

	return chunkModels;
}

Chunk* ChunkLoader::GetChunk(Coordinates coords)
{
	int hash = HashCoordinates(coords);
	
	if (chunks.find(hash) != chunks.end())
	{
		return chunks[hash];
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
	if (output = chunks.find(HashCoordinates(coords)) == chunks.end())
	{
		chunks[HashCoordinates(coords)] = new Chunk(coords, atlas, this);
	}
	return output;
}
