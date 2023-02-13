#pragma once
#include "SceneRenderer.h"

class Renderer {
private:
	SceneRenderer* sceneRenderer;

public: 
	Renderer();
	void render();
};