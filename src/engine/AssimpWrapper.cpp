#include "AssimpWrapper.h"
#include <assimp/postprocess.h>
#include <unordered_map>

// Remove later
#include <iostream>
#include <glm/gtx/string_cast.hpp>


void AssimpWrapper::initLoader(const std::string modelpath) { // TODO maybe name init or soemthing like that
	// read file via ASSIMP
	
	//TODO reserving space for vectors

	long flag1 = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices;

	long flag4 = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices |
		aiProcess_FixInfacingNormals | aiProcess_LimitBoneWeights | (m_isAnim ? 0 : aiProcess_PreTransformVertices);
		
	m_aiScene = m_importer.ReadFile(modelpath, flag4);

	// check for errors
	if (!m_aiScene || m_aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_aiScene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << m_importer.GetErrorString() << std::endl;
		return;
	}
	m_directory = getFileDirectory(modelpath);
}

/*
* Dont' used it's depricated!
*/
void AssimpWrapper::flush() {
	aiReleaseImport(m_aiScene);
}

std::vector<Model> AssimpWrapper::loadModel() {
	std::vector<Model> models;
	for (int i = 0; i < m_aiScene->mNumMeshes; i++) {
		aiMesh* aiMesh = m_aiScene->mMeshes[i];
		std::string modelName = aiMesh->mName.C_Str();
		MeshData meshData = processMeshData(*aiMesh);
		Model model(modelName, meshData);
		//std::vector<Animation> animations = parseAnimations();
		//if (animations.size() > 0)
		model.getAnimationManager().addAnimations(parseAnimations());
		models.emplace_back(model); // create Model and emplace it
	}
	return models;
}

// ---------- Mesh functions ----------

MeshData AssimpWrapper::processMeshData(const aiMesh& aiMesh) {
	
	MeshData meshData;
	meshData.m_meshName = aiMesh.mName.C_Str();
	meshData.m_positions = processVertices(aiMesh);
	meshData.m_indices = processIndices(aiMesh);
	meshData.m_texCoords = processTexCoords(aiMesh);
	meshData.m_normals = processNormals(aiMesh);
	meshData.m_tangents = processTangents(aiMesh);
	meshData.m_bitangents = processBitangents(aiMesh);
	meshData.m_materialName = m_aiScene->mMaterials[aiMesh.mMaterialIndex]->GetName().C_Str();
	
	meshData.m_boneIndices = std::vector<int>(1); 	  //TODO this should not be here
	meshData.m_weights = std::vector<float>(1);		  //TODO this should not be here
	if (m_isAnim) {
		AnimaMeshData animMeshData = parseBones(&aiMesh);
		meshData.m_boneIndices = animMeshData.getBoneIds();
		meshData.m_weights = animMeshData.getWeights();
	}

	return meshData;
}

