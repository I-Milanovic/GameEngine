#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include <glad/glad.h>

#include "Texture.h"


// mozda stavi da je static
unsigned int Texture::generateTexture(const std::string& filePath) {
	int width, height, nChannels;

	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nChannels, 0);
	stbi_set_flip_vertically_on_load(true);

	if (!data) {
		std::cout << "Failed to load the texture path: " << filePath << std::endl;
		return 0;
	}

	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	GLenum format = 0;
	switch (nChannels) {
		case 1:
			format = GL_RED;
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	std::cout << "Texture: " << filePath << " loaded, ID : "  << textureId << " CHANNELES " << nChannels << std::endl;
	stbi_image_free(data);

	return textureId;
}
