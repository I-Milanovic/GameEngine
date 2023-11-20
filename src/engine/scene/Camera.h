#pragma once

#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT, 
	RIGHT
};

const float c_YAW = -90.f;
const float c_PITCH = 0.0f;
const float c_SPEED = 2.5f;
const float c_SENSITIVITY = 0.1f;
const float c_ZOOM = 45.0f;

class Camera {
	public:
		Camera(glm::vec3 position = glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float m_yaw = c_YAW, float m_pitch = c_PITCH) ;

		mat4 getViewMatrix();

		void cameraMove(CameraMovement direction, float deltaTime);

		void cameraRotate(float xoffset, float yoffset, bool constrainPitch = true);

		void cameraZoom(float offsetY);

		inline glm::vec3& getCameraPos() { return m_position; };

	public:
		inline vec3 getPos() { return m_position; };
		inline vec3 getFront() { return m_front; };
		inline vec3 getUp() { return m_up; };
		inline vec3 getRight() { return m_right; };
		inline vec3 getWorldUp() { return m_worldUp; };
		inline float getMovementSpeed() { return m_movementSpeed; };
		inline float getZoom() { return m_zoom; };

	private:
		void updateCameraVectors();

	private:
		vec3 m_position;
		vec3 m_front;
		vec3 m_up;
		vec3 m_right;
		vec3 m_worldUp;

		// euler angles

		float m_yaw;
		float m_pitch;
		float m_mouseSensitivity;
		float m_movementSpeed;
		float m_zoom;

};
