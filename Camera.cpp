#include "Camera.hpp"

#include <glm/gtx/rotate_vector.hpp>

Camera::Camera()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	
	m_direction = glm::vec3(0.0f, 0.0f, -1.0f);

	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(m_position, m_position + m_direction, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::rotate(float angle, glm::vec3 axis)
{
	m_direction = glm::rotate(m_direction, angle, axis);

	m_up = glm::rotate(m_up, angle, axis);
}
