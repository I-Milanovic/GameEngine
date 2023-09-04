#include <iostream>

#include "Application.h"



Application* Application::s_instance = nullptr;

Application::Application(const std::string& name, int width, int height) {

	s_instance = this;

	//m_window = new Window((m_renderer->getSceneRenderer()));
	m_window = new Window();
	m_renderer = new Renderer();
	SceneRenderer* scene = m_renderer->getSceneRenderer();
	m_input = new Input(*scene);
	m_window->init(*scene, *m_input);

	glEnable(GL_DEPTH_TEST);
	run();

	glfwTerminate();
}

void Application::run() {
	GLFWwindow* windowHandle = m_window->getWindowHandle();
	SceneRenderer* scene = m_renderer->getSceneRenderer();
	//Input input(*scene);
	while (!glfwWindowShouldClose(windowHandle)) {

		float currentFrame = static_cast<float>(glfwGetTime());
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;
		
		glm::vec3 pos = scene->getCamera().getPos();
		m_input->keyboardInput(windowHandle, m_deltaTime, pos /*, scene->getCamera().getUp(), scene->getCamera().getFront() */);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw triangle
		m_renderer->render();

		//glfw: swap buffers and poll IO events
		glfwSwapBuffers(windowHandle);
		glfwPollEvents();
	}
}