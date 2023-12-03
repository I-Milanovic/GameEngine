#pragma once

#include "Projection.h"
#include "Camera.h"
#include "../Mesh.h"
#include "lights/SceneLights.h"
#include "Fog.h"

#include <vector>

class Scene {

	public:
		Scene(int width, int height);
		Camera& getCamera() { return m_camera; };
		Projection& getProjection() { return m_projection; };
		SceneLights& getSceneLights() { return m_sceneLights; };

		Mesh& getMesh(int index) { return m_meshes.at(index); };
		void addMesh(Mesh mesh);
		
		void addPointLight(PointLight pointLight);
		void removePointLight(int index);

		void addSpotLight(SpotLight spotLight);
		
		void setAmbientLight(AmbientLight& ambientLight);
		void setDirLight(DirLight dirLight);
		
		std::vector<Mesh> getMeshes();
		void setMeshes(std::vector<Mesh> meshes);

		inline Fog& getFog() { return fog; };

	private: 
		Camera m_camera;
		Projection m_projection;
		std::vector<Mesh> m_meshes;
		SceneLights m_sceneLights;
		Fog fog;
};

