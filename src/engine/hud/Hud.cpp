#include "Hud.h"
#include "src/engine/scene/Texture.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>




Hud::Hud(Renderer& renderer) : m_sceneViewport(SceneViewport()), 
    m_renderer(renderer),
    m_lightUi(renderer.getSceneRenderer().m_scene.getSceneLights()),
    m_propertyPanel(renderer.getSceneRenderer().m_scene),
    m_selectedModel(nullptr),
    m_selectedNode(nullptr)
   //, m_Transform(NodeTransform())
{}

//static ImFont* font1;
//static ImFont* font2;

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

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }	 
	 
	ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
	ImGui_ImplOpenGL3_Init();
    
    static const ImWchar icons_ranges[] = { 0xe005, 0xf8ff, 0 }; // Will not be copied by AddFont* so keep in scope.
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    // load font
    io.Fonts->AddFontFromFileTTF("resources/font/Roboto/Roboto-Medium.ttf", 16);
    io.Fonts->AddFontFromFileTTF("resources/font/myFont/myFont1.ttf", 16, &icons_config, icons_ranges);
   
    io.Fonts->Build();

}

void Hud::renderHud(Framebuffer& frameBuffer) {
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    m_sceneViewport.render(m_renderer);
   
    renderCameraUi();
    renderSceneGraphWindow();
    m_propertyPanel.display();

    //ImGui::ShowDemoWindow();
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

void Hud::renderSceneGraphWindow() {
    ImGui::Begin("SceneGraph");
    renderSceneGraph();
    ImGui::End();
}

void Hud::renderCameraUi() {
    ImGui::Begin("Properties");

    if (ImGui::CollapsingHeader("\xee\xa4\x82   Camera")) {
        renderOptionsUi();
    }

    if (ImGui::CollapsingHeader("\xee\xa4\x81   Textures")) {

        std::string idxKey;
        ImGui::PushItemWidth(300);
        if (ImGui::BeginListBox("##listbox 1")) {
            TextureCache& tc = m_renderer.getSceneRenderer().m_scene.getTextureCache();
        
            for (const auto& [pathKey, tex] : tc.getTextures()) {
                const bool is_selected = (idxKey == pathKey);
                const std::string name = tex.getTextureData().name;


                if (ImGui::Selectable("##", is_selected)) 
                    idxKey = pathKey;
                ImGui::SameLine();
                ImGui::Image((void*)tex.getTextureId(), ImVec2(20, 20));
                ImGui::SameLine();
                ImGui::Text(name.c_str());
            }
            ImGui::EndListBox();
            ImGui::PopItemWidth();
        }

        ImVec2 buttSize(70.0f, 0.0f);
        ImGui::Button("Add ##Texture", buttSize);
        ImGui::SameLine();
        ImGui::Button("Remove ##Texture", buttSize);    // center text


    }

    if (ImGui::CollapsingHeader("\xee\xa4\x80   Light")) {
        m_lightUi.RenderLightUi();
        
    }

    //if (ImGui::CollapsingHeader("SceneGraph")) {
    //    renderSceneGraph();
    //}
    // ImGui::PushFont(font2);
    //ImGui::SeparatorText("\xee\xa4\x81" "  Textures");
    //ImGui::PopFont();
    //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
    //ImGui::SeparatorText("\xee\xa4\x81");
    //ImGui::Text("\xee\xa4\x80");
    //ImGui::PopStyleColor();

    ImGui::End();
}

void Hud::renderOptionsUi() const{
    std::string labelOrtho = "Orthographic";
    std::string labelPerspective = "Perspective";
    std::string label;

    bool& isOrtho = m_renderer.getSceneRenderer().isOrhto;
    if (isOrtho)
        label = labelOrtho;
    else
        label = labelPerspective;

  //  ImGui::Begin("User controls");
    ImGui::Checkbox("Fog", &m_renderer.getSceneRenderer().m_scene.getFog().isActive);
    ImGui::DragFloat("##Density", &m_renderer.getSceneRenderer().m_scene.getFog().density, 0.01f, 0.0f, 1.0f, "Dens: %.3f");

    ImGui::Checkbox(label.c_str(), &isOrtho);
    ImGui::DragFloat("##Size", &m_renderer.getSceneRenderer().m_scene.getProjection().getOrthoSize(), 0.025f, 0.1f, 10.0f, "Size: %.3f");

  //  ImGui::End();
}

void Hud::createSceneGraph(Node* node) {
    if (!node)
        return;
    int numChildren = node->getChildren().size();
    std::string nodeName = node->getName();

    std::string model = "\xee\xa4\x84 ";
    std::string bone = "\xee\xa4\x86 ";
    std::string mesh = "\xee\xa4\x87 ";
    std::string material = "\xee\xa4\x88 ";

    std::string ico;

    if (node->getDataType() == DataType::material)
        ico = material;
    if (node->getDataType() == DataType::mesh)
        ico = mesh;
    if (node->getDataType() == DataType::bone)
        ico = bone;
    if (node->getDataType() == DataType::model)
        ico = model;

    std::string name = ico.append(node->getName().c_str());
   
    if (numChildren == 0) {
        ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen /*| ImGuiTreeNodeFlags_OpenOnArrow*/);
        // Check if leaf node is clicked
        if (ImGui::IsItemClicked())
            if (node->getDataType() == DataType::material)
                node->printDataType();

    }
    else {
        if (ImGui::TreeNodeEx(name.c_str(), /*ImGuiTreeNodeFlags_DefaultOpen |*/ ImGuiTreeNodeFlags_OpenOnDoubleClick)) {
            // Check if parent node is clicked
            if (ImGui::IsItemClicked())
                if (node->getDataType() == DataType::mesh) {
                    m_selectedModel = static_cast<Model*>(node->getData());
                    m_selectedNode = node;
                }
            
            for (Node* child : node->getChildren())
                createSceneGraph(child);
            ImGui::TreePop();
        }
    }
}

