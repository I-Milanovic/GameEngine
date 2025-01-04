#include "ModelLoader.h"

#include "src/engine/scene/Texture.h"

#include <fstream>
#include <sstream>
#include <iostream>


#include <map>

#include <stdio.h>


#include "src/engine/scene/MeshData.h"

// check for needing
#include "algorithm"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>


ModelLoader::ModelLoader(TextureCache& textureCache, MaterialCache& materialCache, ModelCache& modelCache, Scene& scene) // TODO scene graph
	:m_textureCache (textureCache), m_materialCache(materialCache), m_modelCache(modelCache), m_scene(scene)
{}
//  TODO get global up from matadata and apply to model
const aiScene* ModelLoader::getScene(const std::string modelPath, bool isAnim) {
	// read file via ASSIMP
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
		aiProcess_JoinIdenticalVertices | /* aiProcess_FixInfacingNormals |*/
		aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_LimitBoneWeights | (isAnim ? 0 : aiProcess_PreTransformVertices) );

	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return scene;
	}
	m_directory = getFileDirectory(modelPath);	// setDirectory where files may be found when loading
	loadModel(*scene, isAnim);
	//aiReleaseImport(scene);	//TOOD put after the scene has been returned
	return scene;
}

void ModelLoader::loadModel(const aiScene& aiScene, bool isAnim) {
	std::vector<Bone> bones;

	// process Materials
	if (aiScene.HasMaterials()) {
		m_materialCache.addMaterials(processMaterials(aiScene));
	}

//	if (aiScene.HasTextures())
		m_textureCache.addTextures(processTextures(aiScene));
	

	if (aiScene.HasMeshes()) {
		// store bones for graph use

		// Populate scene graph nodes
		m_modelCache.addModels(processModels(aiScene, isAnim, bones)); // selection wont work if this is after call to create scene graph
		m_scene.getSceneGraph().setRootNode(buildSceneGraph(&aiScene, aiScene.mRootNode, nullptr)); // todo uncomment // visual graph

	}

	std::vector<Animation> animations;
	int numAnimations = aiScene.mNumAnimations;
	if (aiScene.HasAnimations()) {

		aiNode* aiRootNode = aiScene.mRootNode;

		Node* rootNode = buildNodesTree(aiScene.mRootNode, nullptr);
		glm::mat4 globalInverseTransformation = glm::inverse(toMatrix(aiScene.mRootNode->mTransformation));

		animations = processAnimations(aiScene, bones, rootNode, globalInverseTransformation);

	}
	//if(isAnim)
		//m_scene.getModelCache().getModel("CharacterMesh-Anim")->addAnimation(animations.at(0));
	//int size = m_scene.getModelCache().getModel("CharacterMesh-Anim")->getAnimations().size();
	//for (auto& model : *m_scene.getModelCache().getModels()) {
	//	std::cout << model.first << std::endl;
	//}

}

Node* ModelLoader::buildSceneGraph(const aiScene* ai_scene, const aiNode* ai_node, Node* parentNode) {
	std::string nodeName = ai_node->mName.data;
	int numChildren = ai_node->mNumChildren;
	glm::mat4 transformation = toMatrix(ai_node->mTransformation);


	std::unordered_map<std::string, Bone> m_bonesMap = storeBones(*ai_scene);

	Node* node = nullptr;
	if (m_bonesMap.contains(nodeName)) {
		node = new Node(nodeName, parentNode, transformation, DataType::bone);
	}

	else {
		node = new Node(nodeName, parentNode, transformation, DataType::model);
	}

	printMetaData(ai_node->mMetaData, false);

	unsigned int meshSize = ai_node->mNumMeshes;
	for (int i = 0; i < meshSize; i++) {
		// Mesh
		unsigned int meshIndex = ai_node->mMeshes[i]; // index of this mesh in aiScene array
		aiMesh* mesh = ai_scene->mMeshes[meshIndex];
		std::string meshName = mesh->mName.C_Str();
		unsigned int matIndex = mesh->mMaterialIndex;

		// set data to my mesh node
		Node* meshNode = new Node(meshName, node, transformation, DataType::mesh);
		meshNode->setData(m_modelCache.getModel(meshName));
		node->setData(m_modelCache.getModel(meshName));

		// Material
		aiMaterial* material = ai_scene->mMaterials[matIndex];
		std::string materialName = material->GetName().C_Str();
		Node* materialNode = new Node(materialName, meshNode, transformation, DataType::material);	// TODO set material node to point to a node in material cache 
		materialNode->setData(&m_materialCache.getMaterial(materialName));			// prvo ucitaj u cache i onda nek samo odatle povuce potrebne informacije a ne iz aiScene

	}
	for (int i = 0; i < numChildren; i++) {
		aiNode* aiChildNode = ai_node->mChildren[i];
		Node* childNode = buildSceneGraph(ai_scene, aiChildNode, node);
	}
	
	return node;
}

