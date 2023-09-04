#include <iostream>
#include <glad/glad.h>

#include "UniformMap.h"



UniformMap::UniformMap(int programId):programId(programId) {

}


void UniformMap::createUniform(string &uniformName) {
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

int UniformMap::getUniformLocation(string &uniformName) const{
	unsigned int location = uniforms.at(uniformName);

	if (location < 0) {
		// TODO set exception
		std::cout << "Could not find uniform: " << uniformName << std::endl;
	}

	return location;
}

void UniformMap::setUniform(string& uniformName, bool value) const {
	glUniform1i(getUniformLocation(uniformName), value);
}

void UniformMap::setUniform(string& uniformName, int value) const {
	glUniform1i(getUniformLocation(uniformName), value);
}

void UniformMap::setUniform(string& uniformName, float value) const {
	glUniform1f(getUniformLocation(uniformName), value);
}

void UniformMap::setUniform(string& uniformName, vec2 &value) const {
	glUniform2fv(getUniformLocation(uniformName), 1, &value[0]);
}

void UniformMap::setUniform(string& uniformName, vec3 &value) const {
	glUniform3fv(getUniformLocation(uniformName), 1, &value[0]);
}

void UniformMap::setUniform(string& uniformName, vec4 &value) const {
	glUniform4fv(getUniformLocation(uniformName), 1, &value[0]);
}

void UniformMap::setUniform(string& uniformName, mat2 &value) const {
	glUniformMatrix2fv(getUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void UniformMap::setUniform(string& uniformName, mat3 &value) const {
	glUniformMatrix3fv(getUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}

void UniformMap::setUniform(string& uniformName, mat4 &value) const {
	glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, &value[0][0]);
}