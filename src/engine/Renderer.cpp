#include "Renderer.h"
#include "scene/Scene.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

	Renderer::Renderer() :
	m_sceneRenderer(SceneRenderer(Scene(1200, 1000))),
	m_frameBuffer(Framebuffer()) {

		m_frameBuffer.init(1200, 800);
		glEnable(GL_DEPTH_TEST);

	}

	void Renderer::render() {
		m_frameBuffer.bindFrameBuffer();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glEnable(GL_BLEND);
		//glBlendEquation(GL_FUNC_ADD);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_sceneRenderer.renderScene();
		m_frameBuffer.unbindFrameBuffer();
	}

