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
			if(threads[number].currentJob == GENERATE_TERRAIN)
			{
				threads[number].processedChunk->GenerateTerrain();
			}
			else if (threads[number].currentJob == GENERATE_MODEL) 
			{
				threads[number].processedChunk->GenerateChunkMesh();
			}

			threads[number].processedChunk = nullptr;
			threads[number].currentJob = NONE;
			threads[number].available = true;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

ChunkThreadPool::ChunkThreadPool(ChunkLoader* inChunkLoader)
{
	chunkLoader = inChunkLoader;

	for (int i = 0; i < threadNumber; i++) {
		threads[i] = ChunkThread{std::thread(&ChunkThreadPool::StartLoop, this, i), true, false, NONE, nullptr};
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
		threads[availableNum].currentJob = job.job;
		if (job.job == GENERATE_TERRAIN) {
			processedChunk->StartProccessingTerrain();
		}
		else if (job.job == GENERATE_MODEL) {
			processedChunk->StartProccessingModel();
		}
		threads[availableNum].processedChunk = processedChunk;
		return true;
	}
	else
	{
		return false;
	}
}
