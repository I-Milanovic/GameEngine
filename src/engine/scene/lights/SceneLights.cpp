#include "SceneLights.h"

#include <iostream>
void SceneLights::addPointLights(std::vector<PointLight> pointLights) {
	m_pointLights = pointLights; 
}

void SceneLights::addPointLight(PointLight pointLight) { 
	m_pointLights.push_back(pointLight); 
}

void SceneLights::removePointLight(int index) {
	PointLight& p = m_pointLights.at(index);
	p.m_color = glm::vec3(0.0f);
	p.m_intensity = 0.0f;


	//m_pointLights.erase(m_pointLights.begin() + index);
}

void SceneLights::addSpotLights(std::vector<SpotLight> spotLights) { 
	m_spotLights = spotLights; 
}

void SceneLights::addSpotLight(SpotLight spotLight) {
	m_spotLights.push_back(spotLight);
}

void SceneLights::removeSpotLight(int index) {
	m_spotLights.erase(m_spotLights.begin() + index);
}

void SceneLights::setAmbientLight(AmbientLight& ambientLight) { m_ambientLight = ambientLight; }
void SceneLights::setDirLight(DirLight dirLight) { m_dirLight = dirLight; }

