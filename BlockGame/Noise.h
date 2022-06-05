#pragma once

class Noise
{
	//Noise class based on the Perlin Noise algorithm
	static const int arrSize = 512;
	static const int randomArray[arrSize];

	int worldSeed;

	float fade(float x);

	float linear(float a, float b, float frac);

	float gradient(float x, float y, int hash);


public:
	Noise(int worldSeed);

	float Sample(float x, float y);

	float SampleOctaves(float x, float y, int octaves, float distribution);
};

