#include <iostream>
#include <glad/glad.h>

#include "UniformMap.h"
#include "../scene/lights/Light.h"


UniformMap::UniformMap(int programId) : m_programId(programId) {
}

void UniformMap::createUniform(const std::string &uniformName) {
	int uniformLocation = glGetUniformLocation(m_programId, uniformName.c_str());

	if (uniformLocation < 0) {
		// TODO better set exception than just print
		std::cout << "Could not find uniform " << uniformName << " in shader program " <<
			m_programId << std::endl;
	}
	else {
		std::cout << "Uniform created: " << uniformName << " at location: " << uniformLocation << std::endl;
		m_uniformMap[uniformName] = uniformLocation;
	}
}

int UniformMap::getUniformLocation(const std::string &uniformName) const{

	bool isContained = m_uniformMap.contains(uniformName);

	if(!isContained) 
		std::cout << "ERROR : Uniform not in List: " << uniformName << std::endl;

	int location = m_uniformMap.at(uniformName);

	if (location < 0) {
		// TODO set exception
		std::cout << "Could not find uniform: " << location << " " << uniformName << std::endl;
	}

	return location;
}

void UniformMap::setUniform(const std::string& uniformName, bool value) const {
	glUniform1i(getUniformLocation(uniformName), value);
}

void UniformMap::setUniform(const std::string& uniformName, int value) const {
	glUniform1i(getUniformLocation(uniformName), value);
}

void UniformMap::setUniform(const std::string& uniformName, float value) const {
	glUniform1f(getUniformLocation(uniformName), value);
}

void UniformMap::setUniform(const std::string& uniformName, glm::vec2 &value) const {
	glUniform2fv(getUniformLocation(uniformName), 1, &value[0]);
}

void UniformMap::setUniform(const std::string& uniformName, const glm::vec3 &value) const {
	glUniform3fv(getUniformLocation(uniformName), 1, &value[0]);
}

void UniformMap::setUniform(const std::string& uniformName, glm::vec4 &value) const {
	glUniform4fv(getUniformLocation(uniformName), 1, &value[0]);
}

void UniformMap::setUniform(const std::string& uniformName, glm::mat2 &value) const {
	glUniformMatrix2fv(getUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void UniformMap::setUniform(const std::string& uniformName, glm::mat3 &value) const {
	glUniformMatrix3fv(getUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void UniformMap::setUniform(const std::string& uniformName, glm::mat4 &value) const {
	glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void UniformMap::createAttenuation(const std::string& uniformName) {
	createUniform(uniformName + ".constant");
	createUniform(uniformName + ".linear");
	createUniform(uniformName + ".exponent");
}

void UniformMap::createMaterial(const std::string& uniformName) {
	createUniform(uniformName + ".ambient");
	createUniform(uniformName + ".diffuse");
	createUniform(uniformName + ".specular");
	createUniform(uniformName + ".reflectance");
}

void UniformMap::createAmbientLight(const std::string& uniformName) {
	createUniform(uniformName + ".factor");
	createUniform(uniformName + ".color");
}

void UniformMap::createPointLightUniform(const std::string& uniformName) {
	createUniform(uniformName + ".position");
	createUniform(uniformName + ".color");
	createUniform(uniformName + ".intensity");
	createAttenuation(uniformName + ".att");
}

void UniformMap::createDirLightUniform(const std::string& uniformName) {
	createUniform(uniformName + ".color");
	createUniform(uniformName + ".direction");
	createUniform(uniformName + ".intensity");

}

void UniformMap::createSpotLightUniform(const std::string& uniformName) {
	createPointLightUniform(uniformName + ".pointLight");
	createUniform(uniformName + ".coneDir");
	createUniform(uniformName + ".cutOff");
	
}

void UniformMap::createPointLightListUniform(const std::string& uniformName, unsigned int size) {
	for (unsigned int i = 0; i < size; i++) {
		std::string count = std::to_string(i);
		createPointLightUniform(uniformName + "[" + count + "]");
	}
}

void UniformMap::createDirLightListUniform(const std::string& uniformName, unsigned int size) {
	for (unsigned int i = 0; i < size; i++) {
		std::string count = std::to_string(i);
		createDirLightUniform(uniformName + "[" + count + "]");
	}
}

void UniformMap::createSpotLightListUniform(const std::string& uniformName, unsigned int size) {
	for (unsigned int i = 0; i < size; i++) {
		std::string count = std::to_string(i);
		createSpotLightUniform(uniformName + "[" + count + "]");
	}
}

void UniformMap::setAttenuationUniform(const std::string& uniformName, Attenuation attenuation) {
	setUniform(uniformName + ".constant", attenuation.m_constant);
	setUniform(uniformName + ".linear", attenuation.m_linear);
	setUniform(uniformName + ".exponent", attenuation.m_exponent);
}

void UniformMap::setMaterialUniform(const std::string& uniformName, Material material) {
	setUniform(uniformName + ".ambient", material.m_ambient);
	setUniform(uniformName + ".diffuse", material.m_diffuse);
	setUniform(uniformName + ".specular", material.m_specular);
	setUniform(uniformName + ".reflectance", material.m_reflectance);
}

void UniformMap::setAmbientLight(const std::string& uniformName, AmbientLight ambientLight) {
	setUniform(uniformName + ".factor", ambientLight.m_factor);
	setUniform(uniformName + ".color", ambientLight.m_color);
}

void UniformMap::setPointLightUniform(const std::string& uniformName, PointLight pointLight) {
	setUniform(uniformName + ".position", pointLight.m_position);
	setUniform(uniformName + ".color", pointLight.m_color);
	setUniform(uniformName + ".intensity", pointLight.m_intensity);
	setAttenuationUniform(uniformName + ".att", pointLight.m_att);
}

void UniformMap::setDirLightUniform(const std::string& uniformName, DirLight dirLight) {
	setUniform(uniformName + ".color", dirLight.m_color);
	setUniform(uniformName + ".direction", dirLight.m_direction);
	setUniform(uniformName + ".intensity", dirLight.m_intensity);
}

void UniformMap::setSpotLightUniform(const std::string& uniformName, SpotLight spotLight) {
	setPointLightUniform(uniformName + ".pointLight", spotLight.m_pointLight);
	setUniform(uniformName + ".coneDir", spotLight.m_coneDir);
	setUniform(uniformName + ".cutOff", spotLight.m_cutOff);
}

void UniformMap::setPointLightListUniform(const std::string& uniformName, std::vector<PointLight> pointLights) {
	for (int i = 0; i < pointLights.size(); i++) {
		std::string count = std::to_string(i);
		setPointLightUniform(uniformName + "[" + count + "]", pointLights[i]);
	}
}
void UniformMap::setDirLightListUniform(const std::string& uniformName, std::vector<DirLight> dirLights) {
	for (int i = 0; i < dirLights.size(); i++) {
		std::string count = std::to_string(i);
		setDirLightUniform(uniformName + "[" + count + "]", dirLights[i]);
	}
}
void UniformMap::setSpotLightListUniform(const std::string& uniformName, std::vector<SpotLight> spotLights) {
	for (int i = 0; i < spotLights.size(); i++) {
		std::string count = std::to_string(i);
		setSpotLightUniform(uniformName + "[" + count + "]", spotLights[i]);
	}
}