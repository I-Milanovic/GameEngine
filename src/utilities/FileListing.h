#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

#include <utility>
#include <vector>


namespace fs = std::filesystem;


enum FileType {
	AllFiles = 1 << 0,
	ImageFile = 1 << 1,
	ModelFile = 1 << 2
};

class FileListing {

public:
	FileListing();
	FileListing(std::string chidlDir);
	void displayPathInfo();
	std::string getParentPath(const std::string path);
	// returns the absolute path of the current working directory with appended /resources/images
	std::string getCurrentPath();

	bool getDirectoryContent(const std::string path, std::vector<std::pair<bool, std::string>>& list, FileType filterFileType);
	


private:
	bool isImageFunc(auto& entry);
	bool isModelFunc(auto& entry);

private:
	std::string m_startingPath;
};

//typedef int FileType;

inline FileType operator|(FileType a, FileType b) {
	return static_cast<FileType>(static_cast<int>(a) | static_cast<int>(b));
}