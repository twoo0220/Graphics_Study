#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
	: m_width(width)
	, m_height(height)
	, m_speed(0.1f)
	, m_sensitivity(100.0f)
	, Position(position)
	, Orientation(glm::vec3(0.0f, 0.0f, -1.0f))
	, Up(glm::vec3(0.0f, 1.0f, 0.0f))
{
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(m_width / m_height), nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow* window)
{
}
