#pragma once

#include <glm/vec4.hpp>
#include <string>

struct MaterialT {

	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	int materialIdx;
	std::string normalMapPath;
	float reflectance;
	glm::vec4 specularColor;
	std::string texturePath;

};
