#include "pch.h"
#include "Noise.h"

const int Noise::randomArray[] = 
		{ 151, 160, 137, 91, 90, 15,	   //A randomly arranged array of numbers from 0-255 repeated.
		131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
		190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
		88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
		77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
		102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196,
		135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123,
		5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
		223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
		129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
		251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
		49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
		138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,
		151, 160, 137, 91, 90, 15,	   
		131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
		190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
		88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
		77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
		102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196,
		135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123,
		5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
		223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
		129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
		251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
		49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
		138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
	};

float Noise::fade(float x)
{
	return x * x * x * (10 + x * (x * 6 - 15));
}

float Noise::linear(float a, float b, float frac)
{
	return a + frac * (b - a);
}

float Noise::gradient(float x, float y, int hash){
	float output = 0;
	switch (hash & 3)
	{
	case 0:
		output = x + y;
		break;
	case 1:
		output = -x + y;
		break;
	case 2:
		output = -x + -y;
		break;
	case 3:
		output = x - y;
		break;
	}
	return output;
}

Noise::Noise(int worldSeed)
{
	this->worldSeed = worldSeed;
}

float Noise::Sample(float x, float y)
{
	int xOffset = randomArray[worldSeed & 255];
	int yOffset = randomArray[(worldSeed + 1) & 255];

	int squareX = ((int)floor(x) + xOffset) & 255;
	int squareY = ((int)floor(y) + yOffset) & 255;

	float distX = x - floor(x);
	float distY = y - floor(y);

	float u = fade(distX);
	float v = fade(distY);

	int bottomLeft = randomArray[randomArray[squareX] + squareY];
	int topLeft = randomArray[randomArray[squareX] + squareY + 1];
	int bottomRight = randomArray[randomArray[squareX + 1] + squareY];
	int topRight = randomArray[randomArray[squareX + 1] + squareY + 1];
	
	float x1 = linear(gradient(distX, distY, bottomLeft), gradient(distX, distY - 1.0f, topLeft), v);
	float x2 = linear(gradient(distX - 1.0f, distY, bottomRight), gradient(distX - 1.0f, distY - 1.0f, topRight), v);

	return linear(x1, x2, u);
}

float Noise::SampleOctaves(float x, float y, int octaves, float distribution)
{
	float strength = 1.0f;
	float output = 0.0f;
	float frequency = 1.0f;
	float sum = 0.0f;

	for (int i = 0; i < octaves; i++) 
	{
		output += strength * Sample(x * frequency, y * frequency);
		sum += strength;
		frequency = frequency / distribution;
		strength = strength * distribution;
	}

	return output / sum;
}
