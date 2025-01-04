#pragma once

#include <string>
#include <vector>

#include "glm/matrix.hpp"


struct AnimatedFrame {
	std::vector<glm::mat4> m_boneMatrices;
};

struct Animation {

	Animation() = default;
	Animation(std::string name, double duration, std::vector<AnimatedFrame> frames)
		: m_name(name), m_duration(duration), m_frames(frames) {};

	std::string m_name;
	double m_duration{ 0.0 };
	std::vector<AnimatedFrame> m_frames;
};