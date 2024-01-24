#include "Hud.h"
#include "../../engine/Texture.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


Hud::Hud(Renderer& renderer) : m_renderer(renderer),
    m_lightUi(renderer.getSceneRenderer().m_scene.getSceneLights()),
    m_textureViewer(TextureViewer(renderer.getSceneRenderer().m_scene)),
    m_sceneViewport(SceneViewport())
{}

void Hud::init(GLFWwindow* windowHandle) {

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
	 
	ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
	ImGui_ImplOpenGL3_Init();
}

void Hud::renderHud(Framebuffer& frameBuffer) {
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    m_sceneViewport.render(m_renderer);
    m_lightUi.RenderLightUi();
    renderCameraUi();
    renderOptionsUi();
    ImGui::ShowDemoWindow();
    m_textureViewer.RenderTextureViewer();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    //{
    //    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    //    ImGui::UpdatePlatformWindows();
    //    ImGui::RenderPlatformWindowsDefault();
    //    glfwMakeContextCurrent(backup_current_context);
    //}
}

void Hud::terminate() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Hud::renderCameraUi() {
 /*   ImGui::Begin("Camera");
    ImGui::SeparatorText("Position");
    ImGui::Text("Warning in local space for now");

    glm::vec3& pos = m_renderer.getSceneRenderer().m_scene.getCamera().getCameraPos();
    float cameraSliderFactW = 0.0f;
    float cameraSliderSpd = 0.05f;

    ImGui::DragFloat("##XcameraPos", &pos.x, cameraSliderSpd, 0.0f, 0.0f, "X: %.3f");
    ImGui::DragFloat("##YcameraPos", &pos.y, cameraSliderSpd, 0.0f, 0.0f, "Y: %.3f");
    ImGui::DragFloat("##ZcameraPos", &pos.z, cameraSliderSpd, 0.0f, 0.0f, "Z: %.3f");
    ImGui::DragFloat("##WcameraPos", &cameraSliderFactW, cameraSliderSpd, 0.0f, 0.0f, "W: %.3f");


    glm::vec3& front = m_renderer.getSceneRenderer().m_scene.getCamera().getFront();
    glm::vec3& right = m_renderer.getSceneRenderer().m_scene.getCamera().getRight();
    glm::vec3& up = m_renderer.getSceneRenderer().m_scene.getCamera().getUp();

    ImGui::SeparatorText("Rotation Euler");
    ImGui::PushItemWidth(100);

    ImGui::Text("RIGHT");
    ImGui::SameLine();
    ImGui::DragFloat("##RXcameraRotE", &right.x, cameraSliderSpd, 0.0f, 0.0f, "X: %.3f");
    ImGui::SameLine();
    ImGui::DragFloat("##RYcameraRotE", &right.y, cameraSliderSpd, 0.0f, 0.0f, "Y: %.3f");
    ImGui::SameLine();
    ImGui::DragFloat("##RZcameraRotE", &right.z, cameraSliderSpd, 0.0f, 0.0f, "Z: %.3f");

    ImGui::Text("UP   ");
    ImGui::SameLine();
    ImGui::DragFloat("##UXcameraRotE", &up.x, cameraSliderSpd, 0.0f, 0.0f, "X: %.3f");
    ImGui::SameLine();
    ImGui::DragFloat("##UYcameraRotE", &up.y, cameraSliderSpd, 0.0f, 0.0f, "Y: %.3f");
    ImGui::SameLine();
    ImGui::DragFloat("##UZcameraRotE", &up.z, cameraSliderSpd, 0.0f, 0.0f, "Z: %.3f");

    ImGui::Text("FRONT");
    ImGui::SameLine();
    ImGui::DragFloat("##FXcameraRotE", &front.x, cameraSliderSpd, 0.0f, 0.0f, "X: %.3f"); 
    ImGui::SameLine();
    ImGui::DragFloat("##FYcameraRotE", &front.y, cameraSliderSpd, 0.0f, 0.0f, "Y: %.3f"); 
    ImGui::SameLine();
    ImGui::DragFloat("##FZcameraRotE", &front.z, cameraSliderSpd, 0.0f, 0.0f, "Z: %.3f");


    ImGui::Text("Camera Quat");
    float& pitch = m_renderer.getSceneRenderer().m_scene.m_quatCamera.pitch;
    ImGui::DragFloat("##CamQuatRotX", &pitch, cameraSliderSpd, 0.0f, 0.0f, "X: %.3f");
   
    float& yaw = m_renderer.getSceneRenderer().m_scene.m_quatCamera.yaw;
    ImGui::DragFloat("##CamQuatRotY", &yaw, cameraSliderSpd, 0.0f, 0.0f, "Y: %.3f");

    ImGui::End();*/
}

void Hud::renderOptionsUi() {
    std::string labelOrtho = "Orthographic";
    std::string labelPerspective = "Perspective";
    std::string label;

    bool& isOrtho = m_renderer.getSceneRenderer().isOrhto;
    if (isOrtho)
        label = labelOrtho;
    else
        label = labelPerspective;

    ImGui::Begin("User controls");
    ImGui::Checkbox("Fog", &m_renderer.getSceneRenderer().m_scene.m_fog.isActive);
    ImGui::DragFloat("##Density", &m_renderer.getSceneRenderer().m_scene.m_fog.density, 0.01f, 0.0f, 1.0f, "Dens: %.3f");

    ImGui::Checkbox(label.c_str(), &isOrtho);
    ImGui::DragFloat("##Size", &m_renderer.getSceneRenderer().m_scene.m_projection.getOrthoSize(), 0.025f, 0.1f, 10.0f, "Size: %.3f");

    ImGui::End();
}
