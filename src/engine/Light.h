#pragma once
#include <glm/glm.hpp>

struct Attenuation {
	float constant;
	float linear;
	float exponent;
};

struct AmbientLight {
	float factor;
	glm::vec3 color;
};

struct PointLight {
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	Attenuation att;
};

struct SpotLight {
	PointLight pointLight;
	glm::vec3 coneDir;
	float cutOff;
};

struct DirLight {
	glm::vec3 color;
	glm::vec3 direction;
	float intensity;
};
