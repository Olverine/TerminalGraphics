#pragma once

#include "Vector.h"

class Matrix
{
	Vector row[4];
public:
	Matrix();
	~Matrix();

	Matrix operator*(Matrix mat);
	Matrix operator*(Vector vec);
	Vector* operator[](int i);
};