std::vector<Model> ModelLoader::processModels(const aiScene& ai_scene, const bool isAnim, std::vector<Bone>& bones) {
	std::vector<Model> models;



	printMetaData(ai_scene.mMetaData, false);

	// process Models
	unsigned int numMeshes = ai_scene.mNumMeshes;
	std::cout << "Number of Meshes: " << numMeshes << std::endl;
	for (int i = 0; i < numMeshes; i++) {
	
		aiMesh* ai_Mesh = ai_scene.mMeshes[i];
		std::string modelName = ai_Mesh->mName.C_Str();
		std::string materialName = ai_scene.mMaterials[ai_Mesh->mMaterialIndex]->GetName().C_Str();		// long boi

		// TODO too much shit down here 
		MeshData meshData = processMeshData(*ai_Mesh, bones, isAnim);
		meshData.setMaterial(m_materialCache.getMaterial(materialName));		// TODO put it in a constructor or something else
		// TODO animations as argument
		Model model(modelName, meshData);
		models.emplace_back(model);
		m_modelCache.addModel(model);
	}

	return models;
}

//// aiScene in fucntion shouldnt be used to retrieve all just data values for the appropriate object
//Mesh ModelLoader::processMesh(const aiScene& aiScene, const aiMesh& aiMesh) {
//	// Mesh
//	std::string meshName = aiMesh.mName.C_Str();
//	unsigned int matIndex = aiMesh.mMaterialIndex;
//	//std::string materialName = aiScene.mMaterials[matIndex]->GetName().C_Str();
//
//	// Material
//	aiMaterial* material = aiScene.mMaterials[matIndex];
//	std::string materialName = material->GetName().C_Str();
//
//	//MeshData meshData = processMeshData(*ai_Mesh, bones, isAnim);
//	//meshData.setMaterial(m_materialCache.getMaterial(materialName));
//	//
//	//
//	//
//	//return Mesh(meshData);
//}

Node* ModelLoader::buildNodesTree(const aiNode* ai_Node, Node* parentNode) {
	std::string nodeName = ai_Node->mName.data;
	int numChildren = ai_Node->mNumChildren;
	glm::mat4 transformation = toMatrix(ai_Node->mTransformation);

	Node* node = new Node(nodeName, parentNode, transformation, DataType::model);

	for (int i = 0; i < numChildren; i++) {
		aiNode* aiChildNode = ai_Node->mChildren[i];
		Node* childNode = buildNodesTree(aiChildNode, node);
	}

	return node;
 }

