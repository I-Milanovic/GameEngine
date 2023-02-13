#pragma once
#include <string>

class Texture {

private:
	const std::string texturePath;
	unsigned int textureId;
	bool isAlpha;
public:
	Texture(std::string &filePath, bool isAlpha);
//	void bindTexture();
//	void cleanup();
//	std::string getTexturePath();
	unsigned int getTextureId();

private:
	void generateTexture(unsigned char* data, int width, int height);



};
