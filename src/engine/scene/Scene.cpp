#include "Scene.h"

Scene::Scene(int width, int height) :
	m_projection(Projection(45.0f, width, height, 100.0f, 0.1f)),
	m_meshes(std::vector<Mesh>()),
	m_sceneLights(SceneLights()), 
	m_quatCamera(QuatCamera(glm::vec3(0.0f, 0.0f, -5.0f))){
}

void Scene::addMesh(Mesh mesh) { 
	m_meshes.push_back(mesh); 
}

void Scene::addPointLight(PointLight pointLight) { 
	m_sceneLights.getPointLights().push_back(pointLight); 
}

void Scene::removePointLight(int index) { 
	m_sceneLights.getPointLights().erase(m_sceneLights.getPointLights().begin() + index); 
}

void Scene::addSpotLight(SpotLight spotLight) { 
	m_sceneLights.getSpotLights().push_back(spotLight);
}

void Scene::setAmbientLight(AmbientLight& ambientLight) { 
	m_sceneLights.setAmbientLight(ambientLight);
}

void Scene::setDirLight(DirLight dirLight) {
	m_sceneLights.setDirLight(dirLight); 
}

void Scene::setMeshes(std::vector<Mesh> meshes) {
	m_meshes = meshes; 
}