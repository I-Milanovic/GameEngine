#include <glad/glad.h>

#include <iostream>

#include "Window.h"


	/*
	float deltaTime = 0.0f; // time between current frame and last frame
	float lastFrame = 0.0f;
*/


	Window::Window(int width, int height) : m_width(width), m_height(height) {
		// glfw initialization and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//setFullScreen();

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

	//	glfwSetInputMode(m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
				i->mouseInput(xpos, ypos);
			}
			else
				i->setFirstMouseTrue();
		});

		//glfwSetWindowSizeCallback(m_windowHandle, [](GLFWwindow* window, int width, int height) {

		//});

		glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow* window) {
			std::cout << "Window is closing!" << std::endl;
		});

	}

	void Window::setFullScreen() {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		m_width = mode->width;
		m_height = mode->height;

		std::cout << m_width << std::endl;
		std::cout << m_height << std::endl;
	}
