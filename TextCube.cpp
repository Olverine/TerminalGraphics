#include <string>
#include <iostream>
#include <stdio.h>
#include "Graphics.h"
#include "quaternion.hpp" 

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"


double before;
double after;
double delta;

int main()
{

	for (int y = 0; y < 33; y++) {
		for (int x = 0; x < 33; x++) {
			clear += "  ";
		}
		clear += "\n";
	}

	mat4 model = mat4(1.0);
	mat4 view = getView(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0)); 
	mat4 projection = getPerspective(radians(90.0f), 0.1, 500);

	//system("pause");
//	SetCursorPos(1366 / 2, 768 / 2);
//	printf(RESET);

	float rotX = 0;
	float rotY = 0;


	while (true) {

//		before = GetTickCount();

		out = clear; 

		for (int i = 0; i < 2211; i++)
		{
			zBuffer[i] = -5000;
		}
		
/*		if (GetKey(VK_RIGHT)) {
			rotX = 0.002f;
		}
		else if (GetKey(VK_LEFT)) {
			rotX = -0.002f;
		}
		else {
			rotX = 0;
		}
		if (GetKey(VK_UP)) {
			rotY = 0.002f;
		}
		else if (GetKey(VK_DOWN)) {
			rotY = -0.002f;
		}
		else {
			rotY = 0;
		}
*/
		/* UNCOMMENT FOR MOUSE CONTROLS! (WINDOWS ONLY!)
		POINT p;
		GetCursorPos(&p);
		rotX = (float)p.x / 1366 - 0.5f;
		rotY = (float)p.y / 768 - 0.5f;
		SetCursorPos(1366 / 2, 768 / 2);
		ShowCursor(false);
		*/

		rotX = 0.0001f;
		rotY = 0.00005f;

		quat rot = quat(vec3(rotY, rotX, 0));

		model *= mat4_cast(rot);

		mat4 mp = model * view * projection ;

		Draw3dBox(vec3(0), vec3(18), mp);

		//DrawLine(0, 0, cos(radians(t)) * 17, sin(radians(t)) * 17);

		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\\" << out.c_str();

//		after = GetTickCount();
//		delta = after - before;
//		before = GetTickCount();
		//printf("%d fps", (1.0 / delta * 1000.0));
	}

//	system("pause");

    return 0;
}
