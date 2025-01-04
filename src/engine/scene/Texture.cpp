#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include "Texture.h"

Texture::Texture(TextureData textureData) : m_textureData(textureData) {
	loadTexture(textureData.path);
}

//Texture::Texture(unsigned int width, unsigned int height, unsigned char* imageData) :
//m_width(width), m_height(height) {
//	generateTexture(width, height, imageData);
//}
//
//Texture::Texture(const std::string& texturePath, const std::string textureName) : m_texturePath(texturePath), m_textureName(textureName) {
//	loadTexture(texturePath);
//}
//
//Texture::Texture(const std::string& texturePath) : Texture(texturePath, "") {
//	
//}

void Texture::loadTexture(const std::string& texturePath) {
	int width, height;
	unsigned char* imageData = stbi_load(texturePath.c_str(), &width, &height, &m_bytesPerPixel, 0);
	if (!imageData) {
		width = m_textureData.width;
		height = m_textureData.height;
	}

	if (!imageData) {
		std::cout << "Failed to load the texture, path: " << texturePath << std::endl;
		//return nullptr;
		m_isLoaded = false;
	}
	generateTexture(width, height, imageData);
	stbi_image_free(imageData);
}

void Texture::generateTexture(unsigned int width, unsigned int height, unsigned char* imageData) {
	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);


	GLenum format = 0;
	switch (m_bytesPerPixel) {
	case 1:
		format = GL_ALPHA;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		format = 0;
		std::cout << "Number of image channels 0" << std::endl;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	std::cout << "Texture: " << m_textureData.path << " loaded, ID : " << m_textureId << " CHANNELES " << m_bytesPerPixel << std::endl;
	glBindTexture(GL_TEXTURE_2D, 0);	// TODO maybe error
	m_isLoaded = true;
}

void Texture::bind(GLenum textureUnit) const {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::deleteTexture() const {
	glDeleteTextures(1, &m_textureId);
}

const TextureData& Texture::getTextureData() const{
	return m_textureData;
}

unsigned int Texture::getTextureId() const {
	return m_textureId;
}

bool Texture::isLoaded() {
	return m_isLoaded;
}