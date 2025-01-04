#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

Entity::Entity(const std::string id, const std::string modelID) 
	: m_id(id), m_modelID(modelID), 
	m_position(glm::vec3()), 
	m_rotation(glm::vec3()) , 
	m_scale(1.0f), 
	m_modelMatrix(glm::mat4(1.0)),
	m_orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
	m_appliedTransform(1.0f)
	{}

const std::string Entity::getID(){
	return m_id;
}

const std::string Entity::getModelID() {
	return m_modelID;
}

void Entity::applyMatrixTransform(glm::mat4 modelMatrix) {
	m_appliedTransform = modelMatrix;
}

const glm::mat4 Entity::getModelMatrix() {
	return m_modelMatrix;
}

void Entity::updateModelMatrix() {
	m_modelMatrix = glm::mat4(1.0f);
	m_modelMatrix *= m_appliedTransform;
	m_modelMatrix = glm::translate(m_modelMatrix, m_position);
	
	m_modelMatrix = m_modelMatrix * glm::mat4_cast(m_orientation);
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_scale));
}

float& Entity::getXrot() {
	return m_x;
}

float& Entity::getYrot() {
	return m_y;
}

float& Entity::getZrot() {
	return m_z;
}

glm::vec3& Entity::getPosition() {
	return m_position;
}

glm::vec3& Entity::getRotation() {
	return m_rotation;
}

float& Entity::getScale() {
	return m_scale;
}

void Entity::setPosition(const glm::vec3 position){
	m_position.x = position.x;
	m_position.y = position.y;
	m_position.z = position.z;
}

void Entity::setRotation(const glm::vec3 rotation) {
	m_rotation.x = rotation.x;
	m_rotation.y = rotation.y;
	m_rotation.z = rotation.z;
}

void Entity::setScale(const float scale) {
	m_scale = scale;
}

//	m_orientation = glm::rotate(m_orientation, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
//	m_orientation = glm::rotate(m_orientation, radianxY, glm::vec3(0.0f, 1.0f, 0.0f));
//	m_orientation = glm::rotate(m_orientation, radiansZ, glm::vec3(0.0f, 0.0f, 1.0f));
//
//	m_rotation.x = 0.0f;
//	m_rotation.y = 0.0f;
//	m_rotation.z = 0.0f;

void Entity::rotate(float x, float y, float z, float angleRad) {
	m_orientation = glm::normalize(m_orientation * glm::angleAxis(angleRad, glm::vec3(x, y, z)));
	std::cout << glm::to_string(m_orientation) << std::endl;
}

void Entity::rotate(float pitch, float yaw, float roll) {
	glm::quat p = glm::angleAxis(pitch - m_x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat y = glm::angleAxis(yaw - m_y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat r = glm::angleAxis(roll - m_z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::quat o = glm::normalize(p * y * r);	// should be xyz - zyx, from right to left
	m_orientation = glm::normalize(m_orientation * o); // this is in local coordinates, change order for world coordinate rotation

	m_x = pitch;
	m_y = yaw;
	m_z = roll;
}

void Entity::rotatePitch(float radians) {
	glm::quat o = glm::angleAxis(radians - m_x, glm::vec3(1.0f, 0.0f, 0.0f));
	m_orientation = o * m_orientation;	// rotate operands to go from world coords to local coords
	m_x = radians;
}

void Entity::rotateYaw(float radians) {
	glm::quat o = glm::angleAxis(radians - m_y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_orientation = o * m_orientation;
	m_y = radians;
}

void Entity::rotateRoll(float radians) {
	glm::quat o = glm::angleAxis(radians - m_z, glm::vec3(0.0f, 0.0f, 1.0f));
	m_orientation = o * m_orientation;
	m_z = radians;
}

void Entity::rotatePitch() {
	glm::quat o = glm::angleAxis(glm::radians(x - m_x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_orientation = o * m_orientation;	// rotate operands to go from world coords to local coords
	//m_x = radians;
	x = m_x;
}

void Entity::rotateYaw() {
	glm::quat o = glm::angleAxis(glm::radians(y - m_y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_orientation = o * m_orientation;
	y = m_y;
//	m_y = radians;
}

void Entity::rotateRoll() {
	glm::quat o = glm::angleAxis(glm::radians(z - m_z), glm::vec3(0.0f, 0.0f, 1.0f));
	m_orientation = o * m_orientation;
	z = m_z;
//	m_z = radians;
}
