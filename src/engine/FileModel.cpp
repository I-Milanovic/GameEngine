#include "FileModel.h"

FileModel::FileModel() : m_fileListing(FileListing()) {
//	m_defaultPath = m_fileListing.getCurrentPath();
	strcpy_s(m_defaultPath, m_fileListing.getCurrentPath().c_str());
	m_fileListing.listDirectory(m_defaultPath, m_directoryList);
	m_fileListing.displayPathInfo();
}


void FileModel::loadNewDir() {
//	setPrviousPath(m_defaultPath);
	// need to implemented in the intput text action 
	m_fileListing.listDirectory(m_defaultPath, m_directoryList);
	std::cout << getPreviousPath() << std::endl;
}

void FileModel::loadParentDir() {
	setPrviousPath(m_defaultPath);
	strcpy_s(m_parentPath, m_fileListing.getParentPath(m_defaultPath).c_str());
	strncpy_s(m_defaultPath, m_parentPath, 100);
//	std::cout << m_defaultPath << std::endl;
	m_fileListing.listDirectory(m_defaultPath, m_directoryList);
	std::cout << getPreviousPath() << std::endl;
}

void FileModel::loadNewDir(const std::string childDir) {
	setPrviousPath(m_defaultPath);
	std::string slash = "/";
	std::string s = slash + childDir;
	//std::cout << s.c_str() << std::endl;

	strcat_s(m_defaultPath, s.c_str());

	m_fileListing.listDirectory(m_defaultPath, m_directoryList);
	std::cout << getPreviousPath() << std::endl;
}

std::string FileModel::getFileFullPath(const std::string fileName) {
	std::string slash = "/";
	return m_defaultPath + slash + fileName;
}
