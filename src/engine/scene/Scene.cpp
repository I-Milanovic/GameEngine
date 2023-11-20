#include "Scene.h"

Scene::Scene(int width, int height) :
	m_projection(Projection(45.0f, width, height, 100.0f, 0.1f )),
	m_camera(Camera(glm::vec3(3.0f, 3.0f, 3.0f))),
	m_sceneLights(SceneLights()),
	m_meshes(std::vector<Mesh>()) {
	m_camera.cameraRotate(-430, -320);
}

Camera* Scene::getCamera() { return &m_camera; };
Projection& Scene::getProjection() { return m_projection; };
SceneLights& Scene::getSceneLights() { return m_sceneLights; };
Mesh Scene::getMesh(int index) { return m_meshes.at(index); };
void Scene::addMesh(Mesh mesh) { m_meshes.push_back(mesh); };

void Scene::addPointLight(PointLight pointLight) { m_sceneLights.getPointLights().push_back(pointLight); };
void Scene::removePointLight(int index) { m_sceneLights.getPointLights().erase(m_sceneLights.getPointLights().begin() + index); };


void Scene::addSpotLight(SpotLight spotLight) { m_sceneLights.getSpotLights().push_back(spotLight); };

void Scene::setAmbientLight(AmbientLight& ambientLight) { m_sceneLights.setAmbientLight(ambientLight); };
void Scene::setDirLight(DirLight dirLight) { m_sceneLights.setDirLight(dirLight); };

std::vector<Mesh> Scene::getMeshes() { return m_meshes; };
void Scene::setMeshes(std::vector<Mesh> meshes) { m_meshes = meshes; };