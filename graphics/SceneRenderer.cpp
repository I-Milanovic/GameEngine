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

std::string modelString = "model";
std::string viewString = "view";
std::string projectionString = "projection";

void SceneRenderer::createUniforms() {


	uniformMap->createUniform(modelString);
	uniformMap->createUniform(viewString);
	uniformMap->createUniform(projectionString);

	uniformMap->createUniform(tex1);
	uniformMap->createUniform(tex2);
}


void SceneRenderer::renderScene() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1->getTextureId());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2->getTextureId());

	shader->useProgram();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);


	uniformMap->setUniform(modelString, model);
	uniformMap->setUniform(viewString, view);
	uniformMap->setUniform(projectionString, projection);

	glBindVertexArray(mesh->getVao());
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}