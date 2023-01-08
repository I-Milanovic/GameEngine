#pragma once
#include <string>

class Texture {

private:
	const std::string texturePath;
	unsigned int textureId;
public:
	Texture(std::string &filePath);
//	void bindTexture();
//	void cleanup();
//	std::string getTexturePath();
//	int getTextureId();

private:
	void generateTexture(unsigned char* data, int width, int height);


};
