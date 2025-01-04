#pragma once

#include <string>
#include <vector>
#include <unordered_map> // TODO probably remove this
#include <optional>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

//#include <glm/vec2.hpp>
//#include <glm/vec3.hpp>

#include "scene/Mesh.h"
#include "src/engine/scene/Model.h"

#include "src/engine/scene/Scene.h"

//#include "src/engine/scene/TextureCache.h"
//#include "src/engine/scene/MaterialCache.h"
//#include "src/engine/scene/ModelCache.h"

#include "glm/matrix.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "src/engine/scene/Node.h"
#include "src/engine/scene/Animation.h"
#include "src/engine/scene/AnimMeshData.h"


class ModelLoader {

public:
	ModelLoader(TextureCache& textureCache, MaterialCache& materialCache, ModelCache& modelCache, Scene& scene);
	const aiScene* getScene(const std::string modelPath, bool isAnim);

	std::vector<Material> processMaterials(const aiScene& aiScene);
	std::vector<TextureData> processTextures(const aiScene& aiScene);

	std::optional<TextureData> getDiffuseTexture(const aiMaterial& aiMaterial);
	std::optional<TextureData> getNormalTexture(const aiMaterial& aiMaterial);

	glm::vec4 getAmbientColor(const aiMaterial& aiMaterial);
	glm::vec4 getDiffuseColor(const aiMaterial& aiMaterial);
	glm::vec4 getSpecularColor(const aiMaterial& aiMaterial);
	float getShininessStrength(const aiMaterial& aiMaterial);

private:
	std::optional<TextureData> getTexture(const aiMaterial& aiMaterial, const aiTextureType textureType);

	void loadModel(const aiScene& aiScene, bool isAnim);
	std::vector<Model> processModels(const aiScene& ai_scene, const bool isAnim, std::vector<Bone>& bones);
	//Mesh processMesh(const aiScene& aiScene, const aiMesh& aiMesh);

	// Hierarchy functions
	Node* buildNodesTree(const aiNode* aiNode, Node* parentNode);
	Node* buildSceneGraph(const aiScene* ai_scene, const aiNode* AiNode, Node* parentNode);

	// Animation functions
	std::vector<Animation> processAnimations(const aiScene& scene, const std::vector<Bone>& boneList, Node* rootNode, const glm::mat4& globalInverseTransformation);
	void processAnim(const aiScene& aiScene);
	std::unordered_map<std::string, Bone> storeBones(const aiScene& ai_scene);
	AnimaMeshData processBones(const aiMesh& aiMesh, std::vector<Bone>& bones);
	int calcAnimationMaxFrames(const aiAnimation& ai_Animation);
	glm::mat4 buildNodeTransformationMatrix(const aiNodeAnim& aiNodeAnim, int frame);
	void buildFrameMatrices(const aiAnimation& aiAnimation, const std::vector<Bone>& bones, AnimatedFrame& animatedFrame,
		int frame, Node* node, const glm::mat4& parentTransformation, const glm::mat4& globalInverseTransform);

	// Mesh functions
	MeshData processMeshData(aiMesh& aiMesh, std::vector<Bone>& bones, bool isAnim);
	std::vector<unsigned int> processIndices(const aiMesh& mesh);
	std::vector<float> processVertices(const aiMesh& aiMesh);
	std::vector<float> processTexCoords(const aiMesh& aiMesh);
	std::vector<float> processTangents(const aiMesh& aiMesh);
	std::vector<float> processBitangents(const aiMesh& aiMesh);
	std::vector<float> processNormals(const aiMesh& aiMesh);

	// Utility functions
	aiNodeAnim* findAIAnimNode(const aiAnimation& ai_Animtion, std::string nodeName);
	std::string getFileDirectory(std::string filePath);
	glm::mat4 toMatrix(const aiMatrix4x4& aiMatrix4x4);
	void printMetaData(const aiMetadata* metaData, bool isPrinting);


private:
	std::vector<Mesh> m_meshes;
	std::string m_directory;
	TextureCache& m_textureCache;
	MaterialCache& m_materialCache;
	ModelCache& m_modelCache;
	Scene& m_scene;
	std::unordered_map<std::string, Bone> m_bonesMap;


};

