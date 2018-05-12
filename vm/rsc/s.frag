#version 410 core
out vec4 FragColor;
in vec4 vColor;

void main()
{
	vec2 circCoord = 2.0 * gl_PointCoord - 1;
	if (dot(circCoord, circCoord) > 0.9) {
		discard;
	}
	FragColor = vColor;
}
