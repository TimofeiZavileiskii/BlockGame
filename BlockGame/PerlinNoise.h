#pragma once

class PerlinNoise
{
	static const int arrSize = 512;
	static const int randomArray[arrSize];

	float fade(float x);

	float linear(float a, float b, float frac);

	float gradient(float x, float y, int hash);


public:
	PerlinNoise() { }

	float Sample(float x, float y);
};

