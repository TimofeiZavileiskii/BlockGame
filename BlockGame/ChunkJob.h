#pragma once
#include "Coordinates.h"

enum ChunkJobType
{
	GENERATE_CHUNK,
	MESH_CHUNK,
	CHANGE_CHUNK,
};

class ChunkJob
{
	int priority;

	ChunkJobType type;
	Coordinates chunksCoordinates;

public:
	friend bool operator<(const ChunkJob& lhs, const ChunkJob& rhs);

	ChunkJob(ChunkJobType type, int priority, Coordinates chunksCoordinates);

	ChunkJobType GetType();

	Coordinates GetCoordinates();

};

