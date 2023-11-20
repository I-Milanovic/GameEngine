#pragma once

#include <GLFW/glfw3.h>

#include "../engine/SceneRenderer.h"
#include "Input.h"

class Window {


	public:
		Window(int width = 800, int height = 600);
	//	Window(SceneRenderer* scene);
		inline const int getWindowWidth() { return m_width; };
		inline const int getWindowHeight() { return m_height; };
		inline GLFWwindow* getWindowHandle() { return m_windowHandle; };
	
		void init(SceneRenderer& scene, Input& input);
		float lastX = 400.0f;


		void setFullScreen();

	private:
		unsigned int m_width;
		unsigned int m_height;
		GLFWwindow* m_windowHandle;// duno if i need this if its default null = NULL;
};


