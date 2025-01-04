#include "MeshData.h"

MeshData::MeshData(const std::vector<float> positions, const std::vector<unsigned int> indices,
	const std::vector<float> texCoords, const std::vector<float> normals, const std::vector<float> tangents, 
	const std::vector<float> bitangents) : MeshData(positions, indices, texCoords, normals, tangents, bitangents, std::vector<int>(positions.size() * 4 / 3), std::vector<float>(positions.size() * 4 / 3)){}

MeshData::MeshData(const std::vector<float> positions, const std::vector<unsigned int> indices
	, const std::vector<float> texCoords, const std::vector<float> normals, const std::vector<float> tangents,
	const std::vector<float> bitangents, const std::vector<int> boneIndices, const std::vector<float> weights)
	: m_positions(positions), m_indices(indices), m_texCoords(texCoords), m_normals(normals)
	, m_tangents(tangents), m_bitangents(bitangents), m_boneIndices(boneIndices), m_weights(weights)
{}

 std::vector<float> MeshData::getPositions() {
	return m_positions;
}

 std::vector<unsigned int> MeshData::getIndices() {
	return m_indices;
}

 std::vector<float> MeshData::getTexCoords() {
	return m_texCoords;
}

std::vector<float> MeshData::getNormals() {
	return m_normals;
}

std::string MeshData::getMaterialName() {
	return m_materialName;
}

std::vector<float> MeshData::getTangents() {
	return m_tangents;
}

std::vector<float> MeshData::getBitangents() {
	return m_bitangents;
}

void MeshData::setMaterialName(const std::string materialName) {
	m_materialName = materialName;
}

std::string MeshData::getMeshName() const {
	return m_meshName;
}

void MeshData::setMeshName(std::string meshName) {
	m_meshName = meshName;
}

std::vector<int> MeshData::getBoneIndices() {
	return m_boneIndices;
}

std::vector<float> MeshData::getWeights() {
	return m_weights;
}

Material& MeshData::getMaterial() {
	return *m_material;
}

void MeshData::setMaterial(Material& material) {
	m_material = &material;
}
