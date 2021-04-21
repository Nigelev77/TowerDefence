#version 400 core

in vec2 fragTexCoords;

out vec4 outColour;

uniform float health;
uniform sampler2D tex;

void main(void)
{
	outColour = texture(tex, fragTexCoords);
	if(fragTexCoords.x<health)
		outColour = vec4(1.0, 1.0, 1.0, 1.0);
	
}