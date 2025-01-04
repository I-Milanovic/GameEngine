#include "FileListing.h"



FileListing::FileListing() : m_startingPath(fs::current_path().string()) {
    std::replace(m_startingPath.begin(), m_startingPath.end(), '\\', '/');
}

FileListing::FileListing(std::string chidlDir) : m_startingPath(fs::current_path().string()) {
    std::replace(m_startingPath.begin(), m_startingPath.end(), '\\', '/');
    m_startingPath.append(chidlDir);
}

void FileListing::displayPathInfo() {
    //std::string str = "C:/Users/38163/Desktop";
    //std::filesystem::path pathToDisplay(str);

    //std::wostringstream wos;
    //wos << L"root_name() = " << pathToDisplay.root_name() << std::endl
    //    << L"root_path() = " << pathToDisplay.root_path() << std::endl
    //    << L"relative_path() = " << pathToDisplay.relative_path() << std::endl
    //    << L"parent_path() = " << pathToDisplay.parent_path() << std::endl
    //    << L"filename() = " << pathToDisplay.filename() << std::endl
    //    << L"stem() = " << pathToDisplay.stem() << std::endl
    //    << L"extension() = " << pathToDisplay.extension() << std::endl;

    fs::current_path();
    std::cout << "Current path is " << fs::current_path() << std::endl;
    std::cout << "Current path is " << fs::temp_directory_path() << std::endl;
}

std::string FileListing::getParentPath(const std::string path) {
    std::filesystem::path pathToDisplay(path);
    return pathToDisplay.parent_path().string();
}

std::string FileListing::getCurrentPath() { 
    return m_startingPath;   
}


bool FileListing::getDirectoryContent(const std::string path, std::vector<std::pair<bool, std::string>>& list, FileType filterFileType) {
    std::filesystem::path pathToDisplay(path);
    if (!std::filesystem::is_directory(pathToDisplay))
        return false;

    list.clear();

    try {
        for (const auto& entry : fs::directory_iterator(pathToDisplay)) {
            bool isDir = entry.is_directory();
            bool isImage = false;
            bool isModel = false;

            if (filterFileType & ImageFile)
                isImage = isImageFunc(entry);

            if (filterFileType & ModelFile)
                isModel = isModelFunc(entry);

            if (filterFileType & AllFiles && !isDir) {
                isImage = true;
                isModel = true;
            }         

            if (isDir) {
                std::pair<bool, std::string> p(isDir, entry.path().filename().string());
                list.push_back(p);
                continue;
            }
            if (isImage) {
                std::pair<bool, std::string> p(isDir, entry.path().filename().string());
                list.push_back(p);
                continue;
            }
            if (isModel) {
                std::pair<bool, std::string> p(isDir, entry.path().filename().string());
                list.push_back(p);
                continue;
            }

        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool FileListing::isImageFunc(auto& entry) {
    bool isFile = entry.is_regular_file();
    bool isJPG = isFile && (entry.path().extension().compare(".jpg") == 0);
    bool isPNG = isFile && (entry.path().extension().compare(".png") == 0);
    bool isImage = isJPG || isPNG;
    return isImage;
}

bool FileListing::isModelFunc(auto& entry) {
    bool isFile = entry.is_regular_file();
    bool isOBJ = isFile && (entry.path().extension().compare(".obj") == 0);
    bool isMTL = isFile && (entry.path().extension().compare(".mtl") == 0);
    return isOBJ || isMTL;
}


