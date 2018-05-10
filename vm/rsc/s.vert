#version 410 core
layout (location = 0) in vec3 aPos;   // The posiiton of the vertex
layout (location = 1) in vec3 aColor;   // The posiiton of the vertex
#define M_PI 3.1415926535897932384626433832795
uniform float rotx;
uniform float roty;
uniform float s;
out vec4 vColor; // output a color to the fragment shader

void main()
{
	float zCos = cos(M_PI * roty);
	float zSin = sin(M_PI * roty);
	float yCos = cos(M_PI);
	float ySin = sin(M_PI);
	float xCos = cos(M_PI / 3 * rotx);
	float xSin = sin(M_PI / 3 * rotx);
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
	mat4 scale = mat4(s, 0, 0, 0,
				0, s, 0, 0,
				0, 0, s, 0,
				0, 0, 0, 1);
	gl_Position = rotZ * vec4(aPos, 1.0);
	gl_Position = rotY * gl_Position;
	gl_Position = rotX * gl_Position;
	gl_Position = scale * gl_Position;
	vColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);
	gl_PointSize = 4.0; // set ourColor to the input color we got from the vertex data
}
