#include "Hud.h"
#include "../../engine/Texture.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

Hud::Hud(SceneRenderer& sceneRenderer) : m_sceneRenderer(sceneRenderer),
m_lightUi(sceneRenderer.getScene().getSceneLights()),
m_textureViewer(TextureViewer(m_sceneRenderer.getScene())){}

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


    //bool what = ImGui::IsWindowHovered();
    //std::cout << what << std::endl;

    renderDisplayWindow(frameBuffer);
    m_lightUi.RenderLightUi();
    renderCameraUi();
    renderOptionsUi();
    ImGui::ShowDemoWindow();

    m_textureViewer.RenderTextureViewer();

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

void Hud::renderDisplayWindow(Framebuffer& frameBuffer) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Renderer display");

//    bool isWindowHovered = ImGui::IsWindowHovered();


    ImVec2 contentSize = ImGui::GetContentRegionAvail();
    m_sceneRenderer.getScene().getProjection().setRatio(static_cast<int> (contentSize.x), static_cast<int> (contentSize.y));
    ImGui::Image((void*)(intptr_t)frameBuffer.getColorTex(), contentSize, ImVec2{ 0, 1 }, ImVec2{ 1,0 });
    ImGui::PopStyleVar();
    ImGui::End();
}

void Hud::renderCameraUi() {
    ImGui::Begin("Camera");
    ImGui::SeparatorText("Position");
    ImGui::Text("Warning in local space for now");

    glm::vec3& pos = m_sceneRenderer.getScene().getCamera().getCameraPos();
    float cameraSliderFactW = 0.0f;
    float cameraSliderSpd = 0.05f;

    ImGui::DragFloat("##XcameraPos", &pos.x, cameraSliderSpd, 0.0f, 0.0f, "X: %.3f");
    ImGui::DragFloat("##YcameraPos", &pos.y, cameraSliderSpd, 0.0f, 0.0f, "Y: %.3f");
    ImGui::DragFloat("##ZcameraPos", &pos.z, cameraSliderSpd, 0.0f, 0.0f, "Z: %.3f");
    ImGui::DragFloat("##WcameraPos", &cameraSliderFactW, cameraSliderSpd, 0.0f, 0.0f, "W: %.3f");
    ImGui::End();
}

void Hud::renderOptionsUi() {
    std::string labelOrtho = "Orthographic";
    std::string labelPerspective = "Perspective";
    std::string label;

    bool& isOrtho = m_sceneRenderer.getIsOrtho();
    if (isOrtho)
        label = labelOrtho;
    else
        label = labelPerspective;

    ImGui::Begin("User controls");
    ImGui::Checkbox("Fog", &m_sceneRenderer.getScene().getFog().isActive);
    ImGui::DragFloat("##Density", &m_sceneRenderer.getScene().getFog().density, 0.01f, 0.0f, 1.0f, "Dens: %.3f");

    ImGui::Checkbox(label.c_str(), &isOrtho);
    ImGui::DragFloat("##Size", &m_sceneRenderer.getScene().getProjection().getOrthoSize(), 0.025f, 0.1f, 10.0f, "Size: %.3f");

    ImGui::End();
}
