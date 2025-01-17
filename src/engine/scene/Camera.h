#pragma once

#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT, 
	RIGHT
};

const float c_YAW =  -90.0f;
const float c_PITCH = 0.0f;
const float c_SPEED = 2.5f;
const float c_SENSITIVITY = 0.1f;
const float c_FOV = 45.0f;


//struct m_orientation {
//	glm::vec3 m_position;
//	glm::vec3 m_front;
//	glm::vec3 m_up;
//	glm::vec3 m_right;
//};

class Camera {
	public:
		Camera(glm::vec3 m_position = glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float m_yaw = c_YAW, float m_pitch = c_PITCH, float m_fov = c_FOV) ;

		mat4 getViewMatrix();

		void cameraMove(CameraMovement direction, float deltaTime);

		void cameraRotate(float xoffset, float yoffset, bool constrainPitch = true);

		void cameraZoom(float offsetY);

		inline glm::vec3& getCameraPos() { return m_position; };

	public:
		inline glm::vec3 getPos() { return m_position; };
		inline glm::vec3& getFront() { return m_front; };
		inline glm::vec3& getUp() { return m_up; };
		inline glm::vec3& getRight() { return m_right; };
		inline glm::vec3 getWorldUp() { return m_worldUp; };
		inline float getMovementSpeed() { return m_movementSpeed; };
		inline float& getFov() { return m_fov; };

		inline float& getOrthoZoom() { return m_orthoZoom; };

	private:
		void updateCameraVectors();

	private:
		vec3 m_position;
		vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
		vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		vec3 m_right;
		vec3 m_worldUp;
		// euler angles

		float m_yaw;
		float m_pitch;
		
		float m_mouseSensitivity;
		float m_movementSpeed;
		
		float m_fov;
		float m_orthoZoom = 1.0f;
};
