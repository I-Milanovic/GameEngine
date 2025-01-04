#pragma once

#include <vector>
#include <string>

#include <glm/matrix.hpp>

class AnimaMeshData {

public:
	AnimaMeshData() = default;
	AnimaMeshData(std::vector<float> weights, std::vector<int> boneIds);

	std::vector<float> getWeights();
	std::vector<int> getBoneIds();

	bool hasAnimData();

private:
	//bool hasAnimData;
	std::vector<float> m_weigthts;
	std::vector<int> m_boneIds;
};

class Bone {
public:
	Bone(int boneId, std::string boneName, glm::mat4 offsetMatrix);

	int getBoneId();
	std::string getBoneName();
	glm::mat4 getOffsetMatrix();

private:
	int m_bonId;
	std::string m_boneName;		// maybe remove cuz it's kept in map as a key
	glm::mat4 m_offsetMatrix;
};

class VertexWeight {

public:
	VertexWeight(int boneId, int vertexId, float weight);

	int getBoneId();
	int getVertexId();
	float getWeight();

	bool operator < (VertexWeight& vertexWeight) const {
		return (m_vertexId < vertexWeight.getVertexId());
	}

private:
	int m_boneId;
	int m_vertexId;
	float m_weight;

};
