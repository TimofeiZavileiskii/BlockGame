#pragma once
class Indicies
{
	unsigned int* indicies;
	int number;

public:
	Indicies(unsigned int* indicies, int number);

	int GetNumber();

	unsigned int* GetData();
};

