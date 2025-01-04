#pragma once

#include "src/engine/scene/Scene.h"

#include "FileExplorerDisplay.h"

class PropertyPanel {


public:
	PropertyPanel(Scene& m_scene);
	void display();

private:
	FileExplorerDisplay m_fileExplorerDisplay;
	Scene& m_scene;
};
