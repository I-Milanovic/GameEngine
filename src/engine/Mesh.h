#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_texCoords;
	glm::vec3 m_tangent;
	glm::vec3 m_biTangent;

	int m_boneIds[MAX_BONE_INFLUENCE];
	float m_weights[MAX_BONE_INFLUENCE];
};

struct TextureS {
	unsigned int m_id;
	std::string m_type;
	std::string m_path;
};


struct Material {
private:
	glm::vec4 defaultColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
public:
	glm::vec4 m_ambient = defaultColor;
	glm::vec4 m_diffuse = defaultColor;
	glm::vec4 m_specular = defaultColor;
	float m_reflectance; // what did they call for this in aiMaterial
	float m_shininess;
	int m_hasTextures;
};

class Mesh {

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureS> textures, Material material);
//	Mesh(const Mesh &m);
	void cleanup();
	inline unsigned int getVao() { return vao; };
	inline unsigned int getIndicesSize() { return static_cast<unsigned int> (m_indices.size()); };

	inline int getTextureId(unsigned int index) { return m_textures.at(index).m_id; };
	inline void setTextureId(const unsigned int index, const int textureId) { m_textures.at(index).m_id = textureId; };
	inline std::vector<Vertex> getVertex() { return m_vertices; };
	inline Material getMaterial() { return m_material; };
	inline void setMaterial(Material material) { m_material = material; };

	inline glm::mat4& getModelMatrix() { return m_modelMatrix; };

private:
	void setupMesh();


private:
	// mesh data
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<TextureS> m_textures;
	Material m_material;
	glm::mat4 m_modelMatrix = glm::mat4(1.0f);;

	unsigned int vbo, vao, ebo;
};