std::unordered_map<std::string, Bone> ModelLoader::storeBones(const aiScene& ai_scene) {
	std::unordered_map<std::string, Bone> bonesMap;
	unsigned int numMeshes = ai_scene.mNumMeshes;
	for (int i = 0; i < numMeshes; i++) {
		aiMesh* aiMesh = ai_scene.mMeshes[i];
		if (aiMesh->HasBones()) {
			unsigned int numBones = aiMesh->mNumBones;
			for (int j = 0; j < numBones; j++) {
				aiBone* aiBone = aiMesh->mBones[j];
				
				std::string boneName = aiBone->mName.data;
				glm::mat4 offMatrix = toMatrix(aiBone->mOffsetMatrix);

				Bone bone(m_bonesMap.size(), boneName, offMatrix);
				m_bonesMap.insert({ boneName, bone });
				bonesMap.insert({ boneName, bone });
			}
		} 
	}
	return bonesMap;

}

std::vector<Material> ModelLoader::processMaterials(const aiScene& aiScene) {
	std::vector<Material> materials;
	unsigned int numMaterials = aiScene.mNumMaterials;

	for (int i = 0; i < numMaterials; i++) {
		aiMaterial* mat = aiScene.mMaterials[i];
		std::string materialName = mat->GetName().C_Str();

		Material material(materialName);
		material.setAmbientColor(getAmbientColor(*mat));
		material.setDiffuseColor(getDiffuseColor(*mat));
		material.setSpecularColor(getSpecularColor(*mat));
		material.setReflectance(getShininessStrength(*mat));

		materials.emplace_back(material);
	}
	return materials;
}

std::vector<TextureData> ModelLoader::processTextures(const aiScene& aiScene) {
	std::vector<TextureData> textures;
	for (int i = 0; i < aiScene.mNumMaterials; i++) {
		aiMaterial* mat = aiScene.mMaterials[i];

		std::optional<TextureData> diffVal = getDiffuseTexture(*mat);
		if(diffVal.has_value())
			textures.emplace_back(diffVal.value());

		diffVal = getNormalTexture(*mat);
		if (diffVal.has_value())
			textures.emplace_back(diffVal.value());
	}

	return textures;
}

std::optional<TextureData> ModelLoader::getDiffuseTexture(const aiMaterial& aiMaterial) {
	return getTexture(aiMaterial, aiTextureType_DIFFUSE);
}

std::optional<TextureData> ModelLoader::getNormalTexture(const aiMaterial& aiMaterial) {
	return getTexture(aiMaterial, aiTextureType_NORMALS);
}

std::optional<TextureData> ModelLoader::getTexture(const aiMaterial& aiMaterial, const aiTextureType textureType) {
	aiString aiTextureName;
	if (aiReturn_SUCCESS == aiMaterial.GetTexture(textureType, 0, &aiTextureName)) {
		std::string texturePath = m_directory + "/" + aiTextureName.C_Str();
		return TextureData(aiTextureName.C_Str(), texturePath);
	}
	return {};
}

glm::vec4 ModelLoader::getAmbientColor(const aiMaterial& aiMaterial) {
	glm::vec4 outColorAmbient(0.0f, 0.0f, 0.0f, 1.0f);
	aiColor3D colorAmbient;
	if (aiReturn_SUCCESS == aiMaterial.Get(AI_MATKEY_COLOR_AMBIENT, colorAmbient)) {
		outColorAmbient.x = colorAmbient.r;
		outColorAmbient.y = colorAmbient.g;
		outColorAmbient.z = colorAmbient.b;
	}
	return outColorAmbient;
}

glm::vec4 ModelLoader::getDiffuseColor(const aiMaterial & aiMaterial) {
	glm::vec4 outDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	aiColor3D colorDiffuse;
	if (aiReturn_SUCCESS == aiMaterial.Get(AI_MATKEY_COLOR_DIFFUSE, colorDiffuse)) {
		outDiffuseColor.x = colorDiffuse.r;
		outDiffuseColor.y = colorDiffuse.g;
		outDiffuseColor.z = colorDiffuse.b;
	}
	return outDiffuseColor;
}

