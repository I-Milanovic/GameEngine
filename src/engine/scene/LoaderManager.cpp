#include "LoaderManager.h"

#include <string>

LoaderManager::LoaderManager(ModelCache& modelCache, MaterialCache& materialCache, TextureCache& textureCache) :
	m_modelCache(modelCache), m_materialCache(materialCache), m_textureCache(textureCache) {}


//TODO model loader moze biti i kompozicija
void LoaderManager::loadModel(const std::string& modelPath, bool isAnim) {
	m_assimpWrapper.m_isAnim = isAnim;
	m_assimpWrapper.initLoader(modelPath);
	m_modelCache.addModels(m_assimpWrapper.loadModel());
	m_materialCache.addMaterials(m_assimpWrapper.processMaterials());
	m_textureCache.addTextures(m_assimpWrapper.processTextures());	
	m_assimpWrapper.createGraph();
}
