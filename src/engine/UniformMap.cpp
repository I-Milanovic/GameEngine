#include <iostream>
#include <glad/glad.h>

#include "UniformMap.h"



UniformMap::UniformMap(int programId):programId(programId) {

}

void UniformMap::createUniform(const std::string &uniformName) {
	unsigned int uniformLocation = glGetUniformLocation(programId, uniformName.c_str());

	if (uniformLocation < 0) {
		// TODO better set exception than just print
		std::cout << "Could not find uniform " << uniformName << " in shader program " <<
			programId << std::endl;
	}
	else {
		std::cout << "Uniform created: " << uniformName << " at location: " << uniformLocation << std::endl;
		uniforms[uniformName] = uniformLocation;
	}
}

int UniformMap::getUniformLocation(const std::string &uniformName) const{

	bool isContained = uniforms.contains(uniformName);

	if(!isContained) 
		std::cout << "ERROR : Uniform not in List: " << uniformName << std::endl;

	int location = uniforms.at(uniformName);

	if (location < 0) {
		// TODO set exception
		std::cout << "Could not find uniform: " << location << " " << uniformName << std::endl;
	}

	return location;
}

void UniformMap::setUniform(const std::string& uniformName, bool value) const {
	glUniform1i(getUniformLocation(uniformName), value);
}

void UniformMap::setUniform(const std::string& uniformName, int value) const {
	glUniform1i(getUniformLocation(uniformName), value);
}

void UniformMap::setUniform(const std::string& uniformName, float value) const {
	glUniform1f(getUniformLocation(uniformName), value);
}

void UniformMap::setUniform(const std::string& uniformName, glm::vec2 &value) const {
	glUniform2fv(getUniformLocation(uniformName), 1, &value[0]);
}

void UniformMap::setUniform(const std::string& uniformName, const glm::vec3 &value) const {
	glUniform3fv(getUniformLocation(uniformName), 1, &value[0]);
}

void UniformMap::setUniform(const std::string& uniformName, glm::vec4 &value) const {
	glUniform4fv(getUniformLocation(uniformName), 1, &value[0]);
}

void UniformMap::setUniform(const std::string& uniformName, glm::mat2 &value) const {
	glUniformMatrix2fv(getUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void UniformMap::setUniform(const std::string& uniformName, glm::mat3 &value) const {
	glUniformMatrix3fv(getUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void UniformMap::setUniform(const std::string& uniformName, glm::mat4 &value) const {
	glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}