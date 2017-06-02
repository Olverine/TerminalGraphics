#pragma once
class Vector
{
	float value[4];
public:
	Vector();
	~Vector();
	float* operator[](int i);
};

