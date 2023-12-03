#pragma once

#include <string>
#include "../utilities/FileListing.h"

class FileModel {
public:
	FileModel();

	void loadParentDir();
	void loadNewDir(const std::string newPath);
	void loadNewDir();

	inline char& getDeafultPath() { return m_defaultPath[0]; };
	inline int getPathSize() { return pathCharSize; };
	inline std::vector<std::pair<bool, std::string>>& getDirectoryList() { return m_directoryList; };

	inline void setPrviousPath(std::string newPath) { strcpy_s(m_previousPath, newPath.c_str()); };
	inline std::string getPreviousPath() { return m_previousPath; };

	std::string getFileFullPath(const std::string fileName);

private:
	const int pathCharSize = 100;
	char m_parentPath[100];
	char m_defaultPath[100];// = "C:/Users/38163/Desktop";
	char m_previousPath[100];
	FileListing m_fileListing;

	std::vector<std::pair<bool, std::string>> m_directoryList;

};

