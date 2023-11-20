#pragma once


#include "../../window/Window.h"
#include "../Framebuffer.h"

#include "../Renderer.h"
#include "LightUi.h"

class Hud {

public:
	Hud(Renderer& renderer);
	void init(Window& window);
	void renderHud(Framebuffer& frameBuffer);
	void terminate();
private:
	Framebuffer m_frameBuffer;
	Renderer& m_renderer;
	LightUi m_lightUi;
};

