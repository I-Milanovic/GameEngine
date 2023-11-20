#include "Camera.h"
#include <iostream>


Camera::Camera(glm::vec3 position, glm::vec3 up , float yaw, float pitch) :m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_movementSpeed(c_SPEED), m_mouseSensitivity(c_SENSITIVITY), m_zoom(c_ZOOM), m_position(position), m_worldUp(up), m_yaw(yaw), m_pitch(pitch) {
	updateCameraVectors();
}

mat4 Camera::getViewMatrix() {
	return lookAt(m_position, m_position + m_front, m_up);
}

void Camera::cameraMove(CameraMovement direction, float deltaTime) {
	float velocity = m_movementSpeed * deltaTime;
	if (direction == FORWARD)
		m_position += m_front * velocity;
	if (direction == BACKWARD)
		m_position -= m_front * velocity;
	if (direction == LEFT)
		m_position -= m_right * velocity;
	if (direction == RIGHT)
		m_position += m_right * velocity;
}

void Camera::cameraRotate(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	// update front, right and up vectors using the updated euler angles
	updateCameraVectors();
}

void Camera::cameraZoom(float offsetY) {
	m_zoom -= (float)offsetY;
	if (m_zoom < 1.0f)
		m_zoom = 1.0f;
	if (m_zoom > 45.0f)
		m_zoom = 45.0f;
}


void Camera::updateCameraVectors() {
	vec3 front;
	front.x = cos(radians(m_yaw)) * cos(radians(m_pitch));
	front.y = sin(radians(m_pitch));
	front.z = sin(radians(m_yaw)) * cos(radians(m_pitch));

	m_front = normalize(front);

	// also re-calculating the right and up vectors
	m_right = normalize(cross(front, m_worldUp));
	// noramlize the vectors, because their length gets closer to 0 the more you
	//look up or down which results in slower movement
	m_up = normalize(cross(m_right, front));
}
