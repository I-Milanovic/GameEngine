#include "Renderer.h"
#include "scene/Scene.h"

	Renderer::Renderer() :
		m_sceneRenderer(SceneRenderer(Scene(1200, 1000))) {
	}

	void Renderer::render() {
		m_sceneRenderer.renderScene();
	}
