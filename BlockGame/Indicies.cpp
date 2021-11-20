#include "Indicies.h"

Indicies::Indicies(unsigned int* data, int count)
{
	indicies = data;
	number = count;
}

int Indicies::GetNumber() {
	return number;
}

unsigned int* Indicies::GetData() {
	return indicies;
}