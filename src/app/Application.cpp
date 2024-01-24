#include <iostream>
#include "Application.h"

Application::Application() :
	m_window(new Window(1200, 800)), m_renderer(new Renderer()),
	m_hud(Hud(*m_renderer)),
	m_input(new Input(m_renderer->getSceneRenderer(), m_hud)){



	SceneRenderer& scene = m_renderer->getSceneRenderer();
	m_window->init(scene, *m_input);


	m_hud.init(m_window->getWindowHandle()/**m_window*/);
	run();

	m_hud.terminate();
	glfwTerminate();
}

void Application::run() {
	GLFWwindow* windowHandle = m_window->getWindowHandle();
	SceneRenderer sceneRenderer = m_renderer->getSceneRenderer();

	while (!glfwWindowShouldClose(windowHandle)) {
		float currentFrame = static_cast<float>(glfwGetTime());
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;
        
		//m_input->keyboardInput(windowHandle, m_deltaTime);
		m_renderer->render();
		m_input->m_deltaTime = m_deltaTime;
		m_hud.renderHud(m_renderer->getFrameBuffer());


		//glfw: swap buffers and poll IO events
		glfwSwapBuffers(windowHandle);
		glfwPollEvents();
	}
}
