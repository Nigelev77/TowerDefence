#version 400 core

in vec3 fragColor;

out vec4 outColor;


void main(void)
{
	outColor = vec4(fragColor, 1.0);

}