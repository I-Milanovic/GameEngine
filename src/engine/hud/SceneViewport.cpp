#include "SceneViewport.h"

void SceneViewport::render(Renderer& renderer) {

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Renderer display");

    m_isHovered = ImGui::IsWindowHovered();
    m_screenPos = ImGui::GetCursorScreenPos();
    m_viewPortSize = ImGui::GetContentRegionAvail();

    renderer.getSceneRenderer().m_scene.m_projection.setRatio(static_cast<int> (m_viewPortSize.x), static_cast<int> (m_viewPortSize.y));
    unsigned int textureId = renderer.getFrameBuffer().getColorTex();
    ImGui::Image((void*)(intptr_t)textureId, m_viewPortSize, ImVec2{ 0, 1 }, ImVec2{ 1,0 });

    ImGui::PopStyleVar();
    ImGui::End();
}