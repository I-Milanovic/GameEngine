#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

#include "ImageLoader.h"

Image ImageLoader::loadTexture(const std::string& filePath) {
	Image image;

	image.data = stbi_load(filePath.c_str(), &image.width, &image.height, &image.nChannels, 0);
	stbi_set_flip_vertically_on_load(true);

	if (!image.data)
		std::cout << "Failed to load the texture, path: " << filePath << std::endl;
	image.path = filePath;
	return image;
}

void ImageLoader::flushImageData(const Image& image) {
	stbi_image_free(image.data);
}
