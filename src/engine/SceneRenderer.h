#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "shader/ShaderProgram.h"
#include "shader/UniformMap.h"

#include "scene/Scene.h"

#include "src/engine/scene/MaterialCache.h"
#include "src/engine/scene/TextureCache.h"

class SceneRenderer {

public:
    SceneRenderer();
    ~SceneRenderer();
    void renderScene();
    void renderModels();
    void renderGrid();

private:
    void createUniforms();
    void setUniforms();
    void createGridUniforms();
  
public:
    Scene m_scene;
    ShaderProgram m_shader;
    ShaderProgram m_lightShader;
    ShaderProgram m_gridShader;
    bool isOrhto = false;
};