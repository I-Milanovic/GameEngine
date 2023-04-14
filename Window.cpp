#include <iostream>
#include <glad/glad.h>

#include "Window.h"

	SceneRenderer* scene;

	float deltaTime = 0.0f; // time between current frame and last frame
	float lastFrame = 0.0f;

	bool firstMouse = true;
	float lastX = 800 / 2.0f;
	float lastY = 600 / 2.0f;


	void Window::init() {
		// glfw initialization and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		createWindow();

		glfwMakeContextCurrent(windowHandle);
		glfwSetFramebufferSizeCallback(windowHandle, &Window::framebuffer_size_callback);
		glfwSetCursorPosCallback(windowHandle, &Window::mouseCallback);
		glfwSetScrollCallback(windowHandle, &Window::scrollCallback);

		glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		//glad load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to intiliaze GLAD" << std::endl;
		}
		renderer = new Renderer();

		scene = renderer->sceneRenderer;
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

			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// input
		//	input->move(deltaTime, scene->camera->, scene->cameraUp, scene->cameraFront);
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

	void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void Window::processInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			scene->camera->processKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			scene->camera->processKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			scene->camera->processKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			scene->camera->processKeyboard(RIGHT, deltaTime);
	}

	void Window::mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);


		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float offsetX = xpos - lastX;
		float offsetY = lastY - ypos; // reversed since y-coordinate go from bottom to top

		lastX = xpos;
		lastY = ypos;


		scene->camera->processMouseMovement(offsetX, offsetY);
	}

	void Window::scrollCallback(GLFWwindow* window, double offsetX, double offsetY) {
		scene->camera->processMouseScroll(static_cast<float>(offsetY));
	}