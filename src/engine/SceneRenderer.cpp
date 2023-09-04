#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include <iostream>

#include "SceneRenderer.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"
#include "UniformMap.h"


Texture* texture1;
Texture* texture2;

UniformMap* uniformMap;


std::string tex1 = "texture1";
std::string tex2 = "texture2";

std::string modelString = "model";
std::string viewString = "view";
std::string projectionString = "projection";

glm::mat4 projection;


SceneRenderer::SceneRenderer() {

 //   camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // Create shader program
    shader = new ShaderProgram("resources/shaders/shader");
    uniformMap = new UniformMap(shader->getProgramId());
    createUniforms();

    // Create mesh to be displayed

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
    
    projection = glm::perspective(glm::radians(m_camera.getZoom()), (float)800 / (float)600, 0.1f, 100.0f);
    uniformMap->setUniform(projectionString, projection);

    
    float radius = 10.0f;
    float camX = static_cast<float>(sin(glfwGetTime()) * radius);
    float camZ = static_cast<float>(cos(glfwGetTime()) * radius);

    glm::mat4 view = m_camera.getViewMatrix();
    uniformMap->setUniform(viewString, view);
    

    glBindVertexArray(mesh->getVao());
    for (unsigned int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model,	glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        uniformMap->setUniform(modelString, model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

}

