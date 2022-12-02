#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* windowHandle, int width, int height);


class Window {

private: const unsigned int width = 800, height = 600;

private: GLFWwindow* windowHandle;



public :
	Window() {
		std::cout << "Window object created" << std::endl;
	}

	~Window() {
		std::cout << "Destrutor called for Window object" << std::endl;
	}

public: void init() {
	// glfw initialization and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	createWindow();

	glfwMakeContextCurrent(windowHandle);
	glfwSetFramebufferSizeCallback(windowHandle, framebuffer_size_callback);



	//glad load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to intiliaze GLAD" << std::endl;
	}

	loop();

	glfwTerminate();

}

private: void createWindow() {
	// glfw window creation
	windowHandle = glfwCreateWindow(width, height, "Demo", NULL, NULL);
	if (windowHandle == NULL) {
		std::cout << "Failed to create GLFWE window" << std::endl;
		glfwTerminate();
	}
}
public: 
	GLFWwindow* getWindowHandle() {
		return windowHandle;
	}

	// render loop
	void loop() {
		while (!glfwWindowShouldClose(windowHandle)) {
			// input
			processInput(windowHandle);

			//glfw: swap buffers and poll IO events
			glfwSwapBuffers(windowHandle);
			glfwPollEvents();
		}
	}

	void processInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

};


	void :: framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