//	Scales the specular color of the material. 	
//This value is kept separate from the specular color by most modelers, and so do we.
glm::vec4 ModelLoader::getSpecularColor(const aiMaterial& aiMaterial) {
	glm::vec4 outSpecularColor(0.0f, 0.0f, 0.0f, 1.0f);
	aiColor3D specularColor;
	if (aiReturn_SUCCESS == aiMaterial.Get(AI_MATKEY_COLOR_SPECULAR, specularColor)) {
		outSpecularColor.x = specularColor.r;
		outSpecularColor.y = specularColor.g;
		outSpecularColor.z = specularColor.b;
	}
	return outSpecularColor;
}

float ModelLoader::getShininessStrength(const aiMaterial& aiMaterial) {
	float shininessStrength = 0.0f;
	aiMaterial.Get(AI_MATKEY_SHININESS_STRENGTH, shininessStrength);
	return shininessStrength;
}

//void ModelLoader::processAnim(const aiScene& aiScene) {
//	std::cout << "..........animation.........." << std::endl;
//	int numAnimations = aiScene.mNumAnimations;
//
//	std::cout << "Number of skeletons: " << aiScene.mNumSkeletons << std::endl;;
//
//	for (int i = 0; i < numAnimations; i++) {
//		aiAnimation* aiAnimation = aiScene.mAnimations[i];
//
//		std::string animName = aiAnimation->mName.data;
//		std::cout << "Animation name: " << animName << std::endl;
//		unsigned int animChannels = aiAnimation->mNumChannels;
//		std::cout << "Number of channels: " << animChannels << std::endl;
//	
//		int maxFrames = calcAnimationMaxFrames(*aiAnimation);
//		std::cout << "Max frames: " << maxFrames << std::endl;
//	}
//
//}

int ModelLoader::calcAnimationMaxFrames(const aiAnimation& ai_Animation) {
	int maxFrames = 0;
	int numNodeAnims = ai_Animation.mNumChannels;
	
	for (int i = 0; i < numNodeAnims; i++) {
		aiNodeAnim* aiNodeAnim = ai_Animation.mChannels[i];
		int numFrames = std::max(std::max(aiNodeAnim->mNumPositionKeys, aiNodeAnim->mNumScalingKeys), aiNodeAnim->mNumRotationKeys);
			maxFrames = std::max(maxFrames, numFrames);
	}
	return maxFrames;
}

void ModelLoader::buildFrameMatrices(const aiAnimation& aiAnimation, const std::vector<Bone>& bones, AnimatedFrame& animatedFrame,
	int frame, Node* node, const glm::mat4& parentTransformation, const glm::mat4& globalInverseTransform) {

	std::string nodeName = node->getName();
	aiNodeAnim* aiNodeAnim = findAIAnimNode(aiAnimation, nodeName);	
	glm::mat4 nodeTransform = node->getNodeTransformation();
	if(aiNodeAnim != nullptr)
		nodeTransform = buildNodeTransformationMatrix(*aiNodeAnim, frame);

	glm::mat4 nodeGlobalTransform =  parentTransformation * nodeTransform;	// TODO check order of operations

	std::vector<Bone> affectedBones;
	for (Bone b : bones) {
		if (b.getBoneName() == nodeName)
			affectedBones.push_back(b);
	}

	for (Bone bone : affectedBones) {
		glm::mat4 boneTransform = globalInverseTransform * nodeGlobalTransform * bone.getOffsetMatrix();
		animatedFrame.m_boneMatrices.at(bone.getBoneId()) = boneTransform;
	}

	for (Node* childNode : node->getChildren()) {
		buildFrameMatrices(aiAnimation, bones, animatedFrame, frame, childNode, nodeGlobalTransform, globalInverseTransform);
	}
}

