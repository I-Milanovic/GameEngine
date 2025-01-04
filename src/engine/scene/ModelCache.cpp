#include "ModelCache.h"

#include "src/engine/ModelLoader.h"

#include <iostream>

ModelCache::ModelCache() {}

Model* ModelCache::getModel(std::string modelName) {	// TODO can't return null as a reference solve this with a pointer
	if(m_models.contains(modelName))
		return &m_models.at(modelName);
	return nullptr;
}

void ModelCache::addModel(Model model) {

	std::string keyName = model.getModelName();
	if (m_models.contains(keyName))
		createNewModelName(model);
	else 
		m_models.insert({ keyName, model });

}

void ModelCache::addModels(const std::vector<Model>& models) {
	for (Model model : models)
		addModel(model);
}

void ModelCache::createNewModelName(Model& model) {
	int idx = 0;
	std::string modelName = model.getModelName();
	std::string newName = modelName;
	while (m_models.contains(newName)) {
		newName = modelName + "_" + std::to_string(idx++);
	}
	model.setModelName(newName);
	m_models.insert({ newName, model });
}

std::unordered_map<std::string, Model>* ModelCache::getModels() {
	return &m_models;
}

//void ModelCache::loadModel(std::string path) {
//	//ModelLoader loader;
//	//Model model = modelLoader.loadModel(path);
//	addModel(model);
//}