#include "QuatCamera.h"

#include <iostream>

//#include <glm/matrix.hpp>

QuatCamera::QuatCamera(glm::vec3 pos) : position(pos) {
	updateViewMatrix();
	

	//up = glm::normalize(up + glm::vec3(1.0f, 1.0f, 0.0f));
	////std::cout << up.x << " " << up.y << " " << up.z << std::endl;

	
}

void QuatCamera::replace() {

}

void  QuatCamera::updateViewMatrix() {

	translate = glm::mat4(1.0f);
	translate = glm::translate(translate, position);

	
	//glm::vec3 point = glm::vec3(position.x, 0.0f, 0.0f);
	//glm::mat4 t1 = glm::translate(glm::mat4(1.0f), -point);
	//glm::mat4 rotationMatrix = glm::mat4_cast(orientation);
	//glm::mat4 t2 = glm::translate(glm::mat4(1.0f), point);	
	//viewMat = translate * t2 * rotationMatrix * t1;


	viewMat = translate * glm::mat4_cast(orientation);
}

void QuatCamera::rotation() {

	glm::quat qPitch = glm::angleAxis(pitch, right);
	glm::quat qYaw = glm::angleAxis(yaw,  up);
	orientation = glm::normalize(qPitch * qYaw);

	updateViewMatrix();
}


void QuatCamera::cameraMove(float offsetX, float offsetY, float deltaTime) {

//	glm::quat invOrient = glm::conjugate(orientation);
	

	//std::cout << offsetX << " " << offsetY << std::endl;

	glm::vec3 worldOffset;
	if (offsetY >= 1) {
		position += glm::vec3(0.0f, 1.0f, 0.0f) * 0.01f;
		
		updateOrientation();
	}
	if (offsetY <= -1) {
		position -= glm::vec3(0.0f, 1.0f, 0.0f) * 0.01f;
		updateOrientation();
	}
	if (offsetX >= 1) {
		position += glm::vec3(1.0f, 0.0f, 0.0f) * 0.01f;
		updateOrientation();
	}
	if (offsetX <= -1) {
		position -= glm::vec3(1.0f, 0.0f, 0.0f) * 0.01f;
		updateOrientation();
	}

	updateViewMatrix();
}


void QuatCamera::updateOrientation() {
//	 zapisi ovo leba ti

	//float p = glm::degrees(glm::pitch(orientation));
	//float y = glm::degrees(glm::yaw(orientation));;

	//glm::vec3 ax = glm::axis(orientation);
	//

	////float angle = glm::acos(glm::dot(glm::normalize(position), ax));

	////float diff = 90.0f - glm::degrees(angle);
	//std::cout << p << " " << y << std::endl;









}