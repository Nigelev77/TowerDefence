#version 400 core

layout(location = 0) in vec3 vertVert;


out vec3 fragColor;

uniform mat4 u_MVP;
uniform float boundary;


void main(void)
{
	gl_Position = u_MVP * vec4(vertVert, 1.0);

	//TODO: Try to refactor this so that it has no branching

	


	if(abs(vertVert.x)<=boundary && abs(vertVert.z)<=boundary)
	{
		fragColor = vec3(0.0, 1.0, 0.0);
	}
	else
	{
		fragColor = vec3(1.0, 1.0, 1.0);
	}
}