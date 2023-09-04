#include <glad/glad.h>
#include <iostream>

#include "ShaderProgram.h"
#include "../utilities/Loader.h"


	ShaderProgram::ShaderProgram(std::string shaderPath) {

		// Concat for the whole file name: path + file extension
		std::string vertexFile = shaderPath + ".vert";
		std::string fragmentFile = shaderPath + ".frag";


		// Instantiate class for file reading
		Loader* loader = new Loader();
		char *vertexSource = loader->read(vertexFile);
		char *fragmentSource = loader->read(fragmentFile);
		delete loader;

		// Create shader program
		programId = glCreateProgram();

		unsigned int vertexId = compileVertex(vertexSource);
		unsigned int fragmentId = compileFragment(fragmentSource);

		link();
		validate();
		
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
	
	}

	unsigned int ShaderProgram::compileVertex(char* source) {
		return compile(source, GL_VERTEX_SHADER, "Vertex");
	}

	unsigned int ShaderProgram::compileFragment(char* source) {
		return compile(source, GL_FRAGMENT_SHADER, "Fragment");
	}

	unsigned int ShaderProgram::compile(char* source, int type, std::string shaderTypeName) {

		// create shader name
		unsigned int shaderId = glCreateShader(type);

		if (shaderId == GL_FALSE) {
			std::cout << "Error creating shader, type: \n" << type << std::endl;
		}

		// Pass the shader code to the 
		glShaderSource(shaderId, 1, &source, NULL);
		glCompileShader(shaderId);

		// check for compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
			std::cout << "ERROR : HADER : VERTEX : COMPILATION FAILED\n" << infoLog << std::endl;
		}
		else {
			std::cout << shaderTypeName << " Shader Compiled!" << std::endl;
		}

		// Attach shader to the program
		glAttachShader(programId, shaderId);

		return shaderId;
	}

	void ShaderProgram::link() {
		glLinkProgram(programId);

		// Check for linking errors
		int success;
		char infoLog[512];
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(programId, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		} 
		else {
			std::cout << "Shader Program Linked" << std::endl;
		}
	}

	void ShaderProgram::validate() {
		glValidateProgram(programId);
		int success;
		char infoLog[512];

		glGetProgramiv(programId, GL_VALIDATE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(programId, 512, NULL, infoLog);
			std::cout << "ERROR VALIDATING PROGRAM\n" << infoLog << std::endl;
		}
		else {
			std::cout << "Shader Program Validated" << std::endl;
		}
	}

	void ShaderProgram::useProgram() {
		glUseProgram(programId);
	}

	void ShaderProgram::detachProgram() {
		glUseProgram(0);
	}

	void ShaderProgram::cleanup() {
		detachProgram();
		if (programId != 0) {
			glDeleteProgram(0);
		}
	}

	unsigned int ShaderProgram::getProgramId() {
		return programId;
	}
