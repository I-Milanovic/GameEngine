#pragma once
#include <glm/glm.hpp>

// Subject to change excpet m_constant, it is always equal to 1.0
struct Attenuation {
	float m_constant = 1.0f;
	float m_linear = 0.09f;
	float m_exponent = 0.032f;
};

struct AmbientLight {
	float m_factor = 1.0f;
	glm::vec3 m_color = glm::vec3(1.0f, 1.0f, 1.0f);
};

struct DirLight {
	glm::vec3 m_color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_intensity = 0.0f;
};

struct PointLight {
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_color = glm::vec3(1.0f, 1.0f, 1.0f);
	float m_intensity = 1.0f;
	Attenuation m_att;
};

struct SpotLight {
	PointLight m_pointLight;
	glm::vec3 m_coneDir = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_cutOff = 1.0f;
};

