#include "Camera.h"
#include <iostream>
#include <iomanip> 

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov) : m_movementSpeed(c_SPEED),
m_mouseSensitivity(c_SENSITIVITY), m_fov(fov), m_position(position), m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), m_yaw(yaw), m_pitch(pitch) {
	updateCameraVectors();

}

mat4 Camera::getViewMatrix() {
	//std::cout << std::fixed << std::setprecision(10) <<
	//	" pos: " << m_position.x << " " << m_position.y << " " << m_position.z << 
	//	" right: " << m_right.x << " " << m_right.y << " " << m_right.z <<
	//	" up: " << m_up.x << " " << m_up.y << " " << m_up.z <<
	//	" front: " << m_front.x << " " << m_front.y << " " << m_front.z << 
	//	//" yaw: " << m_yaw << " pitch: " << m_pitch <<
	//	std::endl;

	return lookAt(m_position, /*glm::vec3(0.0f, 0.0f, 1.0f)*/ m_position + m_front, glm::vec3(0.0f, 1.0f, 0.0f)/*m_up*/);
}

// this should be in input
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

void Camera::cameraRotate(float xoffset, float yoffset, bool constrainPitch) {
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	float val = 1.0f;

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
	m_fov -= (float)offsetY;
	if (m_fov < 1.0f)
		m_fov = 1.0f;
	if (m_fov > 45.0f)
		m_fov = 45.0f;

	// Orthagonal zoom
	float zoomSpd = 0.025f * -offsetY;
	m_orthoZoom += zoomSpd;
	if (m_orthoZoom < 0.1f)
		m_orthoZoom = 0.1f;
	if (m_orthoZoom > 10.0f)
		m_orthoZoom = 10.0f;
}

void Camera::updateCameraVectors() {
	vec3 front;
	front.x = cos(radians(m_yaw)) * cos(radians(m_pitch));
	front.y = sin(radians(m_pitch));
	front.z = sin(radians(m_yaw)) * cos(radians(m_pitch));
	m_front = normalize(front);
	m_right = normalize(cross(front, m_worldUp));
	m_up = normalize(cross(m_right, front));
}
