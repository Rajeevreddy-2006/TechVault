#ifndef VAULTITEM_H
#define VAULTITEM_H

#include <string>
#include <ctime>
#include <iostream>

#include "Encryptor.h"

/*
 * Base class for all items stored in the vault.
 * Provides:
 *  - Common metadata (id, name, creation time)
 *  - Encryption support via strategy pattern
 *  - Polymorphic interface for derived items
 */
class VaultItem {
protected:
    int id;                      
    std::string name;           
    std::string createdAt;       
    Encryptor& encryptor;         // Non-owning encryption

public:
    VaultItem(int id, std::string name, Encryptor& enc);

    // Converts object-specific data to string (before encryption)
    virtual std::string toString() const = 0;

    // Encrypts the string representation for storage
    std::string getEncryptedData() const;

    virtual void showInfo() const;

    const std::string& getName() const;

    virtual ~VaultItem() {}
};

#endif
