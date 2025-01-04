#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "MeshData.h"

#define MAX_BONE_INFLUENCE 4

//struct Vertex {
//	glm::vec3 m_position;
//	glm::vec3 m_normal;
//	glm::vec2 m_texCoords;
//	glm::vec3 m_tangent;
//	glm::vec3 m_biTangent;
//
//	int m_boneIds[MAX_BONE_INFLUENCE];
//	float m_weights[MAX_BONE_INFLUENCE];
//};

//struct TextureS {
//	unsigned int m_id;
//	std::string m_type;
//	std::string m_path;
//};


//struct Material {
//private:
//	glm::vec4 defaultColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
//public:
//	glm::vec4 m_ambient = defaultColor;
//	glm::vec4 m_diffuse = defaultColor;
//	glm::vec4 m_specular = defaultColor;
//	float m_reflectance; // what did they call for this in aiMaterial
//	float m_shininess;
//	int m_hasTextures;
//};

class Mesh {

public:
	Mesh(MeshData meshData);
	void cleanup();
	inline unsigned int getVao() { return vao; };
	inline glm::mat4& getModelMatrix() { return m_modelMatrix; };

	MeshData& getMeshData();

private:
	unsigned int vao;
	unsigned int vbo;
	bool isRendered = true;
	glm::mat4 m_modelMatrix = glm::mat4(1.0f);		// TODO delete model matrix from here!!!???
	std::vector<unsigned int> vbObjects;
	MeshData m_meshData;
};