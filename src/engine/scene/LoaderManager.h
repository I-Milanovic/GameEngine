#pragma once

#include <src/engine/scene/MaterialCache.h>
#include <src/engine/scene/ModelCache.h>
#include <src/engine/scene/TextureCache.h>

#include <src/engine/AssimpWrapper.h>

class LoaderManager {

public:
	LoaderManager(ModelCache& modelCache, MaterialCache& materialCache, TextureCache& textureCache);

	void loadModel(const std::string& modelPath, bool isAnim);

private: 
	ModelCache& m_modelCache;
	MaterialCache& m_materialCache;
	TextureCache& m_textureCache;
	
	AssimpWrapper m_assimpWrapper;

};

