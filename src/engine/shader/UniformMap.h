#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

#include "../scene/lights/Light.h"
#include "../scene/Mesh.h"

#include "src/engine/scene/Material.h"

#include "../scene/Fog.h"

class UniformMap {

public:
	UniformMap(int programId, std::string shaderName);
	
	void createUniform(const std::string& uniformName);

	void setUniform(const std::string& uniformName, bool value) const;
					
	void setUniform(const std::string& uniformName, int value) const;
				
	void setUniform(const std::string& uniformName, float value) const;
				
	void setUniform(const std::string& uniformName, const glm::vec2 &value) const;
				
	void setUniform(const std::string& uniformName, const glm::vec3 &value) const;
				
	void setUniform(const std::string& uniformName, const glm::vec4 &value) const;
													
	void setUniform(const std::string& uniformName, const glm::mat2 &value) const;
													 
	void setUniform(const std::string& uniformName, const glm::mat3 &value) const;
					
	void setUniform(const std::string& uniformName, const glm::mat4 &value) const;

	void setUniform(const std::string& uniformName, std::vector<glm::mat4>& value);

public:
	void createAmbientLight(const std::string& uniformName);

	void createAttenuation(const std::string& uniformName);

	void createMaterial(const std::string& uniformName);

	void createPointLightUniform(const std::string& uniformName);
	void createDirLightUniform(const std::string& uniformName);
	void createSpotLightUniform(const std::string& uniformNae);

	void createFogUniform(const std::string& uniformName);

	void createPointLightListUniform(const std::string& uniformName, unsigned int size);
	void createDirLightListUniform(const std::string& uniformName, unsigned int size);
	void createSpotLightListUniform(const std::string& uniformName, unsigned int size);

public:
	void setAmbientLight(const std::string& uniformName, AmbientLight ambientLight);

	void setAttenuationUniform(const std::string& uniformName, Attenuation attenuation);

	void setMaterialUniform(const std::string& uniformName, Material material);

	void setPointLightUniform(const std::string& uniformName, PointLight pointLight);
	void setDirLightUniform(const std::string& uniformName, DirLight dirLight);
	void setSpotLightUniform(const std::string& uniformName, SpotLight spotLight);

	void setPointLightListUniform(const std::string& uniformName, std::vector<PointLight> pointLights);
	void setDirLightListUniform(const std::string& uniformName, std::vector<DirLight> dirLights);
	void setSpotLightListUniform(const std::string& uniformName, std::vector<SpotLight> spotLights);

	void setFogUniform(const std::string& uniformName, Fog m_fog);


private:
	int getUniformLocation(const std::string& uniformName) const;

private:
	int m_programId;
	std::unordered_map<std::string, unsigned int> m_uniformMap;
	std::string m_shaderName;
};