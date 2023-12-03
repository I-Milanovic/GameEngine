#pragma once
#include "string"


struct Image {
	std::string path;
	int width = 0;
	int height = 0;
	int nChannels = 0;
	unsigned char* data = 0;
};

class ImageLoader {

	public: 
		Image loadTexture(const std::string& filePath);
		void flushImageData(const Image& image);
};

