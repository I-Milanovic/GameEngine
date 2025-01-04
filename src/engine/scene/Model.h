#pragma once

#include <string>
#include <vector>

//#include "src/engine/scene/MeshData.h"
#include "src/engine/scene/Entity.h"

#include "src/engine/scene/Mesh.h"
//#include "src/engine/scene/MeshData.h"

#include "src/engine/scene/Animation.h"

class Model {

public:
	Model(const std::string id, MeshData meshData);


	// ---------- Getters ----------

	Entity& getEntity();
	std::string getModelName();
	MeshData getMeshData();
	AnimationManager& getAnimationManager();
	Mesh& getMesh();

	// ---------- Setters ----------

	void setModelName(std::string modelName);


private:
	std::string m_modelName;
	MeshData m_meshData;
	Entity m_entity;
	Mesh m_mesh;// = nullptr; // TODO make unique pointer
	AnimationManager m_animationManager;	// TODO should not be here cuz of data oriented design




};