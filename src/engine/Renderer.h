#pragma once
#include "SceneRenderer.h"

class Renderer {
	public: 
		Renderer();
		void render();
		inline SceneRenderer* getSceneRenderer() { return sceneRenderer; };
	private:
		SceneRenderer* sceneRenderer;
};