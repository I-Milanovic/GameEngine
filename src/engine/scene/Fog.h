#pragma once
#include <glm/glm.hpp>

struct Fog {
	bool isActive = false;
	glm::vec3 color = glm::vec3(0.5f);
	float density = 0.15f;
};