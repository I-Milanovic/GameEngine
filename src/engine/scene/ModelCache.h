#pragma once

#include <string>
#include <unordered_map>
#include "src/engine/scene/Model.h"




class ModelCache {

public:
	ModelCache();

	Model* getModel(std::string modelName);
	void addModel(Model model);
	void addModels(const std::vector<Model>& models);

	void createNewModelName(Model& model);

//	void loadModel(std::string path);
	
	std::unordered_map<std::string, Model>* getModels();

private:
	std::unordered_map<std::string, Model> m_models;
};