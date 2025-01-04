#include "QuatCamera.h"

#include <iostream>

#include <glm/matrix.hpp>

#include <glm/gtx/string_cast.hpp>

QuatCamera::QuatCamera(glm::vec3 pos) :
	m_position(pos),
	m_orientation(glm::quat()),
	m_quatPitch(glm::quat(glm::angleAxis(0.0f, glm::vec3(1.0f, 0.0f, 0.0f)))),
	m_quatYaw(glm::quat(glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)))) {
	std::cout << glm::to_string(m_quatPitch) << std::endl;
}

QuatCamera::~QuatCamera() {
	std::cout << "Deleting Quat Camera" << std::endl;
}

void QuatCamera::moveForward(const float distance){}

void QuatCamera::moveHorizontal(const float distance) {
	//m_position += -offsetX * right * spd;
	//m_position += -offsetY * up * spd;
	m_position += distance * glm::vec3(1.0f, 0.0f, 0.0f);
}

void QuatCamera::moveVertical(const float distance) {
	m_position += distance * glm::vec3(0.0f, 1.0f, 0.0f);
}

void QuatCamera::rotateYaw(const float radians){ 
	 m_quatYaw = glm::angleAxis(radians, glm::vec3(0.0f, 1.0f, 0.0f));	
	 m_orientation = glm::normalize(m_quatPitch * m_quatYaw);
}

void QuatCamera::rotatePitch(const float radians) {
	m_quatPitch = glm::angleAxis(radians, glm::vec3(1.0f, 0.0f, 0.0f));
	m_orientation = glm::normalize(m_quatPitch * m_quatYaw);
}

void QuatCamera::rotateRoll(const float radians){}

glm::vec3 QuatCamera::getPosition() const{
	return m_position;
}

glm::vec3 QuatCamera::getForwardVector() const {
	return glm::vec3();
}

float QuatCamera::getAngleYaw() const {
	return 0.0f;
}

float QuatCamera::getAnglePitch() const {
	return 0.0f;
}

float QuatCamera::getAngleRoll() const {
	return 0.0f;
}

glm::mat4 QuatCamera::getViewMatrix() const {
	glm::mat4 t1 = glm::translate(glm::mat4(1.0f), -m_position);
	glm::mat4 r = glm::mat4_cast(m_orientation);
	return  t1 * r;
}

//zapisi ovo leba ti
//float p = glm::degrees(glm::m_pitch(m_orientation));
//float y = glm::degrees(glm::m_yaw(m_orientation));;
//glm::vec3 ax = glm::axis(m_orientation);
////float angle = glm::acos(glm::dot(glm::normalize(m_position), ax));
