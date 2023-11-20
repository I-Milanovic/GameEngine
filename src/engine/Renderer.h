#pragma once
#include "SceneRenderer.h"

class Renderer {
	public: 
		Renderer();
		void render();
		inline SceneRenderer& getSceneRenderer() { return m_sceneRenderer; };
	private:
		SceneRenderer m_sceneRenderer;
};