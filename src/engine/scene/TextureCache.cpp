#include "TextureCache.h"

TextureCache::TextureCache() {
	TextureData textureData(m_defaultTexturePath, "Default_texture");
	m_textureCache.insert({ textureData.path, Texture(textureData)});	//todo reinstate later
}

//Texture& TextureCache::createTexture(const std::string& texturePath, const std::string textureName) {
//	TextureData textureData(texturePath, textureName);
//	return createTexture(textureData);
//}



//Texture& TextureCache::createTexture(const TextureData& textureData) {
//	if (m_textureCache.contains(textureData.getPath()))
//		return m_textureCache.at(textureData.getPath());
//
//	Texture texture(textureData);
//	m_textureCache.insert({ textureData.getPath(), texture});
//	return texture;
//}
//
void TextureCache::addTexture(Texture texture) {
	TextureData textureData = texture.getTextureData();
	m_textureCache.insert({ textureData.path, texture });
}

void TextureCache::addTextures(const std::vector<TextureData>& textureDataVec) {
	for (TextureData textureData : textureDataVec)
		m_textureCache.insert({ textureData.path, Texture(textureData)});
}

 Texture& TextureCache::getTexture(const std::string& texturePath){
	if(m_textureCache.contains(texturePath))
		return m_textureCache.at(texturePath);
	return  m_textureCache.at(m_defaultTexturePath);
}

const unsigned int TextureCache::getSize() {
	return m_textureCache.size();
}

void TextureCache::clearTextureCache() {
	m_textureCache.clear();
}


std::map<std::string, Texture>& TextureCache::getTextures() {
	return m_textureCache;
}
