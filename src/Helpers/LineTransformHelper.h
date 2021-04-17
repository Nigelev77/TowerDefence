#pragma once

#include "glm/glm.hpp"
#include "glad/glad.h"



GLuint GetLineBuffer();
GLuint GetLineVertices();

void InitLine();

namespace Line
{
	glm::mat4 GetTransformMatrix(glm::vec3 line, glm::vec3 pos);
}