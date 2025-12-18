#include "../include/VaultManager.h"

#include "../include/PasswordItem.h"
#include "../include/FileItem.h"
#include "../include/SnippetItem.h"

#include <iostream>
#include <fstream>

// Constructor initializes storage and encryption.
VaultManager::VaultManager(Storage* store, Encryptor& enc)
    : encryptor(enc), storage(store) {}

// Add a vault item (VaultManager takes ownership)
void VaultManager::addItem(VaultItem* item) {
    items.push_back(item);
}

// Save all items using the configured storage
void VaultManager::saveAll() {
    for (auto item : items) {
        storage->saveData(*item);
    }
}

// Display all in-memory items
void VaultManager::showAll() {
    for (auto item : items) {
        item->showInfo();
    }
}

// Load encrypted data and directly decrypt + print
void VaultManager::loadDecrypted() {
    std::ifstream fin("local_storage.txt");
    if (!fin) {
        std::cout << "No local storage file found.\n";
        return;
    }

    std::string encrypted;
    std::cout << "\n---- Decrypted Stored Items ----\n";
    while (std::getline(fin, encrypted)) {
        std::string plain = encryptor.decrypt(encrypted);
        std::cout << plain << '\n';
    }
    fin.close();
}

// Load encrypted data and reconstruct VaultItem objects
void VaultManager::loadAndReconstruct() {
    // Clean existing items
    for (auto item : items) {
        delete item;
    }
    items.clear();

    std::ifstream fin("local_storage.txt");
    if (!fin) {
        std::cout << "No local storage file found.\n";
        return;
    }

    std::string encrypted;
    std::cout << "\n---- Reconstructed Objects ----\n";

    while (std::getline(fin, encrypted)) {
        std::string plain = encryptor.decrypt(encrypted);
        std::vector<std::string> parts;

        std::string token;
        for (char c : plain) {
            if (c == '|') {
                parts.push_back(token);
                token.clear();
            } else {
                token += c;
            }
        }
        parts.push_back(token);

        if (parts.size() < 4) {
            std::cout << "Skipped corrupted entry.\n";
            continue;
        }

        const std::string& type = parts[0];

        if (type == "PasswordItem") {
            VaultItem* item =
                new PasswordItem(100 + items.size(),
                                 parts[1], parts[2], parts[3],
                                 encryptor);
            items.push_back(item);
        }
        else if (type == "FileItem") {
            double size = std::stod(parts[3]);
            VaultItem* item =
                new FileItem(100 + items.size(),
                             parts[1], parts[2], size,
                             encryptor);
            items.push_back(item);
        }
        else if (type == "SnippetItem") {
            VaultItem* item =
                new SnippetItem(100 + items.size(),
                                parts[1], parts[2], parts[3],
                                encryptor);
            items.push_back(item);
        }
        else {
            std::cout << "Unknown item type skipped.\n";
        }
    }

    fin.close();
    std::cout << "\nReconstruction completed.\n";
}

// Load encrypted data via storage and show decrypted content
void VaultManager::loadAndShowAll() {
    std::vector<std::string> encrypted = storage->loadData();

    std::cout << "----- Decrypted Vault Items -----\n";
    for (const auto& e : encrypted) {
        std::cout << encryptor.decrypt(e) << '\n';
    }
}

// Search item by name
void VaultManager::searchByName(const std::string& name) const {
    bool found = false;

    for (auto item : items) {
        if (item->getName() == name) {
            item->showInfo();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No item found with name: " << name << '\n';
    }
}

// Delete item by name
bool VaultManager::deleteByName(const std::string& name) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;          // free memory
            items.erase(it);     // remove from vector
            std::cout << "Item deleted successfully.\n";
            return true;
        }
    }

    std::cout << "No item found with name: " << name << '\n';
    return false;
}

// Destructor cleans owned VaultItem objects
VaultManager::~VaultManager() {
    for (auto item : items) {
        delete item;
    }
    items.clear();
}
