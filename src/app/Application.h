#pragma once
#include <string>
#include <GLFW/glfw3.h>

#include "../engine/Renderer.h"
#include "../window/Window.h"
#include "../window/Input.h"

class Application {

	public:
		Application(const std::string& name = "GameEngine", int width = 800, int height = 600);
		
		virtual ~Application() = default;
	
		void run();

		inline static Application& getApplication() { return *s_instance; };

	private:
		Window* m_window;
		Renderer* m_renderer;
		Input* m_input;

		bool m_isRunnin = true;
		float m_lastFrameTime = 0.0f;

		float m_deltaTime = 0.0f; // time between current frame and last frame
		float m_lastFrame = 0.0f;


	private:
		static Application* s_instance;

};
