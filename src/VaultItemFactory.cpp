#include "../include/VaultItemFactory.h"

#include "../include/FileItem.h"
#include "../include/PasswordItem.h"
#include "../include/SnippetItem.h"

#include <iostream>
#include <string>

VaultItem* VaultItemFactory::create(int choice, Encryptor& encryptor) {
    static int idCounter = 1;

    if (choice == 1) {
        std::string name, type;
        double size;

        std::cout << "Enter file name: ";
        std::getline(std::cin, name);

        std::cout << "Enter file type: ";
        std::getline(std::cin, type);

        std::cout << "Enter file size (MB): ";
        std::cin >> size;
        std::cin.ignore();

        return new FileItem(idCounter++, name, type, size, encryptor);
    }
    else if (choice == 2) {
        std::string name, username, password;

        std::cout << "Enter service name: ";
        std::getline(std::cin, name);

        std::cout << "Enter username: ";
        std::getline(std::cin, username);

        std::cout << "Enter password: ";
        std::getline(std::cin, password);

        return new PasswordItem(idCounter++, name, username, password, encryptor);
    }
    else if (choice == 3) {
        std::string name, language, code;

        std::cout << "Enter snippet name: ";
        std::getline(std::cin, name);

        std::cout << "Enter language: ";
        std::getline(std::cin, language);

        std::cout << "Enter code: ";
        std::getline(std::cin, code);

        return new SnippetItem(idCounter++, name, language, code, encryptor);
    }

    return nullptr;
}
