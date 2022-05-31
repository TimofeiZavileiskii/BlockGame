#pragma once
struct Coordinates
{
	int x;
	int y;
	int z;

	friend bool operator<(const Coordinates& lhs, const Coordinates& rhs);

	Coordinates(int inX, int inY, int inZ);

	Coordinates();
};

