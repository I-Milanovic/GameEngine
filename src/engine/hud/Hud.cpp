#include "Hud.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


#include "../../engine/Texture.h"

#include <iostream>

Hud::Hud(Renderer& renderer) : m_renderer(renderer), m_lightUi(renderer.getSceneRenderer().getScene().getSceneLights()){
}

void Hud::init(Window& window) {

	static bool show_demo_window = true;
	static bool show_another_window = false;
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
 //   io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }	 
	 
	ImGui_ImplGlfw_InitForOpenGL(window.getWindowHandle(), true);
	ImGui_ImplOpenGL3_Init();
}

void Hud::renderHud(Framebuffer& frameBuffer) {
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    // main view
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("OpenGL Texture Text");
    ImVec2 contentSize = ImGui::GetContentRegionAvail();
    m_renderer.getSceneRenderer().getScene().getProjection().setRatio(static_cast<int> (contentSize.x), static_cast<int> (contentSize.y));
    ImGui::Image((void*)(intptr_t)frameBuffer.getColorTex(), contentSize, ImVec2 { 0, 1 }, ImVec2{ 1,0 });
    ImGui::PopStyleVar();
    ImGui::End();


    m_lightUi.RenderLightUi();
    {
        ImGui::Begin("Camera");
        ImGui::SeparatorText("Position");
        ImGui::Text("Warning in local space for now");

        glm::vec3& pos = m_renderer.getSceneRenderer().getScene().getCamera()->getCameraPos();
        float cameraSliderFactW = 0.0f;
        float cameraSliderSpd = 0.05f;

        ImGui::DragFloat("##XcameraPos", &pos.x, cameraSliderSpd, 0.0f, 0.0f, "X: %.3f");
        ImGui::DragFloat("##YcameraPos", &pos.y, cameraSliderSpd, 0.0f, 0.0f, "Y: %.3f");
        ImGui::DragFloat("##ZcameraPos", &pos.z, cameraSliderSpd, 0.0f, 0.0f, "Z: %.3f");
        ImGui::DragFloat("##WcameraPos", &cameraSliderFactW, cameraSliderSpd, 0.0f, 0.0f, "W: %.3f");


        ImGui::End();
    }


 //   ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

//ShowExampleAppDockSpace
void Hud::terminate() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}