#include "LineTransformHelper.h"

#include <math.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"


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
    glm::mat4 GetTransformMatrix(glm::vec3 line, glm::vec3 pos)
    {
        const float scale = glm::length(line);
        const glm::vec3 normLine = glm::normalize(line);
        const float dotProd = glm::dot(X_AXIS, normLine);
        const glm::vec3 perp = glm::cross(X_AXIS, normLine);
        glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 0.0f, 0.0f));
        float s = std::sqrt((1 + dotProd) * 2);
        float invs = 1.0f / s;
        glm::quat o{ s * 0.5f, perp.x * invs, perp.y * invs, perp.z * invs };
        glm::mat4 transMat = glm::translate(glm::mat4(1.0f), pos);
        glm::mat4 transform = transMat * glm::toMat4(o) * scaleMat;
        //TODO: UNDERSTAND MORE ABOUT QUATERNIONS
        return transform;
    }

}


