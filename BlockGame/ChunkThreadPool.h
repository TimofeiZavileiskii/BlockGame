#pragma once
#include <thread>

struct ChunkThreadJob;
class ChunkLoader;
class Chunk;

struct ChunkThread 
{
	std::thread thread;
	bool available;
	bool terminate;
	Chunk* processedChunk;
};

class ChunkThreadPool
{
	static const int threadNumber = 16;

	ChunkThread threads[threadNumber];

	ChunkLoader* chunkLoader;

	int FindThread();

	void StartLoop(int number);

public:
	ChunkThreadPool(ChunkLoader* inChunkLoader);

	~ChunkThreadPool();

	int CountWorkingThreads();

	bool AddJob(ChunkThreadJob job);

	
};

