#include "../include/FileItem.h"

#include <iostream>

FileItem::FileItem(int id,
                   std::string name,
                   std::string type,
                   double size,
                   Encryptor& enc)
    : VaultItem(id, std::move(name), enc),
      fileType(std::move(type)),
      fileSize(size)
{
}

std::string FileItem::toString() const {
    return "FileItem|" + name + "|" + fileType + "|" + std::to_string(fileSize);
}

void FileItem::showInfo() const {
    VaultItem::showInfo();
    std::cout << "Type: " << fileType << '\n'
              << "Size: " << fileSize << " MB\n";
}
