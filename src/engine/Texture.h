#pragma once
#include <string>

class Texture {

public:
	Texture(const std::string &filePath);
	unsigned int getTextureId() { return textureId; };

private:
	void generateTexture(unsigned char* data, int width, int height, int c);

private:
	const std::string texturePath;
	unsigned int textureId;

};
