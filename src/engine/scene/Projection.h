#pragma once

#include <glm/glm.hpp>

class Projection {
	public:
		Projection(float fov, int width, int height, float zFar = 100.0f, float zNear = 0.1f);
		void updateProjection();
		inline glm::mat4 getProjectionMatrix() { return m_projectionMatrix; };
		inline void setRatio(int width, int height) {
			m_width = width; m_height = height;		
		};

	private:
		float m_fov;
		int m_width, m_height;
		float m_zFar, m_zNear;
		glm::mat4 m_projectionMatrix;

		//int lastx, lasty;

};