#ifndef FILEITEM_H
#define FILEITEM_H

#include <string>
#include "VaultItem.h"

/*
 * Represents a file stored in the vault.
 * Stores file-specific metadata such as type and size.
 */
class FileItem final : public VaultItem {
private:
    std::string fileType;   // e.g., txt, pdf
    double fileSize;        // size in MB

public:
    FileItem(int id,
             std::string name,
             std::string type,
             double size,
             Encryptor& enc);

    std::string toString() const override;

    void showInfo() const override;
};

#endif
