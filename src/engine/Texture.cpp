#define STB_IMAGE_IMPLEMENTATION
//#include <stb/stb_image.h>
#include <iostream>
#include <glad/glad.h>

#include "Texture.h"

#include "../utilities/ImageLoader.h"

// mozda stavi da je static
unsigned int Texture::generateTexture(const std::string& filePath) {
	
	ImageLoader imageLoader;
	Image image = imageLoader.loadTexture(filePath);


	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, getChannelType(image.nChannels), GL_UNSIGNED_BYTE, image.data);

	glGenerateMipmap(GL_TEXTURE_2D);

	std::cout << "Texture: " << image.path << " loaded, ID : " << textureId << " CHANNELES " << image.nChannels << std::endl;

	return textureId;
}


unsigned int Texture::getChannelType(const unsigned int nChannels) {
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
	return format;
}
