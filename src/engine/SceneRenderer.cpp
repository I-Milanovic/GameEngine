#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <sstream>
#include <string>
#include <iostream>

#include "SceneRenderer.h"
#include "../window/Window.h"

#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "glm/matrix.hpp"

static unsigned int gridVao;

SceneRenderer::SceneRenderer(Scene scene) : m_scene(scene),
m_shader(ShaderProgram("resources/shaders/basicShader")),
m_lightShader(ShaderProgram("resources/shaders/lightShader")),
m_gridShader(ShaderProgram("resources/shaders/grid")) {

    createUniforms();
    createLightUniforms();
    createGridUniforms();

    // Create mesh to be displayed
    ModelLoader m_loader;
    m_loader.loadModel("resources/models/cube.obj");
    m_scene.setMeshes(m_loader.getMeshes());

    SpotLight spotLight;
    m_scene.addSpotLight(spotLight);

    glGenVertexArrays(1, &gridVao);
}

void SceneRenderer::createGridUniforms() {
    m_gridShader.getUniformMap().createUniform("view");
    m_gridShader.getUniformMap().createUniform("proj");
    m_gridShader.getUniformMap().createUniform("pos");
}

void SceneRenderer::setGridUniforms() {

}

void SceneRenderer::createUniforms() {
    m_shader.getUniformMap().createUniform("modelMatrix");
    m_shader.getUniformMap().createUniform("viewMatrix");
    m_shader.getUniformMap().createUniform("projectionMatrix");
            
    m_shader.getUniformMap().createMaterial("material");
    m_shader.getUniformMap().createAmbientLight("ambientLight");
    m_shader.getUniformMap().createPointLightListUniform("pointLights", 5);
    m_shader.getUniformMap().createSpotLightListUniform("spotLights", 1);
    m_shader.getUniformMap().createDirLightUniform("dirLight");
            
    m_shader.getUniformMap().createFogUniform("fog");
}
void SceneRenderer::createLightUniforms() {
    m_lightShader.getUniformMap().createUniform("model");
    m_lightShader.getUniformMap().createUniform("view");
    m_lightShader.getUniformMap().createUniform("projection");
}

void SceneRenderer::setUniforms() {
    m_shader.getUniformMap().setMaterialUniform("material", m_scene.getMesh(0).getMaterial());
    m_shader.getUniformMap().setAmbientLight("ambientLight", m_scene.getSceneLights().getAmbientLight());
    m_shader.getUniformMap().setDirLightUniform("dirLight", m_scene.getSceneLights().getDirLight());
    m_shader.getUniformMap().setPointLightListUniform("pointLights", m_scene.getSceneLights().getPointLights());
    m_shader.getUniformMap().setSpotLightListUniform("spotLights", m_scene.getSceneLights().getSpotLights());
    m_shader.getUniformMap().setFogUniform("fog", m_scene.m_fog);
}

void SceneRenderer::renderScene() {
 

    //m_scene.m_projection.setProjFov(m_scene.getCamera().getFov());
    //m_scene.m_projection.setOrthoSize(m_scene.getCamera().getOrthoZoom());

    glm::mat4 projectionMatrix = m_scene.m_projection.getProjectionMatrix();
    glm::mat4 orthoMatrix = m_scene.m_projection.getOrthoMatrix();
 //   glm::mat4 viewMatrix = m_scene.m_quatCamera.viewMat;
//    glm::mat4 modelMatrix = m_scene.getMesh(0).getModelMatrix();

    m_scene.m_projection.updateProjection();
    m_scene.m_projection.updateOrtho();


    //m_shader.useProgram();
    //setUniforms();

    if(isOrhto) 
        m_shader.getUniformMap().setUniform("projectionMatrix", orthoMatrix);
    else
        m_shader.getUniformMap().setUniform("projectionMatrix", projectionMatrix);

   // m_shader.getUniformMap().setUniform("viewMatrix", viewMatrix);
 
    // bind diffuse map
    //if (m_scene.getMesh(0).getMaterial().m_hasTextures) {
    //    glActiveTexture(GL_TEXTURE0);
    //    glBindTexture(GL_TEXTURE_2D, m_scene.getMesh(0).getTextureId(0));
    //}

    //if (m_scene.getMesh(0).isRendered) {
    //    glBindVertexArray(m_scene.getMesh(0).getVao());
    //    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
    //    m_shader.getUniformMap().setUniform("modelMatrix", modelMatrix);
    //    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_scene.getMesh(0).getIndicesSize()), GL_UNSIGNED_INT, 0);
    //    glBindVertexArray(0);

         //light objects
        //m_lightShader.useProgram();
        //m_lightShader.getUniformMap().setUniform("projection", projectionMatrix);
        //m_lightShader.getUniformMap().setUniform("view", viewMatrix);
        // glBindVertexArray(lightCube->getVao());

        //for (int i = 0; i < 4; i++) {
        //    modelMatrix = glm::mat4(1.0f);
        //    modelMatrix = glm::translate(modelMatrix, pointLightPositions[i]);
        //    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        //    m_lightShader.getUniformMap().setUniform("model", modelMatrix);
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //}

        //glBindVertexArray(0);
   // }


}

void SceneRenderer::renderCube() {

    glm::mat4 modelMatrix = m_scene.getMesh(0).getModelMatrix();

    m_shader.useProgram();
    setUniforms();
    m_shader.getUniformMap().setUniform("projectionMatrix", m_scene.m_projection.m_projectionMatrix);
    m_shader.getUniformMap().setUniform("viewMatrix", m_scene.m_quatCamera.viewMat);

    if (m_scene.getMesh(0).getMaterial().m_hasTextures) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_scene.getMesh(0).getTextureId(0));
    }

    if (m_scene.getMesh(0).isRendered) {
        glBindVertexArray(m_scene.getMesh(0).getVao());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        m_shader.getUniformMap().setUniform("modelMatrix", modelMatrix);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_scene.getMesh(0).getIndicesSize()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    m_shader.detachProgram();
}


void SceneRenderer::renderGrid() {
    m_gridShader.useProgram();
    m_gridShader.getUniformMap().setUniform("view", m_scene.m_quatCamera.viewMat);
    m_gridShader.getUniformMap().setUniform("proj", m_scene.m_projection.m_projectionMatrix);
    glBindVertexArray(gridVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    m_gridShader.detachProgram();
}

void SceneRenderer::renderScatteredBoxes() {
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
}
