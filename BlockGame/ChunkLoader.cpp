#include "pch.h"
#include "ChunkLoader.h"
#include "Chunk.h"
#include "Model.h"


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
	{
		for (int ii = -chunkGenRadious; ii < chunkGenRadious + 1; ii++)
		{
			for(int iii = - chunkGenRadious; iii < chunkGenRadious + 1; iii++)
			GetChunk(Coordinates(currentChunkPos.x + i, currentChunkPos.y + iii, currentChunkPos.z + ii));
		}
	}

	for(const auto& [key, value] : chunks) 
	{
		value->Update();
	}
}

std::vector<Model*>& ChunkLoader::GetChunkModels()
{
	chunkModels.clear();

	for (const std::pair<int, Chunk*>& chunkPair : chunks)
	{
		chunkModels.push_back(chunkPair.second->GetChunkModel());
	}

	return chunkModels;
}

Chunk* ChunkLoader::GetChunk(Coordinates coords)
{
	if (chunks.find(HashCoordinates(coords)) == chunks.end()) 
	{
		chunks[HashCoordinates(coords)] = new Chunk(coords, atlas);
	}
	
	return chunks[HashCoordinates(coords)];
}

Chunk* ChunkLoader::GetChunk(int x, int y, int z)
{
	return GetChunk(Coordinates(x, y, z));
}