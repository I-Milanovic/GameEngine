#pragma once

#include "../FileModel.h"
#include "../Texture.h"
#include "../scene/Scene.h"

class TextureViewer {

public:
	TextureViewer(Scene& scene);
	void loadImageInGPU(const std::string path);
	void RenderTextureViewer();

private:
	void createDirectory();

private:
	unsigned int m_DirImageId;
	unsigned int m_fileImageId;
	FileModel m_fileModel;

	Texture m_texture;
	std::vector<int> m_loadedImages;

	Scene& m_scene;

};

