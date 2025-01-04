#pragma once

#include "CameraAbstract.h"
#include <glm/matrix.hpp>

class OrbitCamera : public CameraAbstract{

public:
	OrbitCamera(const glm::vec3 center, float radius, float minRadius, float azimuthAngle, float polarAngle);

	~OrbitCamera();

	void moveForward(const float by) override;
	void moveHorizontal(const float distance) override;
	void moveVertical(const float distance) override;

	void rotateYaw(const float radians) override;
	void rotatePitch(const float radians) override;
	void rotateRoll(const float radians) override;
	
	glm::vec3 getPosition() const override;
	glm::vec3 getForwardVector() const override;

	float getAngleYaw() const override;
	float getAnglePitch() const override;
	float getAngleRoll() const override;

	glm::mat4 getViewMatrix() const override;

	

private:
	glm::vec3 m_center;
	glm::vec3 m_upVector;
	float m_radius;
	float m_minRadius;
	float m_azimuthAngle;
	float m_polarAngle;

	glm::vec3 m_newRightVector;

};