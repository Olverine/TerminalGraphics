#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include "Maths.h"

using namespace std;

string clear = "";
string out = "";
float zBuffer[2211];
float zClear = FLT_MIN;

char greyscale[9] = {'.',':','-','=','+','*','%','#','@'};

bool pointIsOutOfBounds(vec3 point){
	return point.x > 16 || point.x < -16 || point.y > 16 || point.y < -16;
}

int pixelLocationToCharIndex(vec3 point){
	return (round(point.y + 16) * 67) + 32 + round(point.x * 2);
}

char getGreyscaleChar(float z){
	return greyscale[int(floor(z / 4)) + 4];
}

void setPixel(int index, char c, float z){
	out[index] = getGreyscaleChar(z);
	zBuffer[index] = z;
}

void DrawPoint(vec3 point) {
	int index = pixelLocationToCharIndex(point);
	if (pointIsOutOfBounds(point) || point.z < zBuffer[index]) return;

	char c = getGreyscaleChar(point.z);
	setPixel(index, c, point.z);
	if (point.z < zBuffer[index + 1]) return;
	setPixel(index + 1, c, point.z);
}

void DrawPoint(vec2 point) {
	DrawPoint(vec3(point.x, point.y, 0));
}

void DrawPoint(vec4 point) {
	DrawPoint(vec3(point.x, point.y, 0));
}

void DrawPoint(float x, float y) {
	DrawPoint(vec3(x, y, 0));
}

void DrawPoint(float x, float y, float z) {
	DrawPoint(vec3(x, y, z));
}

void DrawLine(vec3 p1, vec3 p2) {
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
			DrawPoint(point);
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
			DrawPoint(point);
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
			DrawPoint(point);
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
	DrawPoint(point);
}

void DrawLine(vec4 p1, vec4 p2) { 
	DrawLine(vec3(p1.x, p1.y, p1.z), vec3(p2.x, p2.y, p2.z));
}

void DrawLine(int x1, int y1, int x2, int y2) {
	DrawLine(vec3(x1, y1, 0), vec3(x2, y2, 0));
}

void DrawShape(vec4* shape, mat4 matrix){
	for(int i = 1; i < shape[0].x; i+=2){
		DrawLine(matrix * shape[i], matrix * shape[i+1]);
	}
}

vec4* loadShape(string filePath){
    ifstream shapeFile;
    shapeFile.open(filePath);
	vec4 vertices[256];

    string output[256];
    int line = 0;
    if (shapeFile.is_open()) {

        while (!shapeFile.eof()) {
            getline(shapeFile, output[line]);
            istringstream ss(output[line]);
            string token;

			if(!output[line].empty()){

				int i = 0;
				while (getline(ss, token, ',')) {
					float x = stof(token);
					getline(ss, token, ',');
					float y = stof(token);
					getline(ss, token, ',');
					float z = stof(token);
					vertices[line * 2 + i + 1] = vec4(x,y,z,1);
					i++;
				}
				line++;
			}
        }
        vertices[0] = vec4(line * 2);
    }
    shapeFile.close();
	vec4* verts = vertices;
	return verts;
}

void initViewPort(){
	for(int y = 0; y < 33; y++) {
		for (int x = 0; x < 33; x++) {
			clear += "  ";
		}
		clear += "\n";
	}
}

void clearViewPort(){
	out = clear; 
	for (int i = 0; i < 2211; i++)
	{
		zBuffer[i] = -5000;
	}
}