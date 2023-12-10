#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

#include <utility>
#include <vector>


namespace fs = std::filesystem;
class FileListing {

public:
	void displayPathInfo();
	std::string getParentPath(const std::string path);

	std::string getCurrentPath();

	bool listDirectory(const std::string path, std::vector<std::pair<bool, std::string>>& list);

};