glm::mat4 ModelLoader::buildNodeTransformationMatrix(const aiNodeAnim& aiNodeAnim, int frame) {
	aiVectorKey aiVecKey;
	aiVector3D vec;

	glm::mat4 nodeTransform(1.0f);
	int numPositions = aiNodeAnim.mNumPositionKeys;

	if (numPositions > 0) {
		aiVecKey = aiNodeAnim.mPositionKeys[std::min(numPositions - 1, frame)];
		vec = aiVecKey.mValue;
		nodeTransform = glm::translate(nodeTransform, glm::vec3(vec.x, vec.y, vec.z));
	}

	int numRotations = aiNodeAnim.mNumRotationKeys;
	if (numRotations > 0) {
		aiQuatKey quatKey = aiNodeAnim.mRotationKeys[std::min(numRotations - 1, frame)];
		aiQuaternion aiQuat = quatKey.mValue;
		glm::quat quat(aiQuat.w, aiQuat.x, aiQuat.y, aiQuat.z);
		nodeTransform = nodeTransform * glm::mat4_cast(quat);
	}

	int numScalingKeys = aiNodeAnim.mNumScalingKeys;
	if (numScalingKeys > 0) {
		aiVecKey = aiNodeAnim.mScalingKeys[std::min(numScalingKeys - 1, frame)];
		vec = aiVecKey.mValue;
		nodeTransform = glm::scale(nodeTransform, glm::vec3(vec.x, vec.y, vec.z));
	}

	return nodeTransform;
}

MeshData ModelLoader::processMeshData(aiMesh& aiMesh, std::vector<Bone>& bones, bool isAnim) {
	std::vector<float> vertices = processVertices(aiMesh);
	std::vector<unsigned int> indices = processIndices(aiMesh);
	std::vector<float> texCoords = processTexCoords(aiMesh);
	std::vector<float> normals = processNormals(aiMesh);
	
	std::vector<float> tangents = processTangents(aiMesh);
	std::vector<float> bitangents = processBitangents(aiMesh);

//	if(isAnim)
	
	//std::vector<int> bIds(vertices.size() * 4 / 3);
	//std::vector<float> bWeights(vertices.size() * 4 / 3);
	//if (animMeshData.hasAnimData())

	if (isAnim) {
		AnimaMeshData animMeshData = processBones(aiMesh, bones);
		return MeshData(vertices, indices, texCoords, normals, tangents, bitangents, animMeshData.getBoneIds(), animMeshData.getWeights());
	}
	else
		return MeshData(vertices, indices, texCoords, normals, tangents, bitangents);
}

static const unsigned int MAX_BONES = 150;
AnimaMeshData ModelLoader::processBones(const aiMesh& aiMesh, std::vector<Bone>& bones) {
	// One vector can have multiple weights
	std::map<int, std::vector<VertexWeight>> weightSet; // key: vertex id / index
	// process bones
	for (int i = 0; i < aiMesh.mNumBones; i++) {
		aiBone* aiBone = aiMesh.mBones[i];
		int boneId = bones.size();
		bones.emplace_back(boneId, aiBone->mName.data, toMatrix(aiBone->mOffsetMatrix)); // add a bone
	
		// process weights
		for (int j = 0; j < aiBone->mNumWeights; j++) {
			aiVertexWeight aiWeight = aiBone->mWeights[j];
			VertexWeight vw(boneId, aiWeight.mVertexId, aiWeight.mWeight);
	
			std::vector<VertexWeight>& vertexWeights = weightSet[vw.getVertexId()]; // put weight for vertex
			vertexWeights.emplace_back(boneId, aiWeight.mVertexId, aiWeight.mWeight);  // insert vertex weight
		}
	}

	int weightsPerVertex = 4;	//TODO put somewhere else
	std::vector<int> boneIds;
	std::vector<float> weights;
	for (int i = 0; i < aiMesh.mNumVertices; i++) {
		std::vector<VertexWeight>& vertexWeights = weightSet.at(i);
		for (int j = 0; j < weightsPerVertex; j++) {
			if (j < vertexWeights.size()) {
				VertexWeight& vw = vertexWeights.at(j);
				weights.emplace_back(vw.getWeight());
				boneIds.emplace_back(vw.getBoneId());
			}
			else {
				weights.push_back(0.0f);
				boneIds.push_back(0);
			}
		}
	}
	
	return AnimaMeshData(weights, boneIds);
}

