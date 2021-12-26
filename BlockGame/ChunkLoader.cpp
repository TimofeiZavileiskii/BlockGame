#include "pch.h"
#include "ChunkLoader.h"
#include "Chunk.h"
#include "Model.h"


int ChunkLoader::HashCoordinates(Coordinates coords)
{
	return coords.x + coords.y * 100 + coords.z * 1000;
}

ChunkLoader::ChunkLoader(BlockTextureAtlas* atlas)
{
	chunks = std::map<int, Chunk*>();
	chunkModels = std::vector<Model*>();
	this->atlas = atlas;
}

void ChunkLoader::Update()
{
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