#pragma once

#include <string>
#include <vector>
#include <assimp/scene.h>

#include "scene/Mesh.h"

class ModelLoader {

	public:
		ModelLoader() = default;
		void loadModel(const std::string& path);
		inline std::vector<Mesh> getMeshes() { return m_meshes; };

	private:
		void processNode(aiNode& node, const aiScene& scene);
		Mesh processMesh(aiMesh& mesh, const aiScene& scene);
		std::vector<TextureS> loadMaterialTextures(aiMaterial& mat, aiTextureType type, std::string typename);
	//	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
		Material processMaterial(const aiMaterial& mat);
		std::vector<Vertex> processVertices(aiMesh& mesh);
		std::vector<unsigned int> processIndices(const aiMesh& mesh);
		std::vector<TextureS> processTextures(Material& mat, aiMaterial& material);

	private:
		std::vector<TextureS> textures_loaded;
		std::vector<Mesh> m_meshes;
		std::string m_directory;
};