std::vector<Animation> ModelLoader::processAnimations(const aiScene& scene, const std::vector<Bone>& boneList, Node* rootNode, const glm::mat4& globalInverseTransformation) {
	std::vector<Animation> animations;

	// processs all animations
	for (int i = 0; i < scene.mNumAnimations; i++) {
		aiAnimation* aiAnimation = scene.mAnimations[i];
		int maxFrames = calcAnimationMaxFrames(*aiAnimation);

		std::vector<AnimatedFrame> frames;

		for (int j = 0; j < maxFrames; j++) {
			std::vector<glm::mat4> boneMarices(MAX_BONES, glm::mat4(1.0f));
			AnimatedFrame animatedFrame(boneMarices);
			buildFrameMatrices(*aiAnimation, boneList, animatedFrame, j, rootNode, rootNode->getNodeTransformation(), globalInverseTransformation); // calculate matrix for each frame
			frames.push_back(animatedFrame);
		}

		Animation animation(aiAnimation->mName.data, aiAnimation->mDuration, frames);
		animations.push_back(animation);

	}

	return animations;
}

// Mesh functions

std::vector<unsigned int> ModelLoader::processIndices(const aiMesh& mesh) {
	std::vector<unsigned int> indices;

	// now walk throug each of the ai_mesh's faces (a face is a ai_mesh its triangles) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh.mNumFaces; i++) {
		aiFace face = mesh.mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	return indices;
}

std::vector<float> ModelLoader::processVertices(const aiMesh& aiMesh) {
	int size = aiMesh.mNumVertices;
	std::vector<float> vertices(size * 3);
	unsigned int i = 0, j = 0;
	while (j < size) {
		vertices.at(i++) = aiMesh.mVertices[j].x;
		vertices.at(i++) = aiMesh.mVertices[j].y;
		vertices.at(i++) = aiMesh.mVertices[j++].z;
	}
	return vertices;
}

std::vector<float> ModelLoader::processTexCoords(const aiMesh& aiMesh) {

	int size = aiMesh.mNumVertices;
	std::vector<float> texCoords(size * 2);
	unsigned int i = 0, j = 0;
	while (j < size) {
		// Presume we don't have 8 different texture coordinates 
		texCoords.at(i++) = aiMesh.mTextureCoords[0][j].x;
		texCoords.at(i++) = aiMesh.mTextureCoords[0][j++].y;
	}
	return texCoords;
}

std::vector<float> ModelLoader::processTangents(const aiMesh& aiMesh) {
	int size = aiMesh.mNumVertices;
	std::vector<float> tangents(size * 3);
	unsigned int i = 0, j = 0;
	while (j < size) {
		tangents.at(i++) = aiMesh.mTangents[j].x;
		tangents.at(i++) = aiMesh.mTangents[j].y;
		tangents.at(i++) = aiMesh.mTangents[j++].z;
	}
	// TODO check and make here tangents if assimp didn't make normals
	return tangents;
}

std::vector<float> ModelLoader::processBitangents(const aiMesh& aiMesh) {
	int size = aiMesh.mNumVertices;
	std::vector<float> bitangents(size * 3);
	unsigned int i = 0, j = 0;
	while (j < size) {
		bitangents.at(i++) = aiMesh.mBitangents[j].x;
		bitangents.at(i++) = aiMesh.mBitangents[j].y;
		bitangents.at(i++) = aiMesh.mBitangents[j++].z;
	}
	return bitangents;
}

std::vector<float> ModelLoader::processNormals(const aiMesh& aiMesh) {
	int size = aiMesh.mNumVertices;
	std::vector<float> normals(size * 3);
	unsigned int i = 0, j = 0;
	while (j < size) {
		normals.at(i++) = aiMesh.mNormals[j].x;
		normals.at(i++) = aiMesh.mNormals[j].y;
		normals.at(i++) = aiMesh.mNormals[j++].z;
	}
	return normals;
}

