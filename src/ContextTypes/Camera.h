#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/matrix_transform.hpp"


#define X_UNIT_VEC glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_UNIT_VEC glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_UNIT_VEC glm::vec3(0.0f, 0.0f, 1.0f)

class Camera
{
public:
	glm::mat4 m_viewMat;
	glm::mat4 m_Proj;
	glm::vec3 m_Pos;
	glm::vec3 m_EulerRots;
	
	Camera();
	void MoveCamera(glm::vec3 displacement);
	void RotateCamera(glm::vec3 angles);
	const glm::mat4& CalculateViewMat();
	const glm::mat4& GetViewMat() const;
};

