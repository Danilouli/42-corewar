#version 330 core
out vec4 FragColor;
in vec4 vColor;

void main()
{
	vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
	if (dot(circCoord, circCoord) > 0.8) {
		discard;
	}
	FragColor = vColor;
}
