#include "FileListing.h"



//FileListing l;
//std::wcout << l.displayPathInfo() << std::endl;


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
    fs::path p = fs::current_path();
    std::string s = p.string();
    std::replace(s.begin(), s.end(), '\\', '/');
    s.append("/resources/images");
    return s;   
};

bool FileListing::listDirectory(const std::string path, std::vector<std::pair<bool, std::string>>& list) {
    std::filesystem::path pathToDisplay(path);
    if (!std::filesystem::is_directory(pathToDisplay))
        return false;

    list.clear();

    try {
        for (const auto& entry : fs::directory_iterator(pathToDisplay)) {
            bool isFile = entry.is_regular_file();
            bool isDir = entry.is_directory();
            bool isJPG = isFile && (entry.path().extension().compare(".jpg") == 0);
            bool isPNG = isFile && (entry.path().extension().compare(".png") == 0);
            bool isImage = isJPG || isPNG;
       //     bool isBlockFile = entry.is_block_file();


            if (isDir) {
                std::pair<bool, std::string> p(isDir, entry.path().filename().string());
                list.push_back(p);
            }
            if (isImage) {
                std::pair<bool, std::string> p(isDir, entry.path().filename().string());
                list.push_back(p);
            }


        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}



