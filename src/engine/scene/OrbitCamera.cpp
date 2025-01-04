#include "OrbitCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include <glm/gtx/string_cast.hpp>

#include <glm/gtc/constants.hpp>

OrbitCamera::OrbitCamera(const glm::vec3 center, float radius, float minRadius, float azimuthAngle, float polarAngle)
	:m_center(center), m_upVector(0.0f, 1.0f, 0.0f), m_radius(radius), m_minRadius(minRadius), m_azimuthAngle(azimuthAngle), m_polarAngle(polarAngle),
	m_newRightVector(glm::vec3(0.0f)){}

OrbitCamera::~OrbitCamera() {
	std::cout << "Deleting orbit camera" << std::endl;
}

// Rotate azimuth
void OrbitCamera::rotateYaw(const float radians) {
	m_azimuthAngle += radians;

	//Keep azimuth angle iwthin range <0..2PI - it's not necessary, just to have it nicely output
		
	const auto fullCircle = 2.0f * 3.14; // pi glm
	m_azimuthAngle = fmod(m_azimuthAngle, fullCircle);
	if (m_azimuthAngle < 0.0f)
		m_azimuthAngle = fullCircle + m_azimuthAngle;
}

// Rotate polar
void OrbitCamera::rotatePitch(const float radians) {
	m_polarAngle += radians;
	// Check if the angle hasn't axceeded quaretr of a cricle to prevent flip, add a bit of epsiolon like 0.001 radians
	const auto polarCap = 3.14f / 2.0f - 0.001f;
		if (m_polarAngle > polarCap)
			m_polarAngle = polarCap;

		if (m_polarAngle < -polarCap)
			m_polarAngle = -polarCap;
}

void OrbitCamera::rotateRoll(const float radians){}

void OrbitCamera::moveForward(const float by) {
	m_radius -= by;
	if (m_radius < m_minRadius)
		m_radius = m_minRadius;
} 

void OrbitCamera::moveHorizontal(const float distance) {
	const auto m_position = getPosition();
	const glm::vec3 viewVector = getForwardVector();
	const glm::vec3 strafeVector = glm::normalize(glm::cross(viewVector, m_upVector));
	m_newRightVector = strafeVector;
	m_center += strafeVector * distance;
}

void OrbitCamera::moveVertical(const float distance) {
	const glm::vec3 viewVector = getForwardVector();
	const glm::vec3 newUpVector = glm::normalize(glm::cross(m_newRightVector, viewVector));
	m_center += newUpVector * distance;
}

glm::vec3 OrbitCamera::getPosition() const {

	// Calculate sines / cosines angles
	const auto sineAzimuth = sin(m_azimuthAngle);
	const auto cosineAzimuth = cos(m_azimuthAngle);
	const auto sinePolar = sin(m_polarAngle);
	const auto cosinePolar = cos(m_polarAngle);

	// Calculate eye m_position ut of them

	const auto x = m_center.x + m_radius * cosinePolar * cosineAzimuth;
	const auto y = m_center.y + m_radius * sinePolar;
	const auto z = m_center.z + m_radius * cosinePolar * sineAzimuth;

	return glm::vec3(x, y, z);
}

glm::mat4 OrbitCamera::getViewMatrix() const {
	auto m_position = getPosition();
	return glm::lookAt(m_position, m_center, m_upVector);
}

glm::vec3 OrbitCamera::getForwardVector() const {
	const auto m_position = getPosition();
	return glm::normalize(m_center - m_position);
}

float OrbitCamera::getAngleYaw() const {
	return m_azimuthAngle;
}

float OrbitCamera::getAnglePitch() const {
	return m_polarAngle;
}

float OrbitCamera::getAngleRoll() const {
	return 0.0f;
}