#pragma once

#include <glad/glad.h>
#include <string>

#include <src/engine/scene/TextureData.h>

#include <memory>

class Texture {

public:
	Texture(TextureData textureData);
//	Texture(unsigned int width, unsigned int height, unsigned char* imageData);
//	Texture(const std::string& texturePath, const std::string textureName);
//	Texture(const std::string& texturePath);

	void bind(GLenum textureUnit = 0) const;
	void unbind() const;
	void deleteTexture() const;

	const TextureData& getTextureData() const;
	unsigned int getTextureId() const;
	bool isLoaded();



private:
	void loadTexture(const std::string& texturePath);
	void generateTexture(unsigned int width, unsigned int height, unsigned char* imageData);

private:
	//std::unique_ptr<TextureData> m_textureData;
	TextureData m_textureData;
	unsigned int m_textureId;
	int m_bytesPerPixel;
	bool m_isLoaded;
};
