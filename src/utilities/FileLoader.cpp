#include "FileLoader.h"
using namespace std;

	std::string FileLoader::readFile(const std::string filePath) {
		std::ifstream file(filePath, std::ios::in);
		if (!file)
			std::cout << "File doesn't exist at path: " << filePath << std::endl;

		std::string data((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
		file.close();

		return data;
	}