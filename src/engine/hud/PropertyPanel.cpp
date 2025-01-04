#include "PropertyPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


static bool isOpen = false;

PropertyPanel::PropertyPanel(Scene& scene) : m_scene(scene), m_fileExplorerDisplay(FileExplorerDisplay(scene)){
}

void PropertyPanel::display() {


	//ImGui::Begin("Tree Test");

	//ImGui::AlignTextToFramePadding();
	//ImGui::SetNextItemOpen(true);
	//bool treeopen = ImGui::TreeNodeEx("Scene", ImGuiTreeNodeFlags_AllowItemOverlap);
	//ImGui::SameLine();
	//if (ImGui::Button("H##1"));


	//if (treeopen) {
	//	
	//	for (auto i = m_scene.getMeshes().begin(); i != m_scene.getMeshes().end(); i++) {
	//		unsigned int key = i->first;
	//		ImGui::PushID(key);
	//		Mesh& m = m_scene.getMesh(key);
	//		ImGui::Checkbox("##", &m.isRendered);
	//		ImGui::SameLine();
	//		ImGui::TreeNodeEx("Item_1", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_AllowItemOverlap);
	//		ImGui::SameLine();
	//		ImGui::Button("X");
	//		ImGui::PopID();
	//	}

	//	for (int i = 0; i < m_scene.getMeshes().size(); i++) {


	//	}

	//	ImGui::TreePop();
	//}

	//if (ImGui::Button("ADD"))
	//	ImGui::OpenPopup("FileExplorerPopUp2");
	//ImGui::SetNextWindowPos(ImVec2(1200/2 - 700/2, 800/2 - 400/2));
	//m_fileExplorerDisplay.displayAsPopup();
	//ImGui::End();
}
