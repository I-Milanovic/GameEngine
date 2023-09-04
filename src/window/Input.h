#pragma once

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>


#include "../engine/SceneRenderer.h"

class Input {

	public:
		Input(SceneRenderer& scene);
		void keyboardInput(GLFWwindow* windowHandle, const float& const deltaTime, glm::vec3& cameraPos);
		void mouseInput(double xpos, double ypos);
		void scrollInput(double offsetX, double offsetY);
		void keyInput();

	private:
		bool m_isFirstMouse = true;
		float m_lastX = 800 / 2.0f; //m_window.getWindowHeight() / 2.0f;
		float m_lastY = 600 / 2.0f; //m_window.getWindowWidth() / 2.0f;

	private:
		//GLFWwindow* m_window
	//	Window& m_window;
		SceneRenderer& m_scene;

};
