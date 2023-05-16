#include "Camera.h"
#include <SDL.h>

namespace WorldEngine
{
	Camera::Camera()
	{
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		front = glm::vec3(0.0f, 0.0f, -1.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		worldUp = up;
		yaw = -90.0f;
		pitch = 0.0f;
		roll = 0.0f;
		moveSpeed = 0.5f;
		turnSpeed = 0.1f;
		Update();
	}
	Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
	{
		position = startPosition;
		front = glm::vec3(0.0f, 0.0f, -1.0f);
		worldUp = startUp;
		yaw = startYaw;
		pitch = startPitch;
		roll = 0.0f;
		moveSpeed = startMoveSpeed;
		turnSpeed = startTurnSpeed;
		Update();
	}
	void Camera::KeyControl(bool* keys, GLfloat deltaTime)
	{
		GLfloat velocity = moveSpeed * deltaTime;

		if (keys[SDLK_w])
		{
			position += front * velocity;
		}
		if (keys[SDLK_s])
		{
			position -= front * velocity;
		}
		if (keys[SDLK_a])
		{
			position -= right * velocity;
		}
		if (keys[SDLK_d])
		{
			position += right * velocity;
		}
	}
	void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
	{
		xChange *= turnSpeed;
		yChange *= turnSpeed;
		yaw += xChange;
		pitch += yChange;
		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}
		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}
		Update();
	}

	glm::mat4 Camera::CalculateViewMatrix()
	{
		return glm::lookAt(position, position + front, up);
	}

	void Camera::Update()
	{
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}

	Camera::~Camera()
	{

	}
}