// Utility functions

aiNodeAnim* ModelLoader::findAIAnimNode(const aiAnimation& ai_Animtion, std::string nodeName) {
	aiNodeAnim* result = nullptr;
	int numAnimNodes = ai_Animtion.mNumChannels;
	for (int i = 0; i < numAnimNodes; i++) {
		aiNodeAnim* aiNodeAnim = ai_Animtion.mChannels[i];
		if (nodeName == aiNodeAnim->mNodeName.data) {
			result = aiNodeAnim;
			break;
		}
	}
	
	return result;
}

std::string ModelLoader::getFileDirectory(std::string filePath) {		// TODO put in utility class
	unsigned int len = filePath.length();
	std::string a = "/";
	unsigned int r = 0;
	unsigned int c = 0;
	while (r + c <= len) {		// return the position of last '/'
		r = filePath.find(a, r + c++);
	}
	return filePath.erase(r, len);	// erase everyting after the lFast '/' leaving just the directory path
}

glm::mat4 ModelLoader::toMatrix(const aiMatrix4x4& aiMatrix4x4) {
	glm::mat4 result;

//	return glm::mat4(
//		(double)aiMatrix4x4.a1, (double)aiMatrix4x4.b1, (double)aiMatrix4x4.c1, (double)aiMatrix4x4.d1,
//		(double)aiMatrix4x4.a2, (double)aiMatrix4x4.b2, (double)aiMatrix4x4.c2, (double)aiMatrix4x4.d2,
//		(double)aiMatrix4x4.a3, (double)aiMatrix4x4.b3, (double)aiMatrix4x4.c3, (double)aiMatrix4x4.d3,
//		(double)aiMatrix4x4.a4, (double)aiMatrix4x4.b4, (double)aiMatrix4x4.c4, (double)aiMatrix4x4.d4
//	);

	result[0][0] = aiMatrix4x4.a1;
	result[1][0] = aiMatrix4x4.a2;
	result[2][0] = aiMatrix4x4.a3;
	result[3][0] = aiMatrix4x4.a4;
	
	result[0][1] = aiMatrix4x4.b1;
	result[1][1] = aiMatrix4x4.b2;
	result[2][1] = aiMatrix4x4.b3;
	result[3][1] = aiMatrix4x4.b4;
	
	result[0][2] = aiMatrix4x4.c1;
	result[1][2] = aiMatrix4x4.c2;
	result[2][2] = aiMatrix4x4.c3;
	result[3][2] = aiMatrix4x4.c4;
	
	result[0][3] = aiMatrix4x4.d1;
	result[1][3] = aiMatrix4x4.d2;
	result[2][3] = aiMatrix4x4.d3;
	result[3][3] = aiMatrix4x4.d4;

	return result;
}

void ModelLoader::printMetaData(const aiMetadata* metaData, bool isPrinting) {
	if (metaData && isPrinting) {
		for (int i = 0; i < metaData->mNumProperties; i++) {
			aiString key = metaData->mKeys[i];
			aiMetadataEntry entry = metaData->mValues[i];
			aiMetadataType type = entry.mType;
			
			void* v = entry.mData;
			
			aiString s;
			if (metaData->Get(key, s)) {
				std::cout << "\t" << key.data << " " << s.C_Str() << std::endl;
				continue;
			}
			bool b;
			if (metaData->Get(key, b)) {
				std::cout << "\t" << key.data << " " << b << std::endl;
				continue;
			}
			int j;
			if (metaData->Get(key, j)) {
				std::cout << "\t" << key.data << " " << j << std::endl;
				continue;
			}
			aiVector3D vec;
			if (metaData->Get(key, vec)) {
				std::cout << "\t" << key.data << " " << vec.x << " " << vec.y << " " << vec.z << std::endl;
				continue;
			}
			aiMetadata m;
			if (metaData->Get(key, m)) {
				std::cout << "\t" << key.data << " " << "THERES META" << std::endl;
				continue;
			}
			float f;
			if (metaData->Get(key, f)) {
				std::cout << "\t" << key.data << " " << f << std::endl;
				continue;
			}
			int64_t i6;
			if (metaData->Get(key, i6)) {
				std::cout << "\t" << key.data << " " << i6 << std::endl;
				continue;
			}
			uint64_t ui64;
			if (metaData->Get(key, ui64)) {
				std::cout << "\t" << key.data << " " << ui64 << std::endl;
				continue;
			}

			std::cout << "\t" << key.data << " THERES SOMETHING" << std::endl;

		}
	}
}


