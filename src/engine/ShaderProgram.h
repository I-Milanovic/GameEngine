#pragma once
#include <string>

class ShaderProgram {

private:
	unsigned int programId;
	//char* vertexSource;
	//char* fragmentSource;


public:
	ShaderProgram(std::string shaderPath);

	unsigned int compileVertex(char* source);
	unsigned int compileFragment(char* source);

	//TODO void deleteShaderProgram();

	void useProgram();
	void detachProgram();
	void cleanup();

	unsigned int getProgramId();
	
private: 
	unsigned int compile(char* source, int type, std::string shaderTypeName);
	void link();
	void validate();
};
