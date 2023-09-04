#pragma once

#include <GLFW/glfw3.h>

#include "../engine/SceneRenderer.h"
#include "Input.h"

class Window {

	public:
		Window();
	//	Window(SceneRenderer* scene);
		inline const int getWindowWidth() { return m_width; };
		inline const int getWindowHeight() { return m_height; };
		inline GLFWwindow* getWindowHandle() { return m_windowHandle; };
	
		void init(SceneRenderer& scene, Input& input);
		float lastX = 400.0f;

	private:
		const unsigned int m_width = 800;
		const unsigned int m_height = 600;

		GLFWwindow* m_windowHandle;// duno if i need this if its default null = NULL;
};
