#version 410 core
layout (location = 0) in vec3 aPos;   // The posiiton of the vertex
layout (location = 1) in vec3 vClr;   // The color of the vertex
#define M_PI 3.1415926535897932384626433832795
out vec4 vColor; // output a color to the fragment shader

void main()
{
	float zCos = cos(M_PI / -2);
	float zSin = sin(M_PI / -2);
	float yCos = cos(M_PI / 4);
	float ySin = sin(M_PI / 4);
	float xCos = cos(M_PI / -4);
	float xSin = sin(M_PI / -4);
	mat4 rotZ = mat4(zCos, zSin, 0, 0,
					-zSin, zCos, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
	mat4 rotX = mat4(1, 0, 0, 0,
					0, xCos, xSin, 0,
					0, -xSin, xCos, 0,
					0, 0, 0, 1);
	mat4 rotY = mat4(yCos, 0, -ySin, 0,
					0, 1, 0, 0,
					ySin, 0, yCos, 0,
					0, 0, 0, 1);

	gl_Position = rotZ * vec4(aPos, 1.0);
	gl_Position = rotX * gl_Position;
	// vColor = vClr;
	vColor = vec4(vClr.x / 255, vClr.y / 255, vClr.z / 255, 1.0);
	gl_PointSize = 7.0; // set ourColor to the input color we got from the vertex data
}
