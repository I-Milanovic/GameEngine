#pragma once

#include <glm/vec4.hpp>
#include <string>


#include "Texture.h"

struct Material {

public:
	Material(std::string materialName);
	glm::vec4 getAmbientColor();
	glm::vec4 getDiffuseColor();
	std::string getMaterialName();

	std::string getNormalMapPath();
	float getReflectance();
	glm::vec4 getSpecularColor();
	std::string getTexturePath();

	void setAmbientColor(const glm::vec4 ambientColor);
	void setDiffuseColor(const glm::vec4 diffuseColor);
	void setMaterialName(const std::string materialName);

	void setNormaMapPath(const std::string path);
	void setReflectance(const float reflectance);
	void setSpecularColor(const glm::vec4 specularColor);
	void setTexturePath(const std::string path);

	bool hasTexture();
	bool hasNormalTexture();

public:
	const static glm::vec4 s_defaultColor;

private:
	glm::vec4 m_ambientColor;
	glm::vec4 m_diffuseColor;
	glm::vec4 m_specularColor;
	std::string m_materialName;
	std::string m_normalMapPath; //TODO maybe change to name instead of path
	std::string m_texturePath;
	float m_reflectance;		// shininess factor
};
