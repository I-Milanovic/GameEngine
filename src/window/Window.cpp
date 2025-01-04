#include <glad/glad.h>

#include <iostream>

#include "Window.h"


	/*
	float deltaTime = 0.0f; // time between current frame and last frame
	float lastFrame = 0.0f;
*/

	static float x = 0.0f;

	Window::Window(std::string title, int width, int height) : m_title(title), m_width(width), m_height(height) {
		// glfw initialization and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		//setFullScreen();


		m_windowHandle = glfwCreateWindow(m_width, m_height, &m_title[0], NULL, NULL);
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

		glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow* window) {
			std::cout << "Window is closing!" << std::endl;
			});

		glfwSetScrollCallback(m_windowHandle, [](GLFWwindow* window, double offsetX, double offsetY) {
			Input* i = ((Input*)glfwGetWindowUserPointer(window));
			i->scrollInput(offsetX, offsetY);
		});

		glfwSetKeyCallback(m_windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
		});

		 //original
		glfwSetCursorPosCallback(m_windowHandle, [](GLFWwindow* window, double xpos, double ypos) {
			Input* i = ((Input*)glfwGetWindowUserPointer(window));

			bool isMiddleMouseButtonDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
			bool isShiftDown = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

			if (isMiddleMouseButtonDown && isShiftDown) {
				i->keyboardInput(window, 0.0f, xpos, ypos);
			}
			else {
				//i->call();
				if (isMiddleMouseButtonDown) {
					i->mouseInputOld(xpos, ypos);
				}
				else {
					i->setFirstMouseTrue();
					//	i->arcReplace();
				}
			}


		});

		// arcBall
		//glfwSetMouseButtonCallback(m_windowHandle, [](GLFWwindow* window, int button, int action, int mods) {
		//	Input* i = ((Input*)glfwGetWindowUserPointer(window));
		//		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		//			double startXPos, startYPos; // screen coordinates when mouse clicks
		//			glfwGetCursorPos(window, &startXPos, &startYPos);
		//			i->dragAction(startXPos, startYPos);
		//		}
		//		else if (action == GLFW_RELEASE) {
		//			i->arcReplace();
		//		}
		//});
		
		//glfwSetCursorPosCallback(m_windowHandle, [](GLFWwindow* window, double xpos, double ypos) {
		//	Input* i = ((Input*)glfwGetWindowUserPointer(window));
		//	i->moveAction(xpos, ypos);
		//});


	}

	void Window::setFullScreen() {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		m_width = mode->width;
		m_height = mode->height;

		std::cout << m_width << std::endl;
		std::cout << m_height << std::endl;
	}