void Hud::renderSceneGraph() {

    ModelCache& mc = m_renderer.getSceneRenderer().m_scene.getModelCache();

    Node* rootNode = m_renderer.getSceneRenderer().m_scene.getSceneGraph().getRootNode();
   // ImGui::BeginChild("child_2", { 0, 300}, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
    //ImGui::EndChild();

    //HelpMarker("Drag bottom border to resize. Double-click bottom border to auto-fit to vertical contents.");
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
    if (ImGui::BeginChild("ResizableChild", ImVec2(-FLT_MIN, ImGui::GetTextLineHeightWithSpacing() * 8), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY))
        createSceneGraph(rootNode);
    ImGui::PopStyleColor();
    ImGui::EndChild();

    bool disabled = false;
    if (m_selectedModel == nullptr)
        disabled = true;
    else
        disabled = false;

    ImGui::BeginDisabled(disabled);
    glm::vec3* pos = &m_selectedModel->getEntity().getPosition();
    glm::vec3 posZero(0.0f);
    if (disabled) {
        pos = &posZero;
    }

    float sliderStep = 0.005f;
    ImGui::SeparatorText("Model Position");
    ImGui::PushItemWidth(60);
    if (ImGui::DragFloat("##XmodelPos", &pos->x, sliderStep, 0.0f, 0.0f, "X: %.3f"))
        m_renderer.getSceneRenderer().m_scene.getSceneGraph().applyTransformation(m_selectedNode);
    ImGui::SameLine();
    if(ImGui::DragFloat("##YmodelPos", &pos->y, sliderStep, 0.0f, 0.0f, "Y: %.3f"))
        m_renderer.getSceneRenderer().m_scene.getSceneGraph().applyTransformation(m_selectedNode);
    ImGui::SameLine();
    if(ImGui::DragFloat("##ZmodelPos", &pos->z, sliderStep, 0.0f, 0.0f, "Z: %.3f"))
        m_renderer.getSceneRenderer().m_scene.getSceneGraph().applyTransformation(m_selectedNode);
    ImGui::PopItemWidth();


    glm::vec3* rot = &m_selectedModel->getEntity().getRotation();
    glm::vec3 rotZero(0.0f);

    if (disabled)
        rot = &rotZero;


    float k = 0.0f;
    float* x = &k;
    float* y = &k;
    float* z = &k;

    if (m_selectedModel) {
        x = &m_selectedModel->getEntity().getXrot();
        y = &m_selectedModel->getEntity().getYrot();
        z = &m_selectedModel->getEntity().getZrot();
    }

    sliderStep = 0.5f;
    ImGui::SeparatorText("Model Rotation");
    ImGui::PushItemWidth(60);
    if (ImGui::DragFloat("##XmodelRot", x, sliderStep, 0.0f, 0.0f, "X: %.3f")) {
        //m_selectedModel->getEntity().rotatePitch(glm::radians(x));
        
        m_selectedModel->getEntity().rotatePitch();
        m_renderer.getSceneRenderer().m_scene.getSceneGraph().applyTransformation(m_selectedNode);
    }
    ImGui::SameLine();
    if (ImGui::DragFloat("##YmodelRot", y, sliderStep, 0.0f, 0.0f, "Y: %.3f")) {
        //m_selectedModel->getEntity().rotateYaw(glm::radians(y));
       m_selectedModel->getEntity().rotateYaw();
       m_renderer.getSceneRenderer().m_scene.getSceneGraph().applyTransformation(m_selectedNode);
    }
    ImGui::SameLine();
    if (ImGui::DragFloat("##ZmodelRot", z, sliderStep, 0.0f, 0.0f, "Z: %.3f")) {
        //m_selectedModel->getEntity().rotateRoll(glm::radians(z));
       m_selectedModel->getEntity().rotateRoll();
       m_renderer.getSceneRenderer().m_scene.getSceneGraph().applyTransformation(m_selectedNode);
    }
    ImGui::PopItemWidth();

    float scaleZero = 0.0f;
   
    float* scale = &m_selectedModel->getEntity().getScale();
    if (disabled)
        scale = &scaleZero;
    sliderStep = 0.005f;
    ImGui::SeparatorText("Model Scaling");
    ImGui::PushItemWidth(100);
    if(ImGui::DragFloat("##modelScale", scale, sliderStep, 0.0f, 0.0f, "S: %.3f"))
        m_renderer.getSceneRenderer().m_scene.getSceneGraph().applyTransformation(m_selectedNode);
    ImGui::PopItemWidth();
    ImGui::EndDisabled();
}
