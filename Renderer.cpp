#include "Renderer.h"


	Renderer::Renderer() {
		sceneRenderer = new SceneRenderer();
	}

	void Renderer::render() {
		sceneRenderer->renderScene();
	}
