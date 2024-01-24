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
		Hud m_hud;
		Input* m_input;

		bool m_isRunnin = true;
		float m_lastFrameTime = 0.0f;

		float m_deltaTime = 0.0f; // time between current frame and last frame
		float m_lastFrame = 0.0f;

};
