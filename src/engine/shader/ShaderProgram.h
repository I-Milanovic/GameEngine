#pragma once
#include <string>
#include "UniformMap.h"

class ShaderProgram {

	public:
		ShaderProgram(std::string shaderPath);

		unsigned int compileVertex(std::string source);
		unsigned int compileFragment(std::string source);

		//TODO void deleteShaderProgram();

		void useProgram();
		void detachProgram();
		void cleanup();

	//	inline unsigned int getProgramId() { return m_programId; };
		inline UniformMap& getUniformMap() { return m_uniformMap; };

	private: 
		unsigned int compile(std::string source, int type, std::string shaderTypeName);
		void link();
		void validate();

	private:
		unsigned int m_programId;
		UniformMap m_uniformMap;
};
