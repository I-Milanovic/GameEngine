#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up , float yaw, float pitch) :front(glm::vec3(0.0f, 0.0f, -1.0f)),
	movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM), position(position), worldUp(up), yaw(yaw), pitch(pitch)
{
	updateCameraVectors();
}
/*
Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
	float upZ, float yaw, float pitch) :
	position(vec3(posX, posY, posZ)),
	up(vec3(upX, upY, upZ)),
	front(vec3(0.0f, 0.0f, -1.0f)),
	movementSpeed(SPEED),
	mouseSensitivity(SENSITIVITY),
	zoom(ZOOM),
	yaw(yaw),
	pitch(pitch) {

}
*/
mat4 Camera::getViewMatrix() {
	return lookAt(position, position + front, up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// update front, right and up vectors using the updated euler angles
	updateCameraVectors();
}

void Camera::processMouseScroll(float offsetY) {
	zoom -= (float)offsetY;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;

}

void Camera::updateCameraVectors() {
	vec3 front;
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));

	front = normalize(front);

	// also re-calculating the right and up vectors
	right = normalize(cross(front, worldUp));
	// noramlize the vectors, because their length gets closer to 0 the more you
	//look up or down which results in slower movement
	up = normalize(cross(right, front));
}