std::vector<unsigned int> AssimpWrapper::processIndices(const aiMesh& mesh) {
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

std::vector<float> AssimpWrapper::processVertices(const aiMesh& aiMesh) {
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

std::vector<float> AssimpWrapper::processTexCoords(const aiMesh& aiMesh) {

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

std::vector<float> AssimpWrapper::processTangents(const aiMesh& aiMesh) {
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

std::vector<float> AssimpWrapper::processBitangents(const aiMesh& aiMesh) {
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

std::vector<float> AssimpWrapper::processNormals(const aiMesh& aiMesh) {
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

// ---------- Material functions ----------

std::vector<Material> AssimpWrapper::processMaterials() {
	std::vector<Material> materials;
	unsigned int numMaterials = m_aiScene->mNumMaterials;
	// starting from 1 to skip assimps own default material
	for (int i = 0; i < numMaterials; i++) {
		aiMaterial* mat = m_aiScene->mMaterials[i];
	
		std::string materialName = mat->GetName().C_Str();

		// use to throw out obj default material
		if (numMaterials > 1 && !materialName.compare("DefaultMaterial"))	//TODO check this
			continue;


		Material material(materialName);
		material.setAmbientColor(getAmbientColor(*mat));
		material.setDiffuseColor(getDiffuseColor(*mat));
		material.setSpecularColor(getSpecularColor(*mat));
		material.setReflectance(getShininessStrength(*mat));

		// TODO this whole thing should be nicer
		std::optional<TextureData> textureData = getDiffuseTexture(*mat);
		if(textureData.has_value())
			material.setTexturePath(textureData.value().path);	//TODO look at the name vs path more closely for pairing purposes and stick to one
		textureData = getNormalTexture(*mat);
		if (textureData.has_value())
			material.setNormaMapPath(textureData.value().path); //TODO dito here

		materials.emplace_back(material);
	}
	return materials;
}
	// TODO all these funcitons that have inifialized r,g,b,a need to be looked at because some of them ommit texture display
glm::vec4 AssimpWrapper::getAmbientColor(const aiMaterial& aiMaterial) {
	glm::vec4 outColorAmbient(1.0f, 1.0f, 1.0f, 1.0f);	// TODO maybe set all ones?
	aiColor3D colorAmbient;
	if (aiReturn_SUCCESS == aiMaterial.Get(AI_MATKEY_COLOR_AMBIENT, colorAmbient)) {
		outColorAmbient.x = colorAmbient.r;
		outColorAmbient.y = colorAmbient.g;
		outColorAmbient.z = colorAmbient.b;
	}
	return outColorAmbient;
}

glm::vec4 AssimpWrapper::getDiffuseColor(const aiMaterial& aiMaterial) {
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
glm::vec4 AssimpWrapper::getSpecularColor(const aiMaterial& aiMaterial) {
	glm::vec4 outSpecularColor(0.0f, 0.0f, 0.0f, 1.0f);
	aiColor3D specularColor;
	if (aiReturn_SUCCESS == aiMaterial.Get(AI_MATKEY_COLOR_SPECULAR, specularColor)) {
		outSpecularColor.x = specularColor.r;
		outSpecularColor.y = specularColor.g;
		outSpecularColor.z = specularColor.b;
	}
	return outSpecularColor;
}

float AssimpWrapper::getShininessStrength(const aiMaterial& aiMaterial) {
	float shininessStrength = 0.0f;
	aiMaterial.Get(AI_MATKEY_SHININESS_STRENGTH, shininessStrength);
	return shininessStrength;
}

std::vector<TextureData> AssimpWrapper::processTextures() {
	int size = m_aiScene->mNumMaterials;
	std::vector<TextureData> textures;
	for (int i = 0; i < size; i++) {
		aiMaterial* mat = m_aiScene->mMaterials[i];

		std::string matName = mat->GetName().C_Str();
		if (size > 1 && !matName.compare("DefaultMaterial"))	//TODO check this
			continue;

		std::optional<TextureData> textureData = getDiffuseTexture(*mat);
		if (textureData.has_value())
			textures.emplace_back(textureData.value());

		textureData = getNormalTexture(*mat);
		if (textureData.has_value())
			textures.emplace_back(textureData.value());
	}

	return textures;
}

std::optional<TextureData> AssimpWrapper::getTexture(const aiMaterial& aiMaterial, const aiTextureType textureType) {
	aiString aiTextureName;
	if (aiReturn_SUCCESS == aiMaterial.GetTexture(textureType, 0, &aiTextureName)) {
		std::string texturePath = m_directory + "/" + aiTextureName.C_Str();
		return TextureData(texturePath, aiTextureName.C_Str());
	}
	return {};
}

std::optional<TextureData> AssimpWrapper::getDiffuseTexture(const aiMaterial& aiMaterial) {
	return getTexture(aiMaterial, aiTextureType_DIFFUSE);
}

std::optional<TextureData> AssimpWrapper::getNormalTexture(const aiMaterial& aiMaterial) {
	return getTexture(aiMaterial, aiTextureType_NORMALS);
}

// ---------- Animation functions ----------

std::vector<Animation> AssimpWrapper::parseAnimations() {
	std::vector<Animation> animations;
	Node* rootNode = buildNodesTree(m_aiScene->mRootNode, nullptr);

	for (int i = 0; i < m_aiScene->mNumAnimations; i++) {
		aiAnimation* aiAnimation = m_aiScene->mAnimations[i];
		std::vector<AnimatedFrame> animatedFrames = parseSingleAnimation(aiAnimation, rootNode, glm::inverse(toMatrix(m_aiScene->mRootNode->mTransformation)));
		Animation animation(aiAnimation->mName.data, aiAnimation->mDuration, animatedFrames);
		animations.push_back(animation);
	}
	return animations;
}

AnimaMeshData AssimpWrapper::parseBones(const aiMesh* aiMesh) {
	std::unordered_map<int, std::vector<VertexWeight>> vertexIdToWeightsMap;
	for (unsigned int j = 0; j < aiMesh->mNumBones; j++) {
		// insert all unique bones in global map for later use
		aiBone* aiBone = aiMesh->mBones[j];
		std::string boneName = aiBone->mName.C_Str();
		int boneId = m_nameToBoneMap.size();
		if (m_nameToBoneMap.contains(boneName))
			boneId = m_nameToBoneMap.at(boneName).getBoneId();
		else
			m_nameToBoneMap.insert({ boneName, Bone(boneId, boneName, toMatrix(aiBone->mOffsetMatrix)) });

		for (int k = 0; k < aiBone->mNumWeights; k++) {
			aiVertexWeight aiVertexWeight = aiBone->mWeights[k];
			std::vector<VertexWeight>& vertexWeights = vertexIdToWeightsMap[aiVertexWeight.mVertexId];
			vertexWeights.emplace_back(boneId, aiVertexWeight.mVertexId, aiVertexWeight.mWeight);
		}
	}
	// limit to 4 weights per vertex
	int weightsPerVertex = 4;	//TODO put somewhere else
	std::vector<int> boneIds;
	std::vector<float> weights;
	for (int i = 0; i < aiMesh->mNumVertices; i++) {
		std::vector<VertexWeight>& vertexWeights = vertexIdToWeightsMap.at(i);
		for (int j = 0; j < weightsPerVertex; j++) {

			//if (j < vertexWeights.size()) {
			//	VertexWeight& vw = vertexWeights.at(j);
			//	std::cout << vw.getBoneId() << " : " << vw.getVertexId() << " : " << vw.getWeight() << std::endl;
			//}

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

static const unsigned int MAX_BONES = 150;
std::vector<AnimatedFrame> AssimpWrapper::parseSingleAnimation(const aiAnimation* aiAnimation, Node* rootNode, const glm::mat4& globalInverseTransform) {
	std::vector<AnimatedFrame> animatedFrames;
	for (int i = 0; i < getAnimMaxFrames(aiAnimation); i++) {
		std::vector<glm::mat4> boneMatrices(MAX_BONES, glm::mat4(1.0f));	//TODO put this in AnimtedFrame structure
		AnimatedFrame animatedFrame(boneMatrices);
		buildFrameMatrices(aiAnimation, rootNode, i, rootNode->getNodeTransformation(), globalInverseTransform, animatedFrame);
		animatedFrames.push_back(animatedFrame);
	}
	return animatedFrames;
}

int AssimpWrapper::getAnimMaxFrames(const aiAnimation* aiAnimation) {
	int maxFrames = 0;
	int numNodeAnims = aiAnimation->mNumChannels;

	for (int i = 0; i < numNodeAnims; i++) {
		aiNodeAnim* aiNodeAnim = aiAnimation->mChannels[i];
		int numFrames = std::max(std::max(aiNodeAnim->mNumPositionKeys, aiNodeAnim->mNumScalingKeys), aiNodeAnim->mNumRotationKeys);
		maxFrames = std::max(maxFrames, numFrames);
	}
	return maxFrames;
}

void AssimpWrapper::buildFrameMatrices(const aiAnimation* aiAnimation, Node* node, int frame,
	const glm::mat4& parentTransformation, const glm::mat4& globalInverseTransform, AnimatedFrame& animatedFrame) {
	//	std::string nodeName = node->getName();
	//	glm::mat4 nodeTransform = node->getNodeTransformation();

	aiNodeAnim* aiNodeAnim = findAiAnimNode(aiAnimation, node->getName());
	glm::mat4 nodeTransform;
	if (aiNodeAnim)
		nodeTransform = buildPositionMatrix(aiNodeAnim, frame) * buildRotationMatrix(aiNodeAnim, frame) * buildScalingMatrix(aiNodeAnim, frame);
	else
		nodeTransform = node->getNodeTransformation();
	glm::mat4 nodeGlobalTransfrom = parentTransformation * nodeTransform;
	// make an array of affected bones
	// use affected bones to caluclated matrix
	if (m_nameToBoneMap.contains(node->getName())) {
		Bone bone = m_nameToBoneMap.at(node->getName());
		glm::mat4 boneTransform = globalInverseTransform * nodeGlobalTransfrom * bone.getOffsetMatrix();
		animatedFrame.m_boneMatrices.at(bone.getBoneId()) = boneTransform;
	}
	// recursion
	for (Node* childNode : node->getChildren())
		buildFrameMatrices(aiAnimation, childNode, frame, nodeGlobalTransfrom, globalInverseTransform, animatedFrame);
}

aiNodeAnim* AssimpWrapper::findAiAnimNode(const aiAnimation* aiAnimation, std::string nodeName) {
	aiNodeAnim* result = nullptr;
	for (int i = 0; i < aiAnimation->mNumChannels; i++) {
		aiNodeAnim* aiNodeAnim = aiAnimation->mChannels[i];
		if (nodeName == aiNodeAnim->mNodeName.data) {
			result = aiNodeAnim;
			break;
		}
	}
	return result;
}

glm::mat4 AssimpWrapper::buildPositionMatrix(const aiNodeAnim* aiNodeAnim, int frame) {
	glm::mat4 nodeTransform(1.0f);
	int numPositions = aiNodeAnim->mNumPositionKeys;
	if (numPositions > 0) {
		aiVectorKey aiVecKey = aiNodeAnim->mPositionKeys[std::min(numPositions - 1, frame)];
		nodeTransform = glm::translate(nodeTransform, glm::vec3(aiVecKey.mValue.x, aiVecKey.mValue.y, aiVecKey.mValue.z));
	}
	return nodeTransform;
}

glm::mat4 AssimpWrapper::buildRotationMatrix(const aiNodeAnim* aiNodeAnim, int frame) {
	glm::mat4 nodeTransform(1.0f);
	int numRotations = aiNodeAnim->mNumRotationKeys;
	if (numRotations > 0) {
		aiQuatKey quatKey = aiNodeAnim->mRotationKeys[std::min(numRotations - 1, frame)];
		glm::quat quat(quatKey.mValue.w, quatKey.mValue.x, quatKey.mValue.y, quatKey.mValue.z);
		nodeTransform = nodeTransform * glm::mat4_cast(quat);
	}
	return nodeTransform;
}

glm::mat4 AssimpWrapper::buildScalingMatrix(const aiNodeAnim* aiNodeAnim, int frame) {
	glm::mat4 nodeTransform(1.0f);
	int numScales = aiNodeAnim->mNumScalingKeys;
	if (numScales > 0) {
		aiVectorKey aiVecKey = aiNodeAnim->mScalingKeys[std::min(numScales - 1, frame)];
		nodeTransform = glm::scale(nodeTransform, glm::vec3(aiVecKey.mValue.x, aiVecKey.mValue.y, aiVecKey.mValue.z));
	}
	return nodeTransform;
}

// ---------- Utility functions ----------

Node* AssimpWrapper::createGraph() {
	/*m_scene.getSceneGraph().setRootNode()*/;
	return buildSceneGraph(m_aiScene->mRootNode, nullptr);
}

Node* AssimpWrapper::buildSceneGraph(const aiNode* ai_node, Node* parentNode) {
	std::string nodeName = ai_node->mName.data;
	int numChildren = ai_node->mNumChildren;
	glm::mat4 transformation = toMatrix(ai_node->mTransformation);


	//std::unordered_map<std::string, Bone> m_bonesMap = storeBones(*ai_scene);

	Node* node = nullptr;
	if (m_nameToBoneMap.contains(nodeName)) {
		node = new Node(nodeName, parentNode, transformation, DataType::bone);
	}

	else {
		node = new Node(nodeName, parentNode, transformation, DataType::model);
	}

	//printMetaData(ai_node->mMetaData, false);

	unsigned int meshSize = ai_node->mNumMeshes;
	for (int i = 0; i < meshSize; i++) {
		// Mesh
		unsigned int meshIndex = ai_node->mMeshes[i]; // index of this mesh in aiScene array
		aiMesh* mesh = m_aiScene->mMeshes[meshIndex];
		std::string meshName = mesh->mName.C_Str();
		unsigned int matIndex = mesh->mMaterialIndex;

		// set data to my mesh node
		Node* meshNode = new Node(meshName, node, transformation, DataType::mesh);
		//meshNode->setData(m_modelCache.getModel(meshName));
		//node->setData(m_modelCache.getModel(meshName));

		// Material
		aiMaterial* material = m_aiScene->mMaterials[matIndex];
		std::string materialName = material->GetName().C_Str();
		Node* materialNode = new Node(materialName, meshNode, transformation, DataType::material);	// TODO set material node to point to a node in material cache 
		//materialNode->setData(&m_materialCache.getMaterial(materialName));			// prvo ucitaj u cache i onda nek samo odatle povuce potrebne informacije a ne iz aiScene

	}
	for (int i = 0; i < numChildren; i++) {
		aiNode* aiChildNode = ai_node->mChildren[i];
		Node* childNode = buildSceneGraph(aiChildNode, node);
	}

	return node;
}

Node* AssimpWrapper::buildNodesTree(const aiNode* ai_Node, Node* parentNode) {
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

glm::mat4 AssimpWrapper::toMatrix(const aiMatrix4x4& aiMatrix4x4) {
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

std::string AssimpWrapper::getFileDirectory(std::string filePath) {		// TODO put in utility class
	unsigned int len = filePath.length();
	std::string a = "/";
	unsigned int r = 0;
	unsigned int c = 0;
	while (r + c <= len) {		// return the position of last '/'
		r = filePath.find(a, r + c++);
	}
	return filePath.erase(r, len);	// erase everyting after the lFast '/' leaving just the directory path
}

// ---------- Print functions ----------

void AssimpWrapper::printSceneInfo() {
	printMetaData(m_aiScene->mMetaData);

	std::cout << "Scene name: " << m_aiScene->mName.C_Str() << std::endl;
	unsigned int totalVertices = 0;
	unsigned int totalFaces = 0;
	std::set<std::string> unqueNamesBones;
	unsigned int totalAnimMeshes = 0;

	for (int i = 0; i < m_aiScene->mNumMeshes; i++) {
		aiMesh* aiMesh = m_aiScene->mMeshes[i];
		std::cout << "\t" << "Mesh name: " << aiMesh->mName.C_Str() << std::endl;

		unsigned int numVertices = aiMesh->mNumVertices;
		std::cout << "\t" << "Vertices: " << numVertices << std::endl;
		totalVertices += numVertices;

		unsigned int numFaces = aiMesh->mNumFaces;
		std::cout << "\t" << "Faces: " << numFaces << std::endl;
		totalFaces += numFaces;

		unsigned int numBones = aiMesh->mNumBones;
		std::cout << "\t" << "Bones: " << numBones << std::endl;
		printBoneInfo(aiMesh, unqueNamesBones);

		unsigned int numAnimMeshes = aiMesh->mNumAnimMeshes;
		std::cout << "\t" << "Anim meshes: " << numAnimMeshes << std::endl;
		totalAnimMeshes += numAnimMeshes;

		//unsigned int numUvComponents = aiMesh->mNumUVComponents;			// TODO IS ARRAY NOT VALUE
		//std::cout << "\t" << "Uv Componenents: " << numUvComponents << std::endl;

		std::cout << "\n";
	}

	std::cout << "Total vertices: " << totalVertices << std::endl;
	std::cout << "Total faces: " << totalFaces << std::endl;
	std::cout << "Total bones: " << unqueNamesBones.size() << std::endl;
	std::cout << "Total anim meshes: " << totalAnimMeshes << std::endl;
}

void AssimpWrapper::printBoneInfo(const aiMesh* aiMesh, std::set<std::string>& uniqueBones) {
	for (int i = 0; i < aiMesh->mNumBones; i++) {
		aiBone* aiBone = aiMesh->mBones[i];

		std::string boneName = aiBone->mName.C_Str();
		std::cout << "\t\t" << "Bone name: " << boneName << std::endl;
		uniqueBones.insert(boneName);

		unsigned int numWeights = aiBone->mNumWeights;
		std::cout << "\t\t" << "Weights: " << numWeights << std::endl;

		glm::mat4 transformation = toMatrix(aiBone->mOffsetMatrix);
		std::cout << "\t\t " << glm::to_string(transformation) << std::endl;
	}
	
}

void AssimpWrapper::printBones() {
	for (const auto& pair : m_nameToBoneMap) {
		std::string name = (std::string)pair.first;
		Bone bone = ((Bone)pair.second);
		std::cout << bone.getBoneId() << " : " << name << std::endl;
	}
}

void AssimpWrapper::printMetaData(const aiMetadata* metaData) {
	if (metaData) {
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
