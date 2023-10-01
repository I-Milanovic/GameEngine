#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class UniformMap {

public:
	UniformMap(int programId);
	
	void createUniform(const std::string& uniformName);

	void setUniform(const std::string& uniformName, bool value) const;
					
	void setUniform(const std::string& uniformName, int value) const;
				
	void setUniform(const std::string& uniformName, float value) const;
				
	void setUniform(const std::string& uniformName, glm::vec2 &value) const;
				
	void setUniform(const std::string& uniformName, const glm::vec3 &value) const;
				
	void setUniform(const std::string& uniformName, glm::vec4 &value) const;
					
	void setUniform(const std::string& uniformName, glm::mat2 &value) const;
				
	void setUniform(const std::string& uniformName, glm::mat3 &value) const;
					
	void setUniform(const std::string& uniformName, glm::mat4 &value) const;


private:
	int getUniformLocation(const std::string& uniformName) const;

private:
	int programId;
	std::unordered_map<std::string, unsigned int> uniforms;


};