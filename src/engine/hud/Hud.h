#pragma once

#include "../../window/Window.h"
#include "../SceneRenderer.h"
#include "../Framebuffer.h"
#include "LightUi.h"
#include "TextureViewer.h"

class Hud {

public:
	Hud(SceneRenderer& sceneRenderer);
	void init(Window& window);
	void renderHud(Framebuffer& frameBuffer);
	void terminate();

private:
	void renderDisplayWindow(Framebuffer& frameBuffer);
	void renderCameraUi();
	void renderOptionsUi();

private:
	SceneRenderer& m_sceneRenderer;
	LightUi m_lightUi;
	TextureViewer m_textureViewer;
};

