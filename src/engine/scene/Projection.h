#pragma once

#include <glm/glm.hpp>

class Projection {
	public:
		Projection(float& fov, int width, int height, float zFar = 100.0f, float zNear = 0.1f);
		void updateProjection();	
		void updateOrtho();

		inline glm::mat4 getProjectionMatrix() { return m_projectionMatrix; };
		inline glm::mat4 getOrthoMatrix() { return m_orthoMatrix; };
		inline void setRatio(int width, int height) { m_width = width; m_height = height; };

		inline void setProjFov(float fov) { m_fov = fov; };

		inline void setOrthoSize(float size) { orthoSize = size; };
		inline float& getOrthoSize() { return orthoSize; };

	private:
		float m_fov;
		int m_width, m_height;
		float m_zFar, m_zNear;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_orthoMatrix;
		float orthoSize = 1.0f;

};