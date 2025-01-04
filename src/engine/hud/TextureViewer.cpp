#include "TextureViewer.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <imgui/imgui_stdlib.h>



TextureViewer::TextureViewer(Scene& scene) : m_scene(scene) {

	Texture textureDirectory("./resources/images/icons/icons8-folder-80.png");
	textureDirectory.getTextureId();
	Texture textureFile("./resources/images/icons/icons8-image-64.png");
	textureFile.getTextureId();

}

// load texture
void TextureViewer::loadImageInGPU(const std::string path) {
	//Texture texture;
	//int texId = texture.generateTexture(path);
	//m_loadedImages.push_back(texId);
}

static const int MAX_PATH = 100;

void TextureViewer::display() {
	ImGui::Begin("Loaded Textures");

	ImVec2 button_sz(128, 128);
	ImVec2 uv0 = ImVec2(1.0f, 0.0f);							// UV coordinates for (32,32) in our texture
	ImVec2 uv1 = ImVec2(0.0f, 1.0f);                            // UV coordinates for lower-left
	ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);             // Black background
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);


	ImGuiStyle& style = ImGui::GetStyle();
	float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

	int imageLen = m_loadedImages.size();

	for (int i = 0; i < imageLen; i++) {
		ImGui::PushID(i);
		if (ImGui::ImageButton(std::to_string(i).c_str(), (void*)(intptr_t)m_loadedImages.at(i), button_sz, uv0, uv1, bg_col, tint_col)) {
			//m_scene.getMesh(0).setTextureId(0, m_loadedImages.at(i));
		}

		float last_button_x2 = ImGui::GetItemRectMax().x;
		float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected m_position if next button was on same line
		if (i + 1 < imageLen && next_button_x2 < window_visible_x2)
			ImGui::SameLine();
		ImGui::PopID();
	}

	ImGui::End();


	// diff


	ImGui::Begin("Files");

	ImVec2 butSize = ImVec2(20.0f, 20.0f);
	ImGui::BeginDisabled(m_fileModel.getPreviousPath().size() == 0);
	if (ImGui::Button("B", butSize))
		m_fileModel.loadDir(m_fileModel.getPreviousPath());
	ImGui::EndDisabled();
	ImGui::SameLine();
	if(ImGui::Button("U", butSize))
		m_fileModel.loadParentDir();
	ImGui::SameLine();

	std::string path = m_fileModel.getPath();
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
	ImGui::End();
}

void TextureViewer::createDirectory() {
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
			if (ImGui::ImageButton(labelFileName.c_str(), (void*)(intptr_t)m_DirImage, button_sz, uv0, uv1, bg_col, tint_col)) {
				m_fileModel.loadChildDir(labelFileName);
			}
		}
		else {
			if (ImGui::ImageButton(labelFileName.c_str(), (void*)(intptr_t)m_fileImage, button_sz, uv0, uv1, bg_col, tint_col)) {
				std::string s = m_fileModel.getFileFullPath(labelFileName);
				//loadImageInGPU(s);
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