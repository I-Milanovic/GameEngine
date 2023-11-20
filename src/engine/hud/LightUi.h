#pragma once


#include "../scene/lights/SceneLights.h"


#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class LightUi {


public:
	LightUi(SceneLights& sceneLights);
	void RenderLightUi();
private:
	void RenderAmbientLightUi();
	void RenderDirectionalLightUi();
	void RenderPointLightUi();
	void RenderSpotLightUi();


private:
	SceneLights& m_sceneLights;
	ImGuiColorEditFlags m_misc_flags = NULL;

};

