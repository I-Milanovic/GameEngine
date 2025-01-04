#include "FileExplorerDisplay.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


#include <imgui/imgui_stdlib.h>
#include "../FileModel.h"


#include "../ModelLoader.h"

FileExplorerDisplay::FileExplorerDisplay(Scene& scene) :
	m_scene(scene), 
	m_DirImage(TextureData("./resources/images/icons/icons8-folder-80.png", "")), // implicit texture initialization
	m_fileImage(TextureData("./resources/images/icons/icons8-image-64.png", "")) {

	load3DModel("resources/models/cube.obj");
}

void FileExplorerDisplay::displayAsPopupModal() {
	ImGui::SetNextWindowSize(ImVec2(700.0f, 400.0f));
	if(ImGui::BeginPopupModal("FileExplorerPopUp", NULL/*, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize*/)) {
		if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		display();
		ImGui::EndPopup();
	}
}

void FileExplorerDisplay::displayAsWindow() {
	ImGui::Begin("Files");

	display();
	ImGui::End();

}

void FileExplorerDisplay::displayAsPopup() {
	ImGui::SetNextWindowSize(ImVec2(700.0f, 400.0f));
	if (ImGui::BeginPopup("FileExplorerPopUp2")) {
		if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		display();
		ImGui::EndPopup();
	}
}



void FileExplorerDisplay::display() {
	ImVec2 butSize = ImVec2(20.0f, 20.0f);
	ImGui::BeginDisabled(m_fileModel.getPreviousPath().size() == 0);
	if (ImGui::Button("B", butSize))
		m_fileModel.loadDir(m_fileModel.getPreviousPath());
	ImGui::EndDisabled();
	ImGui::SameLine();
	if (ImGui::Button("U", butSize))
		m_fileModel.loadParentDir();
	ImGui::SameLine();

	std::string path = m_fileModel.getPath();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	if (ImGui::InputText("##L", &path, ImGuiInputTextFlags_EnterReturnsTrue))
		m_fileModel.loadDir(path);

	std::string* s = &m_fileModel.getPath();
	ImGui::Text("Data: %p\nSize: %d\nCapacity: %d", *s, s->size(), s->capacity());

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.94f));
	//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 0.94f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.26f, 0.59f, 0.98f, 0.4f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));

	createDirectory();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor(2);
}

void FileExplorerDisplay::createDirectory(){

	ImVec2 button_sz(50, 50);
	ImVec2 uv0 = ImVec2(1.0f, 0.0f);							// UV coordinates for (32,32) in our texture
	ImVec2 uv1 = ImVec2(0.0f, 1.0f);                            // UV coordinates for lower-left
	ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);             // Black background
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);


	ImGuiStyle& style = ImGui::GetStyle();
	float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
	std::vector<std::pair<bool, std::string>> list = m_fileModel.getDirectoryList();

	int size = m_fileModel.getDirectoryList().size();
	int buttons_count = size;

	for (int i = 0; i < size; i++) {
		std::pair<bool, std::string> pair = list.at(i);

		ImGui::PushID(i);

		std::string labelFileName = pair.second;
		ImGui::BeginGroup();
		if (pair.first) {
			if (ImGui::ImageButton(labelFileName.c_str(), (void*)(intptr_t)m_DirImage.getTextureId(), button_sz, uv0, uv1, bg_col, tint_col)) {
				m_fileModel.loadChildDir(labelFileName);
			}
		}
		else {
			if (ImGui::ImageButton(labelFileName.c_str(), (void*)(intptr_t)m_fileImage.getTextureId(), button_sz, uv0, uv1, bg_col, tint_col)) {
				std::string stringPath = m_fileModel.getFileFullPath(labelFileName);
				//loadImageInGPU(stringPath);
				load3DModel(stringPath);
			}
		}
		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 50.0f);
		ImGui::Text(labelFileName.c_str());
		ImGui::PopTextWrapPos();
		ImGui::EndGroup();

		float last_button_x2 = ImGui::GetItemRectMax().x;
		float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected m_position if next button was on same line
		if (i + 1 < buttons_count && next_button_x2 < window_visible_x2)
			ImGui::SameLine();
		ImGui::PopID();
	}

}
// loadtexture
void FileExplorerDisplay::loadImageInGPU(const std::string path) {
	//Texture texture;
	//int texId = texture.generateTexture(path);
	//m_loadedImages.push_back(texId);
}

void FileExplorerDisplay::load3DModel(const std::string path) {
	//"resources/models/cube.obj"
	//std::cout << path << std::endl;
	//ModelLoader modelLoader;
	//std::vector<Mesh> meshes = modelLoader.loadModel(path);
	//
	//for (int i = 0; i < meshes.size(); i++) {
	//	Mesh mesh = meshes.at(i);
	//	m_scene.addMesh(mesh);
	//}
}