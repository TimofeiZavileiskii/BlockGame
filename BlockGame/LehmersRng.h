#pragma once
class LehmersRng
{
	long long state;
	const long long multeplier = 0xda942042e4dd58b5;
public:
	LehmersRng(long seed);

	long longRandom();

	int intRandom();

};

