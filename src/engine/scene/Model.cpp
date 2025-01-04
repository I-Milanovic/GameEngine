#include "Model.h"

Model::Model(const std::string modelName, MeshData meshData)
	: m_modelName(modelName), m_meshData(meshData), m_entity({"1", "1"}), m_mesh(meshData) {}


// ---------- Getters ----------

std::string Model::getModelName() {
	return m_modelName;
}

AnimationManager& Model::getAnimationManager() {
	return m_animationManager;
}

Mesh& Model::getMesh() {
	return m_mesh;
}

MeshData Model::getMeshData() {
	return m_meshData;
}

Entity& Model::getEntity() {
	return m_entity;
}

// ---------- Setters ----------

void Model::setModelName(std::string modelName) {
	m_modelName = modelName;
}


