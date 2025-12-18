#include "../include/Storage.h"

#include <fstream>
#include <iostream>

// Base storage constructor
Storage::Storage(Logger* logger)
    : logger(logger) {
}

// -------- Local Storage --------

LocalStorage::LocalStorage(Logger* logger)
    : Storage(logger) {
}

// Save encrypted data to local file
void LocalStorage::saveData(const VaultItem& item) {
    std::ofstream fout("local_storage.txt", std::ios::app);
    fout << item.getEncryptedData() << std::endl;
    fout.close();

    logger->logMessage("Encrypted item saved to local storage.");
}

// Load encrypted data from local file
std::vector<std::string> LocalStorage::loadData() {
    std::ifstream fin("local_storage.txt");
    std::vector<std::string> data;
    std::string line;

    while (std::getline(fin, line)) {
        data.push_back(line);
    }
    fin.close();

    logger->logMessage("Loaded data from local storage.");
    return data;
}

// -------- Cloud Storage --------

CloudStorage::CloudStorage(Logger* logger)
    : Storage(logger) {
}

// Save encrypted data to cloud file
void CloudStorage::saveData(const VaultItem& item) {
    std::ofstream fout("cloud_storage.txt", std::ios::app);
    fout << item.getEncryptedData() << std::endl;
    fout.close();

    logger->logMessage("Encrypted item uploaded to cloud storage.");
}

// Load encrypted data from cloud file
std::vector<std::string> CloudStorage::loadData() {
    std::ifstream fin("cloud_storage.txt");
    std::vector<std::string> data;
    std::string line;

    while (std::getline(fin, line)) {
        data.push_back(line);
    }
    fin.close();

    logger->logMessage("Loaded data from cloud storage.");
    return data;
}
