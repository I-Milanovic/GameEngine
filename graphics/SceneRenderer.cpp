#include <glad/glad.h>

#include "SceneRenderer.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"
#include "UniformMap.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

Texture* texture1;
Texture* texture2;

UniformMap* uniformMap;

std::string tex1 = "texture1";
std::string tex2 = "texture2";

SceneRenderer::SceneRenderer() {


	// Create shader program
	shader = new ShaderProgram("resources/shaders/shader");
	uniformMap = new UniformMap(shader->getProgramId());
	createUniforms();

	// Create mesh to be displayed
	std::cout << sizeof(vertices) << std::endl;

	//mesh = new Mesh(vertices,  sizeof(vertices));
	mesh = new Mesh(vertices, sizeof(vertices), indices, sizeof(indices));

	std::string file = "resources/images/container.jpg";
	texture2 = new Texture(file, false);

	std::string fileFace = "resources/images/awesomeface.png";
	texture1 = new Texture(fileFace, true);

	shader->useProgram();
	uniformMap->setUniform(tex1, 0);
	uniformMap->setUniform(tex2, 1);
}

std::string transformString = "transform";

void SceneRenderer::createUniforms() {


	uniformMap->createUniform(transformString);

	uniformMap->createUniform(tex1);
	uniformMap->createUniform(tex2);
}


void SceneRenderer::renderScene() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1->getTextureId());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2->getTextureId());


	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.5f, -0.05f, 0.0f));
	transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));


	shader->useProgram();



	uniformMap->setUniform(transformString, transform);

	glBindVertexArray(mesh->getVao());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}