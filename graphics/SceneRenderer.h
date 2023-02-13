#pragma once
#include "ShaderProgram.h"
#include "Mesh.h"


class SceneRenderer {
private:
	ShaderProgram* shader;
	Mesh* mesh;
	const float vertices[32] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 	
	};

	const int indices[6] = {
	   0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

public:
	SceneRenderer();
	void renderScene();

};