#version 400 core

layout(location = 0) in vec3 vertVert;


uniform mat4 u_MVP;
void main(void)
{
	gl_Position = u_MVP*vec4(vertVert, 1.0);

}