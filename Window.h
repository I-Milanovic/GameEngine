#pragma once
#include <GLFW/glfw3.h>

#include "graphics/Renderer.h"

class Window {

private:
	const unsigned int width = 800;
	const unsigned int height = 600;

	GLFWwindow* windowHandle = NULL;
	Renderer* renderer;


public:
	void init();
	GLFWwindow* getWindowHandle();
	void processInput(GLFWwindow* window);

	
private:
	void createWindow();
	void loop();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
	static void scrollCallback(GLFWwindow* window, double offsetX, double offsetY);
	
};
