#include "AnimMeshData.h"

AnimaMeshData::AnimaMeshData(std::vector<float> weights, std::vector<int> boneIds) 
	: m_weigthts(weights), m_boneIds(boneIds){}

std::vector<float> AnimaMeshData::getWeights(){
	return m_weigthts;
}

std::vector<int> AnimaMeshData::getBoneIds() {
	return m_boneIds;
}

bool AnimaMeshData::hasAnimData() {
	//hasAnimData = m_weigthts.size() > 0 && m_boneIds.size() > 0;
	return m_weigthts.size() > 0 && m_boneIds.size() > 0;
}

Bone::Bone(int boneId, std::string boneName, glm::mat4 offsetMatrix) 
	: m_bonId(boneId), m_boneName(boneName), m_offsetMatrix(offsetMatrix){}

int Bone::getBoneId() {
	return m_bonId;
}

std::string Bone::getBoneName() {
	return m_boneName;
}

glm::mat4 Bone::getOffsetMatrix() {
	return m_offsetMatrix;
}

VertexWeight::VertexWeight(int boneId, int vertexId, float weight)
	: m_boneId(boneId), m_vertexId(vertexId), m_weight(weight){}

int VertexWeight::getBoneId() {
	return m_boneId;
}

int VertexWeight::getVertexId() {
	return m_vertexId;
}

float VertexWeight::getWeight() {
	return m_weight;
}
