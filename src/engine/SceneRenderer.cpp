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

#include "src/engine/scene/LoaderManager.h"


static unsigned int gridVao; // TODO uzas

SceneRenderer::SceneRenderer() :
    m_scene(Scene(1200, 1000)),
    m_shader(ShaderProgram("resources/shaders/shader", "MainShader")),
    m_lightShader(ShaderProgram("resources/shaders/lightShader", "LightShader")),
    m_gridShader(ShaderProgram("resources/shaders/grid", "GridShader")) {

    createUniforms();
    createGridUniforms();

    //Model loading move somewhere else
    LoaderManager loaderManager(m_scene.getModelCache(), m_scene.getMaterialCache(), m_scene.getTextureCache());
    std::string minecraftCube = "resources/models/minecraft_cube/minecraftcube.obj";
    std::string pyramidCubes = "resources/models/cube_test/cube_hierarchy.dae";
    std::string pyramidCubes2 = "resources/models/cube_test/cube_hierarchy_2.dae";
    std::string guardBob = "resources/models/bob/boblamp.md5mesh";
    std::string myChar = "resources/models/char/Character.fbx";
    bool isModel = false;
    loaderManager.loadModel(minecraftCube, isModel);

    
    if (isModel) {
        Model& model = *m_scene.getModelCache().getModel("CharacterMesh-Anim");
        model.getAnimationManager().setCurrentAnimationIdx(0);
        model.getEntity().getScale() = 0.01f;
        model.getEntity().updateModelMatrix();
    }
    // render endless grid
    glGenVertexArrays(1, &gridVao);
}

SceneRenderer::~SceneRenderer() {
    std::cout << "SceneRenderer Deleting" << std::endl;
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
            
    m_shader.getUniformMap().createUniform("bonesMatrices");

    m_shader.getUniformMap().createFogUniform("fog");

    m_lightShader.getUniformMap().createUniform("model");
    m_lightShader.getUniformMap().createUniform("view");
    m_lightShader.getUniformMap().createUniform("projection");
}

void SceneRenderer::createGridUniforms() {
    m_gridShader.getUniformMap().createUniform("view");
    m_gridShader.getUniformMap().createUniform("proj");
}

void SceneRenderer::setUniforms() {
    m_shader.getUniformMap().setAmbientLight("ambientLight", m_scene.getSceneLights().getAmbientLight());
    m_shader.getUniformMap().setDirLightUniform("dirLight", m_scene.getSceneLights().getDirLight());
    m_shader.getUniformMap().setPointLightListUniform("pointLights", m_scene.getSceneLights().getPointLights());
    m_shader.getUniformMap().setSpotLightListUniform("spotLights", m_scene.getSceneLights().getSpotLights());
    m_shader.getUniformMap().setFogUniform("fog", m_scene.getFog());
}

void SceneRenderer::renderScene() {
    glm::mat4 projectionMatrix = m_scene.getProjection().getProjectionMatrix();
    glm::mat4 orthoMatrix = m_scene.getProjection().getOrthoMatrix();

    m_scene.getProjection().updateProjection();
    m_scene.getProjection().updateOrtho();


    setUniforms();

    if(isOrhto) 
        m_shader.getUniformMap().setUniform("projectionMatrix", orthoMatrix);
    else
        m_shader.getUniformMap().setUniform("projectionMatrix", projectionMatrix);
}

void SceneRenderer::renderModels() {

    if (!m_scene.getModelCache().getModels()->size())
        return;

    m_shader.useProgram();


    for (auto& [modelName, model] : *m_scene.getModelCache().getModels()) {

        setUniforms();

        m_shader.getUniformMap().setUniform("projectionMatrix", m_scene.getProjection().getProjectionMatrix());
        glm::mat4 veiwMatrix = m_scene.getCamera().getViewMatrix();
        m_shader.getUniformMap().setUniform("viewMatrix", veiwMatrix);


        Material& material = m_scene.getMaterialCache().getMaterial(model.getMeshData().m_materialName);
        Texture& texture = m_scene.getTextureCache().getTexture(material.getTexturePath());

        if (material.hasTexture()) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
        }
        else {
            m_shader.getUniformMap().setMaterialUniform("material", material);
        }
        if (material.hasNormalTexture()) {
            Texture& t = m_scene.getTextureCache().getTexture(material.getNormalMapPath());
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, t.getTextureId());
        }

        glm::mat4 modelMatrix = model.getEntity().getModelMatrix();
        glBindVertexArray(model.getMesh().getVao());
        m_shader.getUniformMap().setUniform("modelMatrix", modelMatrix);

        

        if (model.getAnimationManager().hasCurrentAnimation()) {
            AnimationManager& animData = model.getAnimationManager();
            m_shader.getUniformMap().setUniform("bonesMatrices", animData.getCurrentFrame().m_boneMatrices);
        }
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(model.getMeshData().m_indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    m_shader.detachProgram();
}


void SceneRenderer::renderGrid() {
    m_gridShader.useProgram();
    glm::mat4 veiwMatrix = m_scene.getCamera().getViewMatrix();
    m_gridShader.getUniformMap().setUniform("view", veiwMatrix);
    m_gridShader.getUniformMap().setUniform("proj", m_scene.getProjection().getProjectionMatrix());
    glBindVertexArray(gridVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    m_gridShader.detachProgram();
}