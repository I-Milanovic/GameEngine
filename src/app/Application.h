#pragma once

#include <string>

#include "../window/Window.h"
#include "../engine/Renderer.h"
#include "../engine/hud/Hud.h"
#include "../window/Input.h"

#include <GLFW/glfw3.h>


class Application {

	public:
		Application();	
		virtual ~Application() = default;	
		void run();

		float m_fps = 0.0f;

	private:
		Window* m_window;
		Renderer* m_renderer;
		Hud m_hud;
		Input* m_input;

		bool m_isRunnin = true;
		float m_lastFrameTime = 0.0f;

		float m_deltaTime = 0.0f; // time between current frame and last frame
		float m_lastFrame = 0.0f;

		float lastFrameTimeFps = 0.0f;
		float nextFps = 0.0f;
		
};
