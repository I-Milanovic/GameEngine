#include "Scene.h"

#include "QuatCamera.h"

Scene::Scene(int width, int height) :
	m_camera(new OrbitCamera(glm::vec3(0.0f, 0.0f, 0.0f), 10.0f, 1.0f, 0.0f, 0.0f)),
	m_fog(Fog()),
	m_materialCache(MaterialCache()),
	m_textureCache(TextureCache()),
	m_modelCache(ModelCache()),
	m_projection(Projection(45.0f, width, height, 100.0f, 0.1f)),
	m_sceneLights(SceneLights()),
	m_sceneGraph(SceneGraphTree()) {}

Scene::~Scene() {
	std::cout << "Scene deleting" << std::endl;
	delete m_camera;
}

const void Scene::addEntity(Entity entity) {
	std::cout << "Entity Added: " << entity.getID() << std::endl;
}

void Scene::resize(int width, int height){
	m_projection.setRatio(width, height);
}

CameraAbstract& Scene::getCamera() {
	return *m_camera;
}

Fog& Scene::getFog(){
	return m_fog;
}

Projection& Scene::getProjection(){
	return m_projection;
}

SceneLights& Scene::getSceneLights(){
	return m_sceneLights;
}

MaterialCache& Scene::getMaterialCache(){
	return m_materialCache;
}

TextureCache& Scene::getTextureCache(){
	return m_textureCache;
}

ModelCache& Scene::getModelCache() {
	return m_modelCache;
}

SceneGraphTree& Scene::getSceneGraph() {
	return m_sceneGraph;
}
