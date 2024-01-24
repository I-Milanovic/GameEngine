#pragma once
#include <GLFW/glfw3.h>

#include "../Renderer.h"
#include "../Framebuffer.h"
#include "LightUi.h"
#include "TextureViewer.h"

#include "SceneViewport.h"

class Hud {

public:
	Hud(Renderer& renderer);
	void init(GLFWwindow* windowHandle);
	void renderHud(Framebuffer& frameBuffer);
	void terminate();

private:
	void renderCameraUi();
	void renderOptionsUi();

public:
	SceneViewport m_sceneViewport;

private:
	Renderer& m_renderer;
	LightUi m_lightUi;
	TextureViewer m_textureViewer;
};

