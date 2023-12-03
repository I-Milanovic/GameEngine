#pragma once

#include <string>
#include <GLFW/glfw3.h>

#include "../window/Window.h"
#include "../engine/Renderer.h"
#include "../window/Input.h"

#include "../engine/hud/Hud.h"


class Application {

	public:
		Application();	
		virtual ~Application() = default;	
		void run();

	private:
		Window* m_window;
		Renderer* m_renderer;
		Input* m_input;
		Hud m_hud;

		bool m_isRunnin = true;
		float m_lastFrameTime = 0.0f;

		float m_deltaTime = 0.0f; // time between current frame and last frame
		float m_lastFrame = 0.0f;

};
