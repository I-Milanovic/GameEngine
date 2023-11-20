#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "shader/ShaderProgram.h"
#include "shader/UniformMap.h"

#include "../engine/ModelLoader.h"
#include "../engine/Framebuffer.h"

#include "scene/Scene.h"


class SceneRenderer {

    public:
        SceneRenderer(Scene scene);
        void renderScene();
        inline Scene& getScene() { return m_scene; };
        inline Framebuffer* getFrameBuffer() { return &m_frameBuffer; };
    private:
        void createUniforms();
        void createLightUniforms();
    private:  
        Scene m_scene;
        Framebuffer m_frameBuffer;

	    ShaderProgram* m_shader;
	    ShaderProgram* m_lightShader;
        
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