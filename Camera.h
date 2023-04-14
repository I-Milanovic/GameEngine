#pragma once

#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT, 
	RIGHT
};

const float YAW = -90.f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 worldUp;

	// euler angles

	float yaw;
	float pitch;
	float mouseSensitivity;
	float movementSpeed;
	float zoom;

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) ;

//	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	mat4 getViewMatrix();

	void processKeyboard(CameraMovement direction, float deltaTime);

	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	void processMouseScroll(float offsetY);

private:
	void updateCameraVectors();

};
