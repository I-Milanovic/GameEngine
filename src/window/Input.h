#pragma once

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>


#include "../engine/SceneRenderer.h"

class Input {

	public:
		Input(SceneRenderer& scene);
		void keyboardInput(GLFWwindow* windowHandle, const float& const deltaTime);
		void mouseInput(double xpos, double ypos);
		void scrollInput(double offsetX, double offsetY);
		void keyInput();

		inline void setFirstMouseTrue() { m_isFirstMouse = true; };

	private:
		bool m_isFirstMouse = true;
		float m_lastX = 0.0f;//800 / 2.0f; //m_window.getWindowHeight() / 2.0f;
		float m_lastY = 0.0f;//600 / 2.0f; //m_window.getWindowWidth() / 2.0f;

	private:
		//GLFWwindow* m_window
	//	Window& m_window;
		SceneRenderer& m_sceneRenderer;

};
