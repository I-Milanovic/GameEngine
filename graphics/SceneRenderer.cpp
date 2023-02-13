#include <glad/glad.h>

#include "SceneRenderer.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"

#include <string>

SceneRenderer::SceneRenderer() {
	// Create shader program
	shader = new ShaderProgram("resources/shaders/shader");
	// Create mesh to be displayed

	std::cout << sizeof(vertices) << std::endl;

	//mesh = new Mesh(vertices,  sizeof(vertices));
	mesh = new Mesh(vertices, sizeof(vertices), indices, sizeof(indices));

	std::string file = "resources/images/container.jpg";
	Texture* texture = new Texture(file);
}

void SceneRenderer::renderScene() {
	shader->useProgram();
	glBindVertexArray(mesh->getVao());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}