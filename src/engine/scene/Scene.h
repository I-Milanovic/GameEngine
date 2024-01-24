#pragma once

#include "Projection.h"
#include "Camera.h"
#include "../scene/Mesh.h"
#include "lights/SceneLights.h"
#include "Fog.h"

#include <vector>

#include "ArcballCamera.h"
#include "QuatCamera.h"

class Scene {

public:
	Scene(int width, int height);

	void addMesh(Mesh mesh);
	Mesh& getMesh(int index) { return m_meshes.at(index); };
	inline std::vector<Mesh>& getMeshes() { return m_meshes; };
	void setMeshes(std::vector<Mesh> meshes);
	
	SceneLights& getSceneLights() { return m_sceneLights; };
	void addPointLight(PointLight pointLight);
	void removePointLight(int index);
	void addSpotLight(SpotLight spotLight);
	void setAmbientLight(AmbientLight& ambientLight);
	void setDirLight(DirLight dirLight);
	
public:
	Projection m_projection;
	Fog m_fog;
	QuatCamera m_quatCamera;

private: 
	std::vector<Mesh> m_meshes;
	SceneLights m_sceneLights;
};

