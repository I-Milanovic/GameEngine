#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <sstream>
#include <string>
#include <iostream>

#include "SceneRenderer.h"
#include "../window/Window.h"

#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

SceneRenderer::SceneRenderer(Scene scene) : m_scene(scene) {

    // Create m_shader program
    m_shader = new ShaderProgram("resources/shaders/basicShader");               // ovo je losa kompozicija
    createUniforms();

    // Create light Shader
    m_lightShader = new ShaderProgram("resources/shaders/lightShader");
    createLightUniforms();
     
    m_frameBuffer.init(1200, 800);

    // Create mesh to be displayed
    ModelLoader m_loader;
    m_loader.loadModel("resources/models/cube.obj");
    m_scene.setMeshes(m_loader.getMeshes());

    SpotLight spotLight;
    m_scene.addSpotLight(spotLight);
}


void SceneRenderer::createUniforms() {
    m_shader->getUniformMap().createUniform("modelMatrix");
    m_shader->getUniformMap().createUniform("viewMatrix");
    m_shader->getUniformMap().createUniform("projectionMatrix");

    m_shader->getUniformMap().createMaterial("material");
    m_shader->getUniformMap().createAmbientLight("ambientLight");
    m_shader->getUniformMap().createPointLightListUniform("pointLights", 5);
    m_shader->getUniformMap().createSpotLightListUniform("spotLights", 1);
    m_shader->getUniformMap().createDirLightUniform("dirLight");
}

void SceneRenderer::createLightUniforms() {
    m_lightShader->getUniformMap().createUniform("model");
    m_lightShader->getUniformMap().createUniform("view");
    m_lightShader->getUniformMap().createUniform("projection");
}

void SceneRenderer::renderScene() {

    m_frameBuffer.bindFrameBuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Mesh m = m_scene.getMesh(0);

    // cube object
    m_shader->useProgram();

    // Material
    Material mat = m.getMaterial();
    m_shader->getUniformMap().setMaterialUniform("material", mat);
    
    m_shader->getUniformMap().setAmbientLight("ambientLight", m_scene.getSceneLights().getAmbientLight());

    m_shader->getUniformMap().setDirLightUniform("dirLight", m_scene.getSceneLights().getDirLight());

    //if(m_scene.getSceneLights().getPointLights().size() > 0)
    m_shader->getUniformMap().setPointLightListUniform("pointLights", m_scene.getSceneLights().getPointLights());

    m_shader->getUniformMap().setSpotLightListUniform("spotLights", m_scene.getSceneLights().getSpotLights());

   
    // transformations
    // 
    m_scene.getProjection().updateProjection();
    glm::mat4 projectionMatrix = m_scene.getProjection().getProjectionMatrix();
    glm::mat4 viewMatrix = m_scene.getCamera()->getViewMatrix();

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    m_shader->getUniformMap().setUniform("modelMatrix", modelMatrix);

    m_shader->getUniformMap().setUniform("projectionMatrix", projectionMatrix);
    m_shader->getUniformMap().setUniform("viewMatrix", viewMatrix);

    // bind diffuse map
    if (m.getMaterial().m_hasTextures) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m.getTextureId(0));
    }

    glBindVertexArray(m.getVao());
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
    m_shader->getUniformMap().setUniform("modelMatrix", modelMatrix);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m.getIndicesSize()), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    //for (unsigned int i = 0; i < 10; i++) {
    //    // calculate the modelMatrix matrix for each and pass it to m_shader before drawing
    //    glm::mat4 modelMatrix = glm::mat4(1.0f);
    //    modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
    //    float angle = 20.0f * i;
    //    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    //    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
    //    m_shader->getUniformMap().setUniform("modelMatrix", modelMatrix);

    //   // glDrawArrays(GL_TRIANGLES, 0, 36);
    //    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->getIndicesSize()), GL_UNSIGNED_INT, 0);
    //}

    // light objects
    m_lightShader->useProgram();
    m_lightShader->getUniformMap().setUniform("projection", projectionMatrix);
    m_lightShader->getUniformMap().setUniform("view", viewMatrix);
   // glBindVertexArray(lightCube->getVao());
    
    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, pointLightPositions[i]);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        m_lightShader->getUniformMap().setUniform("model", modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    m_frameBuffer.unbindFrameBuffer();

    glBindVertexArray(0);


    
}

