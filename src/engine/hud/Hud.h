#pragma once

#include "../Renderer.h"
#include "../Framebuffer.h"
#include "LightUi.h"
#include "TextureViewer.h"

#include "SceneViewport.h"

#include "PropertyPanel.h"
#include <GLFW/glfw3.h>


class Hud {

public:
	Hud(Renderer& renderer);
	void init(GLFWwindow* windowHandle);
	void renderHud(Framebuffer& frameBuffer);
	void terminate();

private:
	void renderCameraUi();
	void renderOptionsUi() const;

	void createSceneGraph(Node* node);

	void renderSceneGraph();

	void renderSceneGraphWindow();

public:
	SceneViewport m_sceneViewport;

private:
	Renderer& m_renderer;
	LightUi m_lightUi;
	PropertyPanel m_propertyPanel;

	Model* m_selectedModel;
	Node* m_selectedNode;
};

