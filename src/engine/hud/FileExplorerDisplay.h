#pragma once

#include <string>

#include "src/engine/scene/Texture.h"
#include "../FileModel.h"

#include "../scene/Scene.h"

class FileExplorerDisplay {

public:
	FileExplorerDisplay(Scene& scene);
	void displayAsPopupModal();
	void displayAsWindow();
	void displayAsPopup();

private:
	void display();
	void createDirectory();
	void loadImageInGPU(const std::string path);

	void load3DModel(const std::string path);


private:
	Scene& m_scene;

	Texture m_DirImage;
	Texture m_fileImage;

	FileModel m_fileModel;
	std::vector<int> m_loadedImages;


};