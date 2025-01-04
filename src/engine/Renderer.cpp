#include "Renderer.h"
#include "scene/Scene.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

Renderer::Renderer() :
m_sceneRenderer(SceneRenderer()),
m_frameBuffer(Framebuffer()) {
	m_frameBuffer.init(1200, 800);
	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer() {
	std::cout << "Deleting Renderer" << std::endl;
}

void Renderer::render() {
	m_frameBuffer.bindFrameBuffer();
	glClear(GL_COLOR_BUFFER_BIT);
	
	m_sceneRenderer.renderGrid();
	glClear(GL_DEPTH_BUFFER_BIT);
	m_sceneRenderer.renderScene();
	m_sceneRenderer.renderModels();

	Model* model = m_sceneRenderer.m_scene.getModelCache().getModel("CharacterMesh-Anim");
	if(model &&  model->getAnimationManager().hasCurrentAnimation())
		model->getAnimationManager().nextFrame();

	m_frameBuffer.unbindFrameBuffer();
}

