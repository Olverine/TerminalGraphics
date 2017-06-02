#pragma once
#include <Windows.h>

bool GetKey(int key) {
	return (GetAsyncKeyState(key) < 0);
}