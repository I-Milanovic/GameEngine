#pragma once

#include "Projection.h"
#include "Camera.h"
#include "../Mesh.h"
#include "lights/SceneLights.h"
#include <vector>

class Scene {

	public:
		Scene(int width, int height);
		Camera* getCamera();
		Projection& getProjection();
		SceneLights& getSceneLights();
		Mesh getMesh(int index);
		void addMesh(Mesh mesh);
		
		void addPointLight(PointLight pointLight);
		void removePointLight(int index);

		void addSpotLight(SpotLight spotLight);
		
		void setAmbientLight(AmbientLight& ambientLight);
		void setDirLight(DirLight dirLight);
		
		std::vector<Mesh> getMeshes();
		void setMeshes(std::vector<Mesh> meshes);

	private: 
		Projection m_projection;
		Camera m_camera;
		std::vector<Mesh> m_meshes;
		SceneLights m_sceneLights;
};

