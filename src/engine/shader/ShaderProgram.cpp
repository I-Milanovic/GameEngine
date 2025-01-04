#include "ShaderProgram.h"
#include "../../utilities/FileLoader.h"

#include <glad/glad.h>
#include <iostream>



	ShaderProgram::ShaderProgram(std::string shaderPath, std::string shaderName) :
			m_programId(glCreateProgram()), m_uniformMap(m_programId, shaderName) {

		// Concat for the whole file name: path + file extension
		std::string vertexFile = shaderPath + ".vert";
		std::string fragmentFile = shaderPath + ".frag";

		FileLoader loader;
		unsigned int vertexId = compileVertex(loader.readFile(vertexFile));
		unsigned int fragmentId = compileFragment(loader.readFile(fragmentFile));

		link();
		validate();
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
	
	}

	unsigned int ShaderProgram::compileVertex(std::string source) {
		return compile(source, GL_VERTEX_SHADER, "Vertex");
	}

	unsigned int ShaderProgram::compileFragment(std::string source) {
		return compile(source, GL_FRAGMENT_SHADER, "Fragment");
	}

	unsigned int ShaderProgram::compile(std::string source, int type, std::string shaderTypeName) {

		// createDirectory m_shader name
		unsigned int shaderId = glCreateShader(type);

		if (shaderId == GL_FALSE) {
			std::cout << "Error creating shader:" << m_shaderName << " type: \n" << type << std::endl;
		}

		// Pass the m_shader code to the
		const char* c = source.c_str();
		glShaderSource(shaderId, 1, &c, NULL);
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
			std::cout << m_shaderName << " : " << shaderTypeName << " Shader Compiled!" << std::endl;
		}

		// Attach m_shader to the program
		glAttachShader(m_programId, shaderId);

		return shaderId;
	}

	void ShaderProgram::link() {
		glLinkProgram(m_programId);

		// Check for linking errors
		int success;
		char infoLog[512];
		glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		} 
		else {
			std::cout << m_shaderName << " Shader Program Linked" << std::endl;
		}
	}

	void ShaderProgram::validate() {
		glValidateProgram(m_programId);
		int success;
		char infoLog[512];

		glGetProgramiv(m_programId, GL_VALIDATE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
			std::cout << "ERROR VALIDATING PROGRAM\n" << infoLog << std::endl;
		}
		else {
			std::cout << m_shaderName << " Shader Program Validated" << std::endl;
		}
	}

	void ShaderProgram::useProgram() {
		glUseProgram(m_programId);
	}

	void ShaderProgram::detachProgram() {
		glUseProgram(0);
	}

	void ShaderProgram::cleanup() {
		detachProgram();
		if (m_programId != 0) {
			glDeleteProgram(0);
		}
	}
