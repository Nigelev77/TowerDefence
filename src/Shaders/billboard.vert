#version 400 core

layout(location = 0) in vec3 vertPos;

out vec2 fragTexCoords; 

uniform vec3 worldPos;
uniform vec2 scale;
uniform mat4 proj;
uniform mat4 view;

void main(void)
{
	vec3 camUp = vec3(view[0][1], view[1][1], view[2][1]);
	vec3 camRight = vec3(view[0][0], view[1][0], view[2][0]);
	vec3 boardRight = camRight*scale.x*vertPos.x;
	vec3 boardUp = camUp*scale.y*vertPos.y;
	vec3 boardWorldPos = worldPos+boardRight+boardUp;
	gl_Position = proj * view * vec4(boardWorldPos, 1.0);

	fragTexCoords = vertPos.xy + vec2(0.5, 0.5);
}