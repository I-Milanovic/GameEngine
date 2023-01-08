#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include <glad/glad.h>

#include "Texture.h"


Texture::Texture(std::string &filePath) {
	int width = 0;
	int height = 0;
	int nChannels = 0;

	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nChannels, 0);

	if (data) {
		generateTexture(data, width, height);
		stbi_image_free(data);
	}
	else {
		std::cout << "Failed to load the texture path: " << filePath << std::endl;
//		std::cout << stbi_failure_reason << std::endl;
	}


}

void Texture::generateTexture(unsigned char* data, int width, int height) {
	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	//glPixelStorei

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}




