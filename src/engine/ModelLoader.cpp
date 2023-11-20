#include "ModelLoader.h"

#include "Texture.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <map>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>



void ModelLoader::loadModel(const std::string& path) {
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) { // if it not zero
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	// retreive the directory path fo the filepath
	m_directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recurively
	processNode(*scene->mRootNode, *scene);
} 

void ModelLoader::processNode(aiNode& node, const aiScene& scene) {
	for (unsigned int i = 0; i < node.mNumMeshes; i++) {
		// the node object only contains indices to index the actual objects in the scene.
		// the scene contains all the data, node is just to keep stuff organized (like relations between nods).
		aiMesh* mesh = scene.mMeshes[node.mMeshes[i]];
		m_meshes.push_back(processMesh(*mesh, scene));
		
	}
	// after we'veproces all of the meshese (if any) we then recurseively process each of the children nodes.
	for (unsigned int i = 0; i < node.mNumChildren; i++) {
		processNode(*node.mChildren[i], scene);
	}
}

Mesh ModelLoader::processMesh(aiMesh& mesh, const aiScene& scene) {
	// data to fill
	std::vector<Vertex> vertices = processVertices(mesh);
	std::vector<unsigned int> indices = processIndices(mesh);

	aiMaterial& material = *scene.mMaterials[mesh.mMaterialIndex];
	Material mat = processMaterial(material);
	std::vector<TextureS> textures = processTextures(mat, material);

	return Mesh(vertices, indices, textures, mat);
}

std::vector<Vertex> ModelLoader::processVertices(aiMesh& mesh) {
	std::vector<Vertex> vertices;
	// walk throug each fo the mesh's vertices
	for (unsigned int i = 0; i < mesh.mNumVertices; i++) {
		Vertex vertex;
		vertex.m_position = glm::vec3(mesh.mVertices[i].x, mesh.mVertices[i].y, mesh.mVertices[i].z);
		// normals
		if (mesh.HasNormals()) {
			vertex.m_normal = glm::vec3(mesh.mNormals[i].x, mesh.mNormals[i].y, mesh.mNormals[i].z);
		}

		// texture coordinates
		if (mesh.mTextureCoords[0]) {// check if mesh contains texture coordinates
			glm::vec2 vec(0.0f);
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vertex.m_texCoords = glm::vec2(mesh.mTextureCoords[0][i].x, mesh.mTextureCoords[0][i].y);
			// tangent
			vertex.m_tangent = glm::vec3(mesh.mTangents[i].x, mesh.mTangents[i].y, mesh.mTangents[i].z);
			// bitangent
			vertex.m_biTangent = glm::vec3(mesh.mBitangents[i].x, mesh.mBitangents[i].y, mesh.mBitangents[i].z);
		}
		else
			vertex.m_texCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	return vertices;
}

std::vector<unsigned int> ModelLoader::processIndices(const aiMesh& mesh) {
	std::vector<unsigned int> indices;

	// now walk throug each of the mesh's faces (a face is a mesh its triangles) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh.mNumFaces; i++) {
		aiFace face = mesh.mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return indices;
}

std::vector<TextureS> ModelLoader::processTextures(Material& mat, aiMaterial& material) {
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	std::vector<TextureS> textures;

// 1. diffuse maps
	std::vector<TextureS> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	// 1. specular maps
	std::vector<TextureS> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	// 1. normal maps
	std::vector<TextureS> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	// 1. height maps
	std::vector<TextureS> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object create from the extracting  mesh data
	if (diffuseMaps.empty() || textures.at(0).m_id == 0)
		mat.m_hasTextures = 0;
	else
		mat.m_hasTextures = 1;


	return textures;
}

Material ModelLoader::processMaterial(const aiMaterial& mat) {
	Material material;
	aiColor4D color(0.f, 0.f, 0.f, 0.0f);
//	float shininess;

	int result = aiGetMaterialColor(&mat, AI_MATKEY_COLOR_AMBIENT, &color);
	if (result == aiReturn_SUCCESS)
		material.m_ambient = glm::vec3(color.r, color.g, color.b);

	result = aiGetMaterialColor(&mat, AI_MATKEY_COLOR_DIFFUSE, &color);
	if (result == aiReturn_SUCCESS)
		material.m_diffuse = glm::vec3(color.r, color.g, color.b);

	result = aiGetMaterialColor(&mat, AI_MATKEY_COLOR_SPECULAR, &color);
	if (result == aiReturn_SUCCESS)
		material.m_specular = glm::vec3(color.r, color.g, color.b);

	unsigned int max = 1;

	float shininessStrength = 0.0f;
	result = aiGetMaterialFloatArray(&mat, AI_MATKEY_SHININESS_STRENGTH, &shininessStrength, &max);
	//if (result == aiReturn_SUCCESS)
		material.m_reflectance = shininessStrength;

	return material;
}

// checks all material textures of a given type and loads teh textures if thye're not loaded yet.
// the required info is returned as a Texture struct.
std::vector<TextureS> ModelLoader::loadMaterialTextures(aiMaterial& mat, aiTextureType type, std::string typeName) {
	std::vector<TextureS> textures;
	for (unsigned int i = 0; i < mat.GetTextureCount(type); i++) {
		aiString str;
		mat.GetTexture(type, i, &str);

//		std::cout << "FILE NAME : " << str.C_Str() << " DIRECTORY : " << this->m_directory << std::endl;
		// check if  texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (int j = 0; j < textures_loaded.size(); j++) {
			if (std::strcmp(textures_loaded[j].m_path.data(), str.C_Str()) == 0) {
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip) {
			// if texture hasn't been loaded alreayd, load it

			std::string filename = std::string(str.C_Str());
			filename = this->m_directory + '/' + filename;

			Texture tex;

			TextureS texture;
			texture.m_id = tex.generateTexture(filename);
			texture.m_type = typeName;
			texture.m_path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);	// store it as texture loaded for entire model, to endure we won't unnecessary load duplicate textures.




		}
	}
	return textures;
}