#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <sstream>
#include <string>

#include <iostream>

#include "SceneRenderer.h"
#include "ShaderProgram.h"
#include "Mesh.h"

#include "Light.h"


#include "glm/ext.hpp" 
#include "glm/gtx/string_cast.hpp"

SceneRenderer::SceneRenderer() {

    // Create shader program
    shader = new ShaderProgram("resources/shaders/basicShader");               // ovo je losa kompozicija
    createUniforms();

    // Create light Shader
    lightShader = new ShaderProgram("resources/shaders/lightShader");
    createLightUniforms();
     
    // Create mesh to be displayed
    m_loader.loadModel("resources/models/cube.obj");
    std::vector<Mesh> v = m_loader.getMeshes();
    mesh = new Mesh(v.at(0));
    lightCube = new Mesh(v.at(0));
}

void SceneRenderer::createUniforms() {
    shader->getUniformMap().createUniform("modelMatrix");
    shader->getUniformMap().createUniform("viewMatrix");
    shader->getUniformMap().createUniform("projectionMatrix");

    shader->getUniformMap().createMaterial("material");
    shader->getUniformMap().createAmbientLight("ambientLight");
    shader->getUniformMap().createPointLightListUniform("pointLights", 1);
    shader->getUniformMap().createSpotLightListUniform("spotLights", 1);
    shader->getUniformMap().createDirLightUniform("dirLight");

}

void SceneRenderer::createLightUniforms() {
    lightShader->getUniformMap().createUniform("model");
    lightShader->getUniformMap().createUniform("view");
    lightShader->getUniformMap().createUniform("projection");
}

void SceneRenderer::renderScene() {
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    // cube object
    shader->useProgram();

    // Material
    Material mat = mesh->getMaterial();
    shader->getUniformMap().setMaterialUniform("material", mat);
    
    AmbientLight ambientLight(1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    shader->getUniformMap().setAmbientLight("ambientLight", ambientLight);

    Attenuation att1(1.0f, 1.0f, 1.0f);
    PointLight pointLight1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, att1);
    std::vector<PointLight> v;
    v.push_back(pointLight1);
    shader->getUniformMap().setPointLightListUniform("pointLights", v);

    Attenuation att2(1.0f, 1.0f, 1.0f);
    PointLight pointLight2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, att2);
    SpotLight spotLight(pointLight2, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
    std::vector<SpotLight> s;
    s.push_back(spotLight);
    shader->getUniformMap().setSpotLightListUniform("spotLights", s);

    DirLight dirLight(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
    shader->getUniformMap().setDirLightUniform("dirLight", dirLight);

    // transformations
    projection = glm::perspective(glm::radians(m_camera.getZoom()), (float)800 / (float)600, 0.1f, 100.0f);
    glm::mat4 view = m_camera.getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    shader->getUniformMap().setUniform("modelMatrix", model);

    shader->getUniformMap().setUniform("projectionMatrix", projection);
    shader->getUniformMap().setUniform("viewMatrix", view);

    // bind diffuse map
    if (mesh->getMaterial().m_hasTextures) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->getTextureId(0));
    }
    //    glActiveTexture(GL_TEXTURE1);
    //    glBindTexture(GL_TEXTURE_2D, mesh->getTextureId(0));
    //}
    glBindVertexArray(mesh->getVao());
    //glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.5f));
    shader->getUniformMap().setUniform("modelMatrix", model);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->getIndicesSize()), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    //for (unsigned int i = 0; i < 10; i++) {
    //    // calculate the model matrix for each and pass it to shader before drawing
    //    glm::mat4 model = glm::mat4(1.0f);
    //    model = glm::translate(model, cubePositions[i]);
    //    float angle = 20.0f * i;
    //    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    //    model = glm::scale(model, glm::vec3(0.5f));
    //    shader->getUniformMap().setUniform("model", model);

    //   // glDrawArrays(GL_TRIANGLES, 0, 36);
    //    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->getIndicesSize()), GL_UNSIGNED_INT, 0);
    //}

    // light objects
    lightShader->useProgram();
    lightShader->getUniformMap().setUniform("projection", projection);
    lightShader->getUniformMap().setUniform("view", view);
   // glBindVertexArray(lightCube->getVao());
    
    for (int i = 0; i < 4; i++) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader->getUniformMap().setUniform("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
    
}

