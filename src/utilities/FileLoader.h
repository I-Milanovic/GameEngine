#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>

class FileLoader {
public: 
	std::string readFile(const std::string filePath);
};