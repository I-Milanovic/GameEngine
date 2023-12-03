#pragma once
#include <string>
class Texture {

public:
	unsigned int generateTexture(const std::string& filePath);
	unsigned int getTextureId() { return textureId; };

private:
	unsigned int getChannelType(const unsigned int nChannels);


private:
	const std::string texturePath;
	unsigned int textureId;

};
