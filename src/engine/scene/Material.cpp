#include "Material.h"


const glm::vec4 Material::s_defaultColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

// TODO this whole class is complete shite
Material::Material(std::string materialName) 
	: m_materialName(materialName),
	m_ambientColor(s_defaultColor),
	m_diffuseColor(s_defaultColor),
	m_specularColor(s_defaultColor),
	m_reflectance(0.0f)
	{}

glm::vec4 Material::getAmbientColor() {
	return m_ambientColor;
}

glm::vec4 Material::getDiffuseColor() {
	return m_diffuseColor;
}

std::string Material::getMaterialName() {
	return m_materialName;
}

std::string Material::getNormalMapPath() {
	return m_normalMapPath;
}

float Material::getReflectance() {
	return m_reflectance;
}

glm::vec4 Material::getSpecularColor() {
	return m_specularColor;
}

std::string Material::getTexturePath() {
	return m_texturePath;
}

void Material::setAmbientColor(const glm::vec4 ambientColor) {
	m_ambientColor = ambientColor;
}

void Material::setDiffuseColor(const glm::vec4 diffuseColor) {
	m_diffuseColor = diffuseColor;
}

void Material::setMaterialName(const std::string materialName) {
	m_materialName = materialName;
}

void Material::setNormaMapPath(const std::string path) {
	m_normalMapPath = path;
}

void Material::setReflectance(const float reflectance) {
	m_reflectance = reflectance;
}

void Material::setSpecularColor(const glm::vec4 specularColor) {
	m_specularColor = specularColor;
}

void Material::setTexturePath(const std::string path) {
	m_texturePath = path;
}

bool Material::hasNormalTexture() {
	return !m_normalMapPath.empty();
}

bool Material::hasTexture() {
	return !m_texturePath.empty();
}
