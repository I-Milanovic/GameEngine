#pragma once

#include "../FileModel.h"
#include "src/engine/scene/Texture.h"
#include "../scene/Scene.h"

class TextureViewer {

public:
	TextureViewer(Scene& scene);
	void loadImageInGPU(const std::string path);
	void display();


private:
	void createDirectory();

private:
	unsigned int m_DirImage;
	unsigned int m_fileImage;

	FileModel m_fileModel;

	std::vector<int> m_loadedImages;

	Scene& m_scene;

};

