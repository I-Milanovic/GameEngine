#pragma once

#include <string>
#include "../utilities/FileListing.h"

class FileModel {
public:
	FileModel();

	void loadParentDir();
	void loadChildDir(std::string newPath);

	void loadDir(const std::string newPath);

	inline std::vector<std::pair<bool, std::string>>& getDirectoryList() { return m_directoryList; };

	inline std::string& getPath() { return m_path; };
	inline void setPath(std::string newPath) { m_path = newPath; };
	inline void setPreviousPath(std::string newPath) { m_previousPath = newPath; };
	inline std::string getPreviousPath() { return m_previousPath; };

	std::string getFileFullPath(const std::string fileName);

private:
	std::string m_path;
	std::string m_parentPath;
	std::string m_previousPath;

	FileListing m_fileListing;
	std::vector<std::pair<bool, std::string>> m_directoryList;
};

