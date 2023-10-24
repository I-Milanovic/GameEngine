#pragma once
#include <string>

class Texture {

public:
	unsigned int generateTexture(const std::string& filePath);
	unsigned int getTextureId() { return textureId; };

private:
	const std::string texturePath;
	unsigned int textureId;

};
