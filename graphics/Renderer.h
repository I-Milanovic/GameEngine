#pragma once
#include "SceneRenderer.h"

class Renderer {
public:
	SceneRenderer* sceneRenderer;

public: 
	Renderer();
	void render();
	SceneRenderer getSceneRenderer();
};