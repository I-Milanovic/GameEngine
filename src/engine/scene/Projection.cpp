#include "Projection.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Projection::Projection(float fov, int width, int height, float zFar, float zNear) 
	: m_fov(fov), m_width(width), m_height(height), m_zFar(zFar), m_zNear(zNear),
	m_projectionMatrix(glm::perspective(glm::radians(m_fov), (float)m_width / (float)(m_height), m_zNear, m_zFar)),
	m_orthoMatrix(glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, 0.1f, 10.0f)) {
}

void Projection::updateProjection() {
	//std::cout << m_fov << std::endl;
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), (float)m_width / (float)(m_height), m_zNear, m_zFar);
}

void Projection::updateOrtho() {	

	float ratio = static_cast<float>(m_width) / static_cast<float>(m_height);
	float zoom = 0.001;
	float orthoWidth = m_width * (orthoSize * zoom);
	float orthoHeight = m_height * (orthoSize * zoom);

	m_orthoMatrix = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, 0.1f, 10.0f);
}
