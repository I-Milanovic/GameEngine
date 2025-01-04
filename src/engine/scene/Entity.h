#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <glm/gtc/quaternion.hpp>

#include <glm/glm.hpp>

#include <src/engine/scene/AnimationManager.h>

class Entity {

public:
	Entity(const std::string id, const std::string modelID);

	const std::string getID();
	const std::string getModelID();
	void applyMatrixTransform(glm::mat4 modelMatrix);
	const glm::mat4 getModelMatrix();
	glm::vec3& getPosition();
	glm::vec3& getRotation();
	float&  getScale();

	void setPosition(const glm::vec3 position);
	void setRotation(const glm::vec3 rotation);
	void setScale(const float scale);

	void rotate(float x, float y, float z, float angleRad);
	void rotate(float pitch, float yaw, float roll);

	void rotateYaw(float radians);
	void rotatePitch(float radians);
	void rotateRoll(float radians);

	void rotatePitch();
	void rotateYaw();
	void rotateRoll();

	void updateModelMatrix();

	float& getXrot();
	float& getYrot();
	float& getZrot();

private:
	std::string m_id;
	std::string m_modelID;

	glm::vec3 m_position;
	glm::vec3 m_rotation; // should be quaternion
	float m_scale;

	glm::mat4 m_modelMatrix;

	glm::quat m_orientation;

	float m_x = 0.0f, m_y = 0.0f, m_z = 0.0f;

	float x = 0.0f, y = 0.0f, z = 0.0f;

	glm::mat4 m_appliedTransform;
	//glm::quat xOri;
	//glm::quat yOri;
	//glm::quat zOri;

};
