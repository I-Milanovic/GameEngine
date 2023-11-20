#include "Projection.h"

#include <glm/gtc/matrix_transform.hpp>



Projection::Projection(float fov, int width, int height, float zFar, float zNear) 
	: m_fov(fov), m_width(width), m_height(height), m_zFar(zFar), m_zNear(zNear),
	m_projectionMatrix(glm::perspective(glm::radians(m_fov), (float)m_width / (float)(m_height), m_zNear, m_zFar)){

}

void Projection::updateProjection() {
	//if ((m_width != lastx) && (m_height != lasty)) {
	//	std::cout << m_width << "   " << m_height << std::endl;
	//	lastx = m_width;
	//	lasty = m_height;
	//}
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), (float)m_width / (float)(m_height), m_zNear, m_zFar);
}
