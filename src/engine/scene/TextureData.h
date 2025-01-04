#pragma once

#include <string>
#include <iostream>
struct TextureData {
	TextureData(std::string path, std::string name) : path(path), name(name) {};
	std::string path;
	std::string name;
	int width = 0;
	int height = 0;
};

