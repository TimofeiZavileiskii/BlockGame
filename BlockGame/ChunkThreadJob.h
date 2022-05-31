#pragma once
#include "Coordinates.h"

enum ChunkJob
{
	GENERATE_TERRAIN,
	GENERATE_MODEL
};

struct ChunkThreadJob
{
	Coordinates coordinates = Coordinates(0,0,0);
	ChunkJob job;

	ChunkThreadJob(Coordinates inCoordinates, ChunkJob inJob)
	{
		coordinates = inCoordinates;
		job = inJob;
	}
};

