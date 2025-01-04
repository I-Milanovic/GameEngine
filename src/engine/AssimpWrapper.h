#pragma once

// Utility includes
#include <vector>
#include <unordered_map>
//Assimp includes
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

// My includes
#include "scene/Mesh.h"
#include "src/engine/scene/Model.h"
#include "src/engine/scene/Animation.h"
#include "src/engine/scene/AnimMeshData.h"


// Remove includes
#include <optional>
#include <src/engine/scene/Node.h>
#include <set>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

class AssimpWrapper{

public:
	//AssimpWrapper(const AssimpWrapper& assimpWrapper) = delete;

	void initLoader(const std::string modelpath);
	void flush();
	std::vector<Model> loadModel();
	std::vector<Material> processMaterials();
	std::vector<TextureData> processTextures();
	std::vector<Animation> parseAnimations();
	Node* createGraph();
	void printSceneInfo();
	void printBones();
private:
	// ---------- Mesh functions ----------

	MeshData processMeshData(const aiMesh& aiMesh);
	std::vector<unsigned int> processIndices(const aiMesh& mesh);
	std::vector<float> processVertices(const aiMesh& aiMesh);
	std::vector<float> processTexCoords(const aiMesh& aiMesh);
	std::vector<float> processTangents(const aiMesh& aiMesh);
	std::vector<float> processBitangents(const aiMesh& aiMesh);
	std::vector<float> processNormals(const aiMesh& aiMesh);
	
	// ---------- Material functions ----------

	glm::vec4 getAmbientColor(const aiMaterial& aiMaterial);
	glm::vec4 getDiffuseColor(const aiMaterial& aiMaterial);
	glm::vec4 getSpecularColor(const aiMaterial& aiMaterial);
	float getShininessStrength(const aiMaterial& aiMaterial);
	std::optional<TextureData> getTexture(const aiMaterial& aiMaterial, const aiTextureType textureType);
	std::optional<TextureData> getDiffuseTexture(const aiMaterial& aiMaterial);
	std::optional<TextureData> getNormalTexture(const aiMaterial& aiMaterial);

	// ---------- Animation functions ----------

	AnimaMeshData parseBones(const aiMesh* aiMesh);
	std::vector<AnimatedFrame> parseSingleAnimation(const aiAnimation* aiAnimation, Node* rootNode, const glm::mat4& globalInverseTransform);
	int getAnimMaxFrames(const aiAnimation* aiAnimation);
	void buildFrameMatrices(const aiAnimation* aiAnimation, Node* node, int frame,
		const glm::mat4& parentTransformation, const glm::mat4& globalInverseTransform, AnimatedFrame& animatedFrame);
	aiNodeAnim* findAiAnimNode(const aiAnimation* aiAnimation, std::string nodeName);
	glm::mat4 buildPositionMatrix(const aiNodeAnim* aiNodeAnim, int frame);
	glm::mat4 buildRotationMatrix(const aiNodeAnim* aiNodeAnim, int frame);
	glm::mat4 buildScalingMatrix(const aiNodeAnim* aiNodeAnim, int frame);

	// ---------- Utility functions ----------

	Node* buildNodesTree(const aiNode* ai_Node, Node* parentNode);
	Node* buildSceneGraph(const aiNode* ai_node, Node* parentNode);
	glm::mat4 toMatrix(const aiMatrix4x4& aiMatrix4x4);
	std::string getFileDirectory(std::string filePath);

	// ---------- Printing functions ----------

	void printBoneInfo(const aiMesh* aiMesh, std::set<std::string>& uniqueBones);
	void printMetaData(const aiMetadata* metaData);

public:
	bool m_isAnim;	// TODO delete later

private:
	Assimp::Importer m_importer;
	std::string m_directory; // TODO can it be passed as arg?
	const aiScene* m_aiScene;	// TODO might fuck me later cuz of global const, maybe put it in function

	std::unordered_map<std::string, Bone> m_nameToBoneMap;
};

