#pragma once

#include <glm/mat4x4.hpp>

#include <iostream>

class CameraAbstract {

public:
	virtual inline ~CameraAbstract() { std::cout << "abs camera" << std::endl; };

	virtual void moveForward(const float distance) = 0;
	virtual void moveHorizontal(const float distance) = 0;
	virtual void moveVertical(const float distance) = 0;

	virtual void rotateYaw(const float radians) = 0;
	virtual void rotatePitch(const float radians) = 0;
	virtual void rotateRoll(const float radians) = 0;

public:
	virtual glm::vec3 getPosition() const = 0;
	virtual glm::vec3 getForwardVector() const = 0;

	virtual float getAngleYaw() const = 0;
	virtual float getAnglePitch() const = 0;
	virtual float getAngleRoll() const = 0;

	virtual glm::mat4 getViewMatrix() const = 0;

};