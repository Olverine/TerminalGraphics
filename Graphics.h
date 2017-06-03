#pragma once
#include <string>
#include "Maths.h"

using namespace std;

string clear = "";
string out = "";
float zBuffer[2211];
float zClear = FLT_MIN;

void DrawPoint(vec3 point, char character) {
	if (point.x > 16 || point.x < -16 || point.y > 16 || point.y < -16)
		return;

	int index = (round(point.y + 16) * 67) + 32 + round(point.x * 2);

	if (point.z < zBuffer[index])
		return;

	out[index] = 'X';
	zBuffer[index] = point.z;
	if (point.z < zBuffer[index + 1])
		return;
	out[index + 1] = 'X';
	zBuffer[index + 1] = point.z;
}

void DrawPoint(vec2 point, char character) {
	DrawPoint(vec3(point.x, point.y, 0), character);
}

void DrawPoint(vec4 point, char character) {
	DrawPoint(vec3(point.x, point.y, 0), character);
}

void DrawPoint(float x, float y, char character) {
	DrawPoint(vec3(x, y, 0), character);
}

void DrawPoint(float x, float y, float z, char character) {
	DrawPoint(vec3(x, y, z), character);
}

void DrawLine(vec3 p1, vec3 p2, char character) {
	int i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
	vec3 point = p1;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	dz = p2.z - p1.z;
	x_inc = (dx < 0) ? -1 : 1;
	l = abs(dx);
	y_inc = (dy < 0) ? -1 : 1;
	m = abs(dy);
	z_inc = (dz < 0) ? -1 : 1;
	n = abs(dz);
	dx2 = l << 1;
	dy2 = m << 1;
	dz2 = n << 1;

	if ((l >= m) && (l >= n)) {
		err_1 = dy2 - l;
		err_2 = dz2 - l;
		for (i = 0; i < l; i++) {
			DrawPoint(point, 'h');
			if (err_1 > 0) {
				point.y += y_inc;
				err_1 -= dx2;
			}
			if (err_2 > 0) {
				point.z += z_inc;
				err_2 -= dx2;
			}
			err_1 += dy2;
			err_2 += dz2;
			point.x += x_inc;
		}
	}
	else if ((m >= l) && (m >= n)) {
		err_1 = dx2 - m;
		err_2 = dz2 - m;
		for (i = 0; i < m; i++) {
			DrawPoint(point, 'h');
			if (err_1 > 0) {
				point.x += x_inc;
				err_1 -= dy2;
			}
			if (err_2 > 0) {
				point.z += z_inc;
				err_2 -= dy2;
			}
			err_1 += dx2;
			err_2 += dz2;
			point.y += y_inc;
		}
	}
	else {
		err_1 = dy2 - n;
		err_2 = dx2 - n;
		for (i = 0; i < n; i++) {
			DrawPoint(point, 'h');
			if (err_1 > 0) {
				point.y += y_inc;
				err_1 -= dz2;
			}
			if (err_2 > 0) {
				point.x += x_inc;
				err_2 -= dz2;
			}
			err_1 += dy2;
			err_2 += dx2;
			point.z += z_inc;
		}
	}
	DrawPoint(point, 'h');
}

/*void DrawLine(vec3 p1, vec3 p2, char character) {
	if (p1 == p2) {
		DrawPoint(p1, character);
		return;
	}

	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	int sx = dx < 0 ? -1 : 1;
	int sy = dy < 0 ? -1 : 1;

	float distance = Distance(p1, p2);

	float slope = 0;
	float pitch = 0;

	int i = 0;

	if (abs(dy) < abs(dx)) { 
		slope = dy / dx;
		pitch = p1.y - slope * p1.x;
		while (trunc(p1.x) != trunc(p2.x)) {
			DrawPoint(p1.x, slope * p1.x + pitch, Lerp(p1.z, p2.z, Distance(p1, p2) / distance), character);
			p1.x += sx;
			i++;
		}
	}
	else {
		slope = dx / dy;
		pitch = p1.x - slope * p1.y;
		while (trunc(p1.y) != trunc(p2.y)) {
			DrawPoint(slope * p1.y + pitch, p1.y, Lerp(p1.z, p2.z, Distance(p1, p2) / distance), character);
			p1.y += sy;
			i++;
		}
	}

	DrawPoint(p2.x, p2.y, Lerp(p1.z, p2.z, Distance(p1, p2) / distance), character);
}*/

void DrawLine(vec4 p1, vec4 p2) { 
	DrawLine(vec3(p1.x, p1.y, p1.z), vec3(p2.x, p2.y, p2.z), static_cast<char>(176));
}

void DrawLine(int x1, int y1, int x2, int y2) {
	DrawLine(vec3(x1, y1, 0), vec3(x2, y2, 0), static_cast<char>(176));
}

void Draw3dBox(vec3 position, vec3 dimensions, mat4 matrix){
	vec3 p = position;
	vec3 d = dimensions / 2.0f;
	DrawLine(matrix * vec4(p.x - d.x, p.y - d.y, p.z + d.z, 1), matrix * vec4(p.x + d.x, p.y - d.y, p.z + d.z, 1));
	DrawLine(matrix * vec4(p.x + d.x, p.y - d.y, p.z + d.z, 1), matrix * vec4(p.x + d.x, p.y + d.y, p.z + d.z, 1));
	DrawLine(matrix * vec4(p.x + d.x, p.y + d.y, p.z + d.z, 1), matrix * vec4(p.x - d.x, p.y + d.y, p.z + d.z, 1));
	DrawLine(matrix * vec4(p.x - d.x, p.y + d.y, p.z + d.z, 1), matrix * vec4(p.x - d.x, p.y - d.y, p.z + d.z, 1));
	DrawLine(matrix * vec4(p.x - d.x, p.y - d.y, p.z - d.z, 1), matrix * vec4(p.x + d.x, p.y - d.y, p.z - d.z, 1));
	DrawLine(matrix * vec4(p.x + d.x, p.y - d.y, p.z - d.z, 1), matrix * vec4(p.x + d.x, p.y + d.y, p.z - d.z, 1));
	DrawLine(matrix * vec4(p.x + d.x, p.y + d.y, p.z - d.z, 1), matrix * vec4(p.x - d.x, p.y + d.y, p.z - d.z, 1));
	DrawLine(matrix * vec4(p.x - d.x, p.y + d.y, p.z - d.z, 1), matrix * vec4(p.x - d.x, p.y - d.y, p.z - d.z, 1));
	DrawLine(matrix * vec4(p.x - d.x, p.y - d.y, p.z - d.z, 1), matrix * vec4(p.x - d.x, p.y - d.y, p.z + d.z, 1));
	DrawLine(matrix * vec4(p.x + d.x, p.y - d.y, p.z - d.z, 1), matrix * vec4(p.x + d.x, p.y - d.y, p.z + d.z, 1));
	DrawLine(matrix * vec4(p.x + d.x, p.y + d.y, p.z - d.z, 1), matrix * vec4(p.x + d.x, p.y + d.y, p.z + d.z, 1));
	DrawLine(matrix * vec4(p.x - d.x, p.y + d.y, p.z - d.z, 1), matrix * vec4(p.x - d.x, p.y + d.y, p.z + d.z, 1));
}
