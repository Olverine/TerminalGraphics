#include <string>
#include <iostream>
#include <stdio.h>
#include "glm/gtx/euler_angles.hpp"
#include "Graphics.h"

int main(int argc, char* argv[])
{
	vec4* shape = loadShape(argv[1]);
	initViewPort();

	mat4 model = mat4(1.0);
	mat4 view = getView(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0)); 
	mat4 projection = getPerspective(radians(90.0f), 0.1, 500);

	float rotX = 0;
	float rotY = 0;

	system("clear");

	while (true) {
		clearViewPort();		

		rotX += 0.0002f;
		rotY += 0.0005f;

		model = eulerAngleYXZ(rotY, rotX, 0.0f);

		mat4 mp =  projection * view * model;
		DrawShape(shape, mp);

		cout << out.c_str() << "\033[1;1H";
	}

    return 0;
}