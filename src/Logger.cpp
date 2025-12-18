#include "../include/Logger.h"

#include <iostream>
#include <fstream>

void ConsoleLogger::logMessage(const std::string& msg) {
    std::cout << "[Console Log] " << msg << std::endl;
}

FileLogger::FileLogger(std::string file)
    : filename(file) {
}

void FileLogger::logMessage(const std::string& msg) {
    std::ofstream fout(filename, std::ios::app);
    if (!fout) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
        return;
    }
    fout << "[File Log] " << msg << std::endl;
}
