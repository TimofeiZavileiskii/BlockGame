#include "pch.h"
#include "ChunkThreadPool.h"
#include "ChunkThreadJob.h"
#include "Chunk.h"
#include "ChunkLoader.h"

int ChunkThreadPool::FindThread()
{
	for (int i = 0; i < threadNumber; i++) {
		if (threads[i].available)
			return i;
	}
	return -1;
}

int ChunkThreadPool::CountWorkingThreads()
{
	int total = 0;
	for (int i = 0; i < threadNumber; i++) {
		if (!threads[i].available)
			total++;
	}
	return total;
}

void ChunkThreadPool::StartLoop(int number)
{
	while (!threads[number].terminate) 
	{
		if (threads[number].processedChunk != nullptr) 
		{
			threads[number].processedChunk->GenerateTerrain();
			threads[number].processedChunk->GenerateChunkMesh();
			threads[number].processedChunk = nullptr;
			threads[number].available = true;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

ChunkThreadPool::ChunkThreadPool(ChunkLoader* inChunkLoader)
{
	chunkLoader = inChunkLoader;

	for (int i = 0; i < threadNumber; i++) {
		threads[i] = ChunkThread{std::thread(&ChunkThreadPool::StartLoop, this, i), true, false, nullptr};
	}
}

ChunkThreadPool::~ChunkThreadPool()
{
	for (int i = 0; i < threadNumber; i++) {
		threads[i].terminate = true;
		threads[i].thread.join();
	}
}

bool ChunkThreadPool::AddJob(ChunkThreadJob job)
{
	Chunk* processedChunk = chunkLoader->GetChunk(job.coordinates);
	int availableNum = FindThread();

	if (availableNum != -1)
	{
		threads[availableNum].available = false;
		processedChunk->StartProccessing();
		threads[availableNum].processedChunk = processedChunk;
	}
	else
	{
		return false;
	}
}
