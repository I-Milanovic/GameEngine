#pragma once
#include "Light.h"
#include <vector>

class SceneLights {

	public:
		inline AmbientLight& getAmbientLight() { return m_ambientLight; };
		inline DirLight& getDirLight() { return m_dirLight; };
		inline std::vector<PointLight>& getPointLights() { return m_pointLights; };
		inline std::vector<SpotLight>& getSpotLights() { return m_spotLights; };

		void addPointLights(std::vector<PointLight> pointLights);
		void addPointLight(PointLight pointLight);
		void removePointLight(int index);

		void addSpotLights(std::vector<SpotLight> spotLights);
		void addSpotLight(SpotLight spotLight);
		void removeSpotLight(int index);

		void setAmbientLight(AmbientLight& ambientLight);
		void setDirLight(DirLight dirLight);


	private:
		AmbientLight m_ambientLight;
		DirLight m_dirLight;
		std::vector<PointLight> m_pointLights;
		std::vector<SpotLight> m_spotLights;

};

