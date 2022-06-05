#include "pch.h"
#include "LehmersRng.h"

LehmersRng::LehmersRng(long seed)
{
	state = seed;
}

long LehmersRng::longRandom()
{
	state *= multeplier;
	return state >> 64;
}

int LehmersRng::intRandom()
{
	state *= multeplier;
	return state >> 96;
}
