#include "../include/VaultItem.h"

#include <iostream>
#include <ctime>

VaultItem::VaultItem(int id, std::string name, Encryptor& enc)
    : id(id), name(std::move(name)), encryptor(enc)
{
    std::time_t now = std::time(nullptr);
    createdAt = std::ctime(&now);
    createdAt.pop_back(); // remove trailing newline
}

std::string VaultItem::getEncryptedData() const {
    return encryptor.encrypt(toString());
}

void VaultItem::showInfo() const {
    std::cout << "ID: " << id << '\n'
              << "Name: " << name << '\n'
              << "Created At: " << createdAt << '\n';
}

const std::string& VaultItem::getName() const {
    return name;
}
