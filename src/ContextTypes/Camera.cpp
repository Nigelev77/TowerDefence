#include "Camera.h"


void Camera::MoveCamera(glm::vec3 displacement)
{
	m_Pos += displacement;
}

void Camera::RotateCamera(glm::vec3 angles)
{
	//x is up/down
	//y is left/right
	//TODO: Maybe find a work around with fewer branches?
	m_EulerRots += angles;
	if (m_EulerRots.x > 90.0f && m_EulerRots.x<270.0f) m_EulerRots.x = 90.0f;
	if (m_EulerRots.x < 270.0f && m_EulerRots.x > 90.0f) m_EulerRots.x = 270.0f;
	if (m_EulerRots.x >360.0f) m_EulerRots.x -= 360.0f;
	if (m_EulerRots.y >360.0f) m_EulerRots.y -= 360.0f;
	if (m_EulerRots.x < 0) m_EulerRots.x += 360.0f;
	if (m_EulerRots.y < 0) m_EulerRots.y += 360.0f;
}

const glm::mat4& Camera::CalculateViewMat()
{
	m_viewMat = glm::mat4(1.0f);
	m_viewMat = glm::rotate(m_viewMat, glm::radians(m_EulerRots.x), X_UNIT_VEC);
	m_viewMat = glm::rotate(m_viewMat, glm::radians(m_EulerRots.y), Y_UNIT_VEC);
	m_viewMat = glm::rotate(m_viewMat, glm::radians(m_EulerRots.z), Z_UNIT_VEC);
	m_viewMat = glm::translate(m_viewMat, -m_Pos);
	return m_viewMat;

}

const glm::mat4& Camera::GetViewMat() const
{
	return m_viewMat;
}



Camera::Camera()
	: m_Pos{}, m_EulerRots{}, m_viewMat{}, m_Proj{glm::perspective(45.0f, 16.0f/9.0f, 0.5f, 250.0f)}
{}