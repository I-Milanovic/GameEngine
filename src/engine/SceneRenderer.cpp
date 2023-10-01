#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <sstream>
#include <string>

#include <iostream>

#include "SceneRenderer.h"
#include "ShaderProgram.h"
#include "Mesh.h"


SceneRenderer::SceneRenderer() {

    // Create shader program
    shader = new ShaderProgram("resources/shaders/shader");
    uniformMap = new UniformMap(shader->getProgramId());                // ovo je losa kompozicija
    createUniforms();

    // Create light Shader
    lightShader = new ShaderProgram("resources/shaders/lightShader");
    lightUniformMap = new UniformMap(lightShader->getProgramId());
    createLightUniforms();


    // Create mesh to be displayed
    //mesh = new Mesh(vertices,  sizeof(vertices));
    mesh = new Mesh(vertices, sizeof(vertices), indices, sizeof(indices));
    lightCube = new Mesh(vertices, sizeof(vertices), indices, sizeof(indices));

    texture1 = new Texture("resources/images/container2.png");
    texture2 = new Texture("resources/images/container2_specular.png");

    //shader->useProgram();
}

void SceneRenderer::createUniforms() {
    uniformMap->createUniform("model");
    uniformMap->createUniform("view");
    uniformMap->createUniform("projection");

    uniformMap->createUniform("material.diffuse");
    uniformMap->createUniform("material.specular");
    uniformMap->createUniform("material.shininess");

    for (int i = 0; i < 4; i++) {
        std::string s = std::to_string(i);
        uniformMap->createUniform("pointLights[" + s + "].position");
        uniformMap->createUniform("pointLights[" + s + "].att.constant");
        uniformMap->createUniform("pointLights[" + s + "].att.linear");
        uniformMap->createUniform("pointLights[" + s + "].att.quadratic");

        uniformMap->createUniform("pointLights[" + s + "].lightComp.ambient");
        uniformMap->createUniform("pointLights[" + s + "].lightComp.diffuse");
        uniformMap->createUniform("pointLights[" + s + "].lightComp.specular");
    }

    uniformMap->createUniform("dirLight.direction");
    uniformMap->createUniform("dirLight.lightComp.ambient");
    uniformMap->createUniform("dirLight.lightComp.diffuse");
    uniformMap->createUniform("dirLight.lightComp.specular");

    uniformMap->createUniform("spotLight.position");
    uniformMap->createUniform("spotLight.direction");
    uniformMap->createUniform("spotLight.cutOff");
    uniformMap->createUniform("spotLight.outerCutOff");
    uniformMap->createUniform("spotLight.att.constant");
    uniformMap->createUniform("spotLight.att.linear");
    uniformMap->createUniform("spotLight.att.quadratic");
    uniformMap->createUniform("spotLight.lightComp.ambient");
    uniformMap->createUniform("spotLight.lightComp.diffuse");
    uniformMap->createUniform("spotLight.lightComp.specular");


    uniformMap->createUniform("viewPos");
}

void SceneRenderer::createLightUniforms() {
    lightUniformMap->createUniform("model");
    lightUniformMap->createUniform("view");
    lightUniformMap->createUniform("projection");
}

void SceneRenderer::renderScene() {
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    // cube object
    shader->useProgram();

    // light properties
    //uniformMap->setUniform("material.diffuse", 0);
    //uniformMap->setUniform("material.specular", 1);
    uniformMap->setUniform("viewPos", m_camera.getPos());
    uniformMap->setUniform("material.shininess", 32.0f);

    // directional light
    uniformMap->setUniform("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    uniformMap->setUniform("dirLight.lightComp.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
    uniformMap->setUniform("dirLight.lightComp.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    uniformMap->setUniform("dirLight.lightComp.specular", glm::vec3(0.5f, 0.5f, 0.5f));

    // point light 1
    uniformMap->setUniform("pointLights[0].position", pointLightPositions[0]);
    uniformMap->setUniform("pointLights[0].lightComp.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
    uniformMap->setUniform("pointLights[0].lightComp.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    uniformMap->setUniform("pointLights[0].lightComp.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    uniformMap->setUniform("pointLights[0].att.constant", 1.0f);
    uniformMap->setUniform("pointLights[0].att.linear", 0.09f);
    uniformMap->setUniform("pointLights[0].att.quadratic", 0.032f);
    // point light 2
    uniformMap->setUniform("pointLights[1].position", pointLightPositions[1]);
    uniformMap->setUniform("pointLights[1].lightComp.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
    uniformMap->setUniform("pointLights[1].lightComp.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    uniformMap->setUniform("pointLights[1].lightComp.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    uniformMap->setUniform("pointLights[1].att.constant", 1.0f);
    uniformMap->setUniform("pointLights[1].att.linear", 0.09f);
    uniformMap->setUniform("pointLights[1].att.quadratic", 0.032f);
    // point light 3
    uniformMap->setUniform("pointLights[2].position", pointLightPositions[2]);
    uniformMap->setUniform("pointLights[2].lightComp.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
    uniformMap->setUniform("pointLights[2].lightComp.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    uniformMap->setUniform("pointLights[2].lightComp.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    uniformMap->setUniform("pointLights[2].att.constant", 1.0f);
    uniformMap->setUniform("pointLights[2].att.linear", 0.09f);
    uniformMap->setUniform("pointLights[2].att.quadratic", 0.032f);
    // point light 4
    uniformMap->setUniform("pointLights[3].position", pointLightPositions[3]);
    uniformMap->setUniform("pointLights[3].lightComp.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
    uniformMap->setUniform("pointLights[3].lightComp.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    uniformMap->setUniform("pointLights[3].lightComp.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    uniformMap->setUniform("pointLights[3].att.constant", 1.0f);
    uniformMap->setUniform("pointLights[3].att.linear", 0.09f);
    uniformMap->setUniform("pointLights[3].att.quadratic", 0.032f);

    // spot light
    uniformMap->setUniform("spotLight.position", m_camera.getPos());
    uniformMap->setUniform("spotLight.direction", m_camera.getFront());
    uniformMap->setUniform("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    uniformMap->setUniform("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    uniformMap->setUniform("spotLight.lightComp.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
    uniformMap->setUniform("spotLight.lightComp.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    uniformMap->setUniform("spotLight.lightComp.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    uniformMap->setUniform("spotLight.att.constant", 1.0f);
    uniformMap->setUniform("spotLight.att.linear", 0.09f);
    uniformMap->setUniform("spotLight.att.quadratic", 0.032f);

    // transformations
    projection = glm::perspective(glm::radians(m_camera.getZoom()), (float)800 / (float)600, 0.1f, 100.0f);
    glm::mat4 view = m_camera.getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    uniformMap->setUniform("model", model);

    uniformMap->setUniform("projection", projection);
    uniformMap->setUniform("view", view);

    // bind diffuse map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1->getTextureId());

    // bind specular map
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2->getTextureId());

    glBindVertexArray(mesh->getVao());
    for (unsigned int i = 0; i < 10; i++) {
        // calculate the model matrix for each and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        uniformMap->setUniform("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // light objects
    lightShader->useProgram();
    lightUniformMap->setUniform("projection", projection);
    lightUniformMap->setUniform("view", view);
    glBindVertexArray(lightCube->getVao());
    
    for (int i = 0; i < 4; i++) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.2f));
        lightUniformMap->setUniform("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
}

