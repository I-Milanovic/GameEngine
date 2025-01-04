#pragma once

#include <string>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <src/engine/scene/Material.h>

// (SoA) structure of arrays
struct MeshData {

public:
	//MeshData(const std::vector<float> positions, const std::vector <unsigned int> indices,
	//	const std::vector <float> texCoords, const std::vector <float> normals, const std::vector <float> tangents, const std::vector <float> bitangents);
	
	//MeshData(const std::vector<float> positions, const std::vector <unsigned int> indices,
	//	const std::vector <float> texCoords, const std::vector <float> normals, const std::vector <float> tangents, const std::vector <float> bitangents,
	//	std::vector<int> boneIndices, std::vector<float> weights);

	std::string m_meshName;
	std::vector<float> m_positions;
	std::vector<unsigned int> m_indices;
	std::vector<float> m_texCoords;
	std::vector<float> m_normals;

	std::vector<float> m_tangents;
	std::vector<float> m_bitangents;
	std::string m_materialName;

	std::vector<int> m_boneIndices;
	std::vector<float> m_weights;
	
	//glm::vec3 aabbMax;
	//glm::vec3 aabbMin;



//private:
//	Material* m_material;
//

};

