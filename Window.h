#pragma once
#include <GLFW/glfw3.h>

#include "Renderer.h"

class Window {

private:
	const unsigned int width = 800;
	const unsigned int height = 600;

	GLFWwindow* windowHandle = NULL;
	Renderer* renderer;


public:
	void init();
	GLFWwindow* getWindowHandle();

	
private:
	void createWindow();
	void loop();
	void processInput(GLFWwindow* window);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
