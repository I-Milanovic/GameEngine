#include "Renderer.h"

	Renderer::Renderer() {
		sceneRenderer = new SceneRenderer();
	}

	void Renderer::render() {
		sceneRenderer->renderScene();
	}

	SceneRenderer Renderer::getSceneRenderer() {
		return *sceneRenderer;
	}
