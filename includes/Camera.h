#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
const float SENSITIVITY	= 0.1f;
const float YAW			= -90.0f;
const float PITCH		= 0.0f;
const float SPEED		= 2.5f;
const float ZOOM		= 45.0f;

class Camera 
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Yaw;
	float Pitch;
	float MoveSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = YAW,
		float pitch = PITCH)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)),
		MoveSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Zoom(ZOOM) 
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	Camera(float posX = 0.0f,
		float posY = 0.0f,
		float posZ = 0.0f,
		float upX = 0.0f,
		float upY = 1.0f,
		float upZ = 0.0f,
		float yaw = YAW,
		float pitch = PITCH)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)),
		MoveSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix() { return glm::lookAt(Position, Position + Front, Up); }
#pragma region Process Input
	void ProcessKeyboard(Camera_Movement dir, float deltaTime)
	{
		float velocity = MoveSpeed * deltaTime;
		switch (dir)
		{
		case FORWARD:
			Position += Front * velocity;
			break;
		case BACKWARD:
			Position -= Front * velocity;
			break;
		case LEFT:
			Position -= Right * velocity;
			break;
		case RIGHT:
			Position += Right * velocity;
			break;
		default:
			break;
		}
	}

	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= MouseSensitivity;
		yOffset *= MouseSensitivity;
		Yaw += xOffset;
		Pitch += yOffset;
		if (constrainPitch) {
			if (Pitch > 89.0f)Pitch = 89.0f;
			if (Pitch < -89.0f) Pitch = -89.0f;
		}
		updateCameraVectors();
	}

	void ProcessMouseScroll(float yOffset) {
		Zoom -= yOffset;
		if (Zoom < 1.0f) Zoom = 1.0f;
		if (Zoom > 45.0f) Zoom = 45.0f;
	}

#pragma endregion
			
private:
	void updateCameraVectors() 
	{
		// calculate the new Front Vec
		glm::vec3 dir;
		dir.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		dir.y = sin(glm::radians(Pitch));
		dir.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(dir);
		// new Right/Up Vec
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));

	}
};