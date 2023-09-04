#include <glad/glad.h>

#include <iostream>

#include "Window.h"


	/*
	float deltaTime = 0.0f; // time between current frame and last frame
	float lastFrame = 0.0f;
*/


	Window::Window() {
		// glfw initialization and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_windowHandle = glfwCreateWindow(m_width, m_height, "Demo", NULL, NULL);
		if (m_windowHandle == NULL) {
			std::cout << "Failed to create GLFWE window" << std::endl;
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_windowHandle);

		//glad load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to intiliaze GLAD" << std::endl;
		}

		glfwSetInputMode(m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::init(SceneRenderer& scene, Input& input) {
		glfwSetWindowUserPointer(m_windowHandle, &input);

		glfwSetScrollCallback(m_windowHandle, [](GLFWwindow* window, double offsetX, double offsetY) {
			Input* i = ((Input*)glfwGetWindowUserPointer(window));
			i->scrollInput(offsetX, offsetY);
		});

		glfwSetKeyCallback(m_windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
		});

		glfwSetCursorPosCallback(m_windowHandle, [](GLFWwindow* window, double xpos, double ypos) {
			Input* i = ((Input*)glfwGetWindowUserPointer(window));
			i->mouseInput(xpos, ypos);
		});
	
		glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow* window) {
			std::cout << "Window is closing!" << std::endl;
		});

	}