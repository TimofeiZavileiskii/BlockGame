#pragma once
#include <map>
#include <vector>

class Chunk;
class Model;
struct Coordinates;

class ChunkLoader
{
	std::map<int, Chunk*> chunks;
	std::vector<Model*> chunkModels;


	int HashCoordinates(Coordinates coords);


public:
	ChunkLoader();

	void Update();

	std::vector<Model*>& GetChunkModels();

	Chunk* GetChunk(Coordinates coords);

	Chunk* GetChunk(int x, int y, int z);

};

