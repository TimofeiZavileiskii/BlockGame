#include "pch.h"
#include "ChunkJob.h"

ChunkJob::ChunkJob(ChunkJobType inType, int inPriority, Coordinates inChunksCoordinates) 
{
	type = inType;
	priority = inPriority;
	chunksCoordinates = inChunksCoordinates;
}

ChunkJobType ChunkJob::GetType()
{
	return type;
}

Coordinates ChunkJob::GetCoordinates()
{
	return chunksCoordinates;
}

bool operator<(const ChunkJob& lhs, const ChunkJob& rhs)
{
	return lhs.priority < rhs.priority;
}
