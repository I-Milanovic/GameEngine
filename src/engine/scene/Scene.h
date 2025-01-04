#pragma once

#include <map>
#include <vector>

#include "Projection.h"
#include "../scene/Mesh.h"
#include "lights/SceneLights.h"
#include "Fog.h"

//#include "Camera.h"
//#include "ArcballCamera.h"

#include "OrbitCamera.h"
#include "CameraAbstract.h"

#include "src/engine/scene/MaterialCache.h"
#include "src/engine/scene/TextureCache.h"
#include "src/engine/scene/ModelCache.h"

#include "src/engine/scene/Model.h"
#include "src/engine/scene/Entity.h"

#include "src/engine/scene/SceneGraphTree.h"

class Scene {

public:
	Scene(int width, int height);
	~Scene();

	const void addEntity(Entity entity);

	void resize(int width, int height);

	CameraAbstract& getCamera();
	Fog& getFog();
	Projection& getProjection();
	SceneLights& getSceneLights();

	MaterialCache& getMaterialCache();
	TextureCache& getTextureCache();
	ModelCache& getModelCache();

	SceneGraphTree& getSceneGraph();

private: 
	CameraAbstract* m_camera;
	Fog m_fog;

	MaterialCache m_materialCache;
	TextureCache m_textureCache;
	ModelCache m_modelCache;

	Projection m_projection;
	SceneLights m_sceneLights;

	SceneGraphTree m_sceneGraph;	// TODO shouldn't be in here
};

