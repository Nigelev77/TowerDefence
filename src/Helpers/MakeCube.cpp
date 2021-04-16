#include "MakeCube.h"

static GLuint bufferID = 0;

const static float buffer[24] =
{
	-0.5f, -0.5f, 0.5f, //0
	-0.5f, 0.5f, 0.5f, //1
	0.5f, 0.5f, 0.5f, //2
	0.5f, -0.5f, 0.5f, //3
	-0.5f, -0.5f, -0.5f, //4
	-0.5f, 0.5f, -0.5f, //5
	0.5f, 0.5f, -0.5f, //6
	0.5f, -0.5f, -0.5f //7
};

const static unsigned int indices[24] =
{
	0, 1,
	1, 2,
	2, 3,
	3,0,
	4,5,
	5,6,
	6, 7,
	7, 4,
	0, 4,
	1, 5,
	2, 6,
	3, 7
};

//Creates Unit Cube and uploads it to create a VAO for the buffers in memory
void InitCube()
{
	glGenVertexArrays(1, &bufferID);
	glBindVertexArray(bufferID);


	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), buffer, GL_STATIC_DRAW);
	

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


GLuint GetCubeBuffer()
{
	return bufferID;
}

GLuint GetCubeVertexCount()
{
	return 24;
}

