#pragma once
#include "SceneRenderer.h"
#include "../engine/Framebuffer.h"

class Renderer {
	public: 
		Renderer();
		~Renderer();
		void render();
		inline SceneRenderer& getSceneRenderer() { return m_sceneRenderer; };
		inline Framebuffer& getFrameBuffer() { return m_frameBuffer; };
	private:
		SceneRenderer m_sceneRenderer;
		Framebuffer m_frameBuffer;
		
};