//aiColor3D colorEmissive;
//if (mat->Get(AI_MATKEY_COLOR_EMISSIVE, colorEmissive) == AI_SUCCESS) {
////	std::cout << "Emissive: " << colorEmissive.r << " " << colorEmissive.g << " " << colorEmissive.b <<  std::endl;
//}
//
//aiColor3D colorReflective;
//if (mat->Get(AI_MATKEY_COLOR_REFLECTIVE, colorReflective) == AI_SUCCESS) {
//	//	std::cout << "Reflective: " << colorReflective.r << " " << colorReflective.g << " " << colorReflective.b << std::endl;
//}
//
//aiColor3D colorTransparent;
//if (mat->Get(AI_MATKEY_COLOR_TRANSPARENT, colorTransparent) == AI_SUCCESS) {
//	//	std::cout << "Transparent: " << colorTransparent.r << " " << colorTransparent.g << " " << colorTransparent.b << std::endl;
//}
//
//int blendFunc; // default value false
//if (mat->Get(AI_MATKEY_BLEND_FUNC, blendFunc) == AI_SUCCESS) {
//	//	std::cout << "Blend fun: " << blendFunc << std::endl;
//}
//
//// default value 1
//float refraction;
//if (mat->Get(AI_MATKEY_REFRACTI, refraction) == AI_SUCCESS) {
//	//	std::cout << "Refraction: " << refraction << std::endl;
//}
//
//// deafult value 0
//float reflectivity;
//if (mat->Get(AI_MATKEY_REFLECTIVITY, reflectivity) == AI_SUCCESS) {
//	//	std::cout << "Reflectivity: " << reflectivity << std::endl;
//}
//
//// 	Use this value to decide whether you have to activate alpha blending for rendering.
////OPACITY != 1 usually also implies TWOSIDED = 1 to avoid cull artifacts.
//// default value 1
//float opacity; 
//if (mat->Get(AI_MATKEY_OPACITY, opacity) == AI_SUCCESS) {
//	//	std::cout << "Opacity: " << opacity << std::endl;
//}
//
//int shadingModel; // default  value gouraud
//if (mat->Get(AI_MATKEY_SHADING_MODEL, shadingModel) == AI_SUCCESS) {
//	//	std::cout << "Shading: " << shadingModel << std::endl;
//}
//
//aiColor3D specularFactor;
//if (mat->Get(AI_MATKEY_SPECULAR_FACTOR, specularFactor) == AI_SUCCESS) {
//	//	std::cout << "Specular factor: " << specularFactor.r << " " << specularFactor.g << " " << specularFactor.b << std::endl;
//}

//Defines the shininess of a phong-shaded material. This is actually the exponent of the phong specular equation 	
//SHININESS = 0 is equivalent to SHADING_MODEL = aiShadingMode_Gouraud.
//float shininess;
//if (mat->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
//	//	std::cout << "Shininess: " << shininess << std::endl;
//}
//
//aiColor3D anisotropyFactor;
//if (mat->Get(AI_MATKEY_ANISOTROPY_FACTOR, anisotropyFactor) == AI_SUCCESS) {
//	//	std::cout << "Anisotropy factor: " << anisotropyFactor.r << " " << anisotropyFactor.g << " " << anisotropyFactor.b <<  std::endl;
//}