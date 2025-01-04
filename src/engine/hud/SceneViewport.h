#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "../Renderer.h"

class SceneViewport {

public:
	void render(Renderer& renderer);

public:
	bool m_isHovered = false;
	ImVec2 m_screenPos;		// m_position in a main window
	ImVec2 m_viewPortSize;	// width height
};

