#pragma once

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>


#include "../engine/SceneRenderer.h"

#include "../engine/hud/Hud.h"

class Input {

	public:
		Input(SceneRenderer& sceneRenderer, Hud& hud);
		void keyboardInput(GLFWwindow* windowHandle, const float& const deltaTime, double xpos, double ypos);
		void mouseInputOld(double xpos, double ypos);
		void mouseInput(double xpos, double ypos);
		void scrollInput(double offsetX, double offsetY);
		void keyInput();

		inline void setFirstMouseTrue() { m_isFirstMouse = true; };

		void dragAction(double startXPos, double startYPos);
		void moveAction(double xpos, double ypos);
		void arcReplace();

		void deltaMove(double xpos, double ypos);
	private:
		void calcNDC(double xpos, double ypos, glm::vec3& vec);

	private:
		bool m_isFirstMouse = true;
		float m_lastX = 0.0f;//800 / 2.0f; //m_window.getWindowHeight() / 2.0f;
		float m_lastY = 0.0f;//600 / 2.0f; //m_window.getWindowWidth() / 2.0f;



	private:
		SceneRenderer& m_sceneRenderer;
		Hud& m_hud;
		//float& m_windowWidth;
		//float& m_windowHeight;
		//bool& m_isHovered;

	public:
		float m_deltaTime;

};
