#include "FileModel.h"

FileModel::FileModel() : m_fileListing(FileListing()) {
	m_path = m_fileListing.getCurrentPath();
	m_fileListing.listDirectory(m_path, m_directoryList);
}

void FileModel::loadDir(const std::string newPath) {
	bool pathExists = m_fileListing.listDirectory(newPath, m_directoryList);
	if (pathExists) {
		setPreviousPath(m_path);
		setPath(newPath);
	}
}

void FileModel::loadChildDir(std::string childDirName) {
	std::string path;
	path.append(m_path).append("/").append(childDirName);
	loadDir(path);
}

void FileModel::loadParentDir() {
	loadDir(m_fileListing.getParentPath(m_path));
}

std::string FileModel::getFileFullPath(const std::string fileName) {
	std::string filePath;
	return filePath.append(m_path).append("/").append(fileName);
}
