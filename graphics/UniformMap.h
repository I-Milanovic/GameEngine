#pragma once

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;
class UniformMap {

private:
	int programId;
	unordered_map<string, unsigned int> uniforms;

public:
	UniformMap(int programId);

	void createUniform(string &uniformName);
	
	void setUniform(string &uniformName, bool value) const;

	void setUniform(string &uniformName, int value) const;

	void setUniform(string& uniformName, float value) const;

	void setUniform(string& uniformName, vec2 &value) const;

	void setUniform(string& uniformName, vec3 &value) const;

	void setUniform(string& uniformName, vec4 &value) const;

	void setUniform(string& uniformName, mat2 &value) const;

	void setUniform(string& uniformName, mat3 &value) const;

	void setUniform(string &uniformName, mat4 &value) const;


private:
	int getUniformLocation(string &uniformName) const;



};