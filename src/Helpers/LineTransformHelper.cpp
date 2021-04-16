#include "LineTransformHelper.h"

#include <math.h>
#include "glm/gtc/matrix_transform.hpp"

#define X_AXIS glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_AXIS glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_AXIS glm::vec3(0.0f, 0.0f, 1.0f)

static GLuint bufferID = 0;

static const float buffer[6] =
{
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f
};

static const unsigned int indices[2] =
{
    0,1
};

static glm::vec3 initialLine{ 1.0f, 0.0f, 0.0f };

GLuint GetLineBuffer()
{
    return bufferID;
}

GLuint GetLineVertices()
{
    return 2;
}

void InitLine()
{
    
    glGenVertexArrays(1, &bufferID);
    glBindVertexArray(bufferID);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), buffer, GL_STATIC_DRAW);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


namespace Line
{
    glm::mat4 GetTransformMatrix(glm::vec3 line)
    {
        const float scale = glm::distance({ 0.0f, 0.0f, 0.0f }, line);
        const double xAngle = std::atan2(line.y, line.x);
        const double zAngle = std::atan2(line.x, line.z);
        const double yAngle = std::atan2(line.x, line.y);
        glm::mat4 transformMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f, 1.0f));
        transformMat = glm::rotate(transformMat, (float)xAngle, X_AXIS);
        transformMat = glm::rotate(transformMat, (float)yAngle, Y_AXIS);
        transformMat = glm::rotate(transformMat, (float)zAngle, Z_AXIS);
        return transformMat;
    }

}


