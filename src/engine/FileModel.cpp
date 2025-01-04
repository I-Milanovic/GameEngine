#include "FileModel.h"

FileModel::FileModel() : m_fileListing(FileListing("/resources/images")) {
	m_path = m_fileListing.getCurrentPath();
	m_fileListing.getDirectoryContent(m_path, m_directoryList, ImageFile | ModelFile);
}

void FileModel::loadDir(const std::string newPath) {
	bool pathExists = m_fileListing.getDirectoryContent(newPath, m_directoryList, ImageFile | ModelFile);
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
