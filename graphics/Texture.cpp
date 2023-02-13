#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include <glad/glad.h>

#include "Texture.h"


Texture::Texture(std::string& filePath, bool isAlpha) : isAlpha (isAlpha) {
	int width = 0;
	int height = 0;
	int nChannels = 0;

	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nChannels, 0);
	stbi_set_flip_vertically_on_load(true);

	if (data) {
		generateTexture(data, width, height);
		stbi_image_free(data);
		std::cout << "Texture: " << filePath << " loaded" << std::endl;
	}
	else {
		std::cout << "Failed to load the texture path: " << filePath << std::endl;
//		std::cout << stbi_failure_reason << std::endl;
	}
}

void Texture::generateTexture(unsigned char* data, int width, int height) {
	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	if(isAlpha)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

}

unsigned int Texture::getTextureId() {
	return textureId;
}
