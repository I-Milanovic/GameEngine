#include <iostream>
#include <glad/glad.h>
#include "Window.h"
 


	void Window::init() {
	// glfw initialization and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	createWindow();

	glfwMakeContextCurrent(windowHandle);
	glfwSetFramebufferSizeCallback(windowHandle, &Window::framebuffer_size_callback);

	//glad load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to intiliaze GLAD" << std::endl;
	}
	renderer = new Renderer();
	
	glEnable(GL_DEPTH_TEST);

	loop();

	glfwTerminate();
}

	void Window::createWindow() {
	// glfw window creation
	windowHandle = glfwCreateWindow(width, height, "Demo", NULL, NULL);
	if (windowHandle == NULL) {
		std::cout << "Failed to create GLFWE window" << std::endl;
		glfwTerminate();
	}
}

	GLFWwindow* Window::getWindowHandle() {
		return windowHandle;
	}

	// render loop
	void Window::loop() {
		while (!glfwWindowShouldClose(windowHandle)) {

			// input
			processInput(windowHandle);

			// rendering commands here
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// draw triangle
			renderer->render();

			//glfw: swap buffers and poll IO events
			glfwSwapBuffers(windowHandle);
			glfwPollEvents();
		}
	}

	void Window::processInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}