#pragma once
#include <map>
#include <vector>
#include <memory>

#include "Texture.h"

class TextureCache {
public:
	TextureCache();

//	Texture& createTexture(const TextureData& textureData);
	//Texture& createTexture(const std::string& texturePath, const std::string textureName);
	void clearTextureCache();

	void addTexture(Texture texture);
	void addTextures(const std::vector<TextureData>& textureDataVec);

	std::map<std::string, Texture>& getTextures();
	Texture& getTexture(const std::string& texturePath);
	const unsigned int getSize();

private:
	const std::string m_defaultTexturePath = "./resources/images/TexelGrid.png";
	std::map<std::string, Texture> m_textureCache;
};
