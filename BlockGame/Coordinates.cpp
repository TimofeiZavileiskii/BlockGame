#include "pch.h"
#include "Coordinates.h"

Coordinates::Coordinates(int inX, int inY, int inZ)
{
	x = inX;
	y = inY;
	z = inZ;
}

Coordinates::Coordinates()
{
	x = 0;
	y = 0;
	z = 0;
}

bool operator<(const Coordinates& lhs, const Coordinates& rhs)
{
	if (lhs.x != rhs.x)
	{
		return lhs.x < rhs.x;
	}
	else if (lhs.y != rhs.y)
	{
		return lhs.y < rhs.y;
	}
	else
	{
		return lhs.z < rhs.z;
	}

}
