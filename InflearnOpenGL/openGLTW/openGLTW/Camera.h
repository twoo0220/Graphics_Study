#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum class CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.0f,
		float pitch = 0.0f);

private:
	void updateCameraVectors();

	glm::vec3 mPosition{};
	glm::vec3 mFront{};
	glm::vec3 mUp{};
	glm::vec3 mRight{};
	glm::vec3 mWorldUp{};

	float mYaw = 0.0f;
	float mPitch = 0.0f;
	float mMovementSpeed = 2.5f;
	float mMouseSensitivity = 0.1f;
	float mZoom = 45.0f;
};
