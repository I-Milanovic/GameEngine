#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "shader/ShaderProgram.h"
#include "shader/UniformMap.h"

#include "../engine/ModelLoader.h"
#include "scene/Scene.h"


class SceneRenderer {

public:
    SceneRenderer(Scene scene);
    void createGridUniforms();
    void setGridUniforms();
    void renderScene();
    void renderCube();
    void renderGrid();

private:
    void createUniforms();
    void createLightUniforms();
    void setUniforms();
    void renderScatteredBoxes();
  
public:
    Scene m_scene;
    ShaderProgram m_shader;
    ShaderProgram m_lightShader;
    ShaderProgram m_gridShader;
    bool isOrhto = false;

private:
    glm::vec3 cubePositions[10] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[4] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };

};