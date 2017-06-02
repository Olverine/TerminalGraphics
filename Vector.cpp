#include "Vector.h"



Vector::Vector()
{
}


Vector::~Vector()
{
}

float* Vector::operator[](int i)
{
	return &value[i];
}
