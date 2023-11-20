#include <iostream>
#include "Application.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


Application* Application::s_instance = nullptr;



Application::Application() :
	m_window(new Window(1200, 800)), m_renderer(new Renderer()), 
	m_input(new Input(m_renderer->getSceneRenderer())), m_hud(Hud(*m_renderer)) {

	s_instance = this;

	SceneRenderer& scene = m_renderer->getSceneRenderer();
	//scene.getScene().getProjection().setRatio(m_window->getWindowWidth(), m_window->getWindowHeight());
	m_window->init(scene, *m_input);


	m_hud.init(*m_window);
	glEnable(GL_DEPTH_TEST);
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
        
		m_input->keyboardInput(windowHandle, m_deltaTime);


		m_renderer->render();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw sceneRenderer
		m_hud.renderHud(*m_renderer->getSceneRenderer().getFrameBuffer());
	
		// rendering commands here


		//glfw: swap buffers and poll IO events
		glfwSwapBuffers(windowHandle);
		glfwPollEvents();
	}
}
