#ifndef VAULTMANAGER_H
#define VAULTMANAGER_H

#include <vector>
#include <string>

#include "VaultItem.h"
#include "Storage.h"

/*
 * VaultManager
 * -------------
 * Central controller of the TechVault system.
 * Responsibilities:
 *  - Owns and manages VaultItem objects
 *  - Coordinates saving/loading via Storage
 *  - Uses Encryptor indirectly through VaultItem
 */
class VaultManager
{
private:
    std::vector<VaultItem *> items; // OWNS VaultItem objects
    Encryptor &encryptor;           // non-owning reference
    Storage *storage;               // non-owning pointer

public:
    VaultManager(Storage *store, Encryptor &enc);

    // Add a vault item (ownership transferred to VaultManager)
    void addItem(VaultItem *item);

    // Save all items using the configured storage
    void saveAll();

    void showAll();

    // Load encrypted data and just decrypt + print
    void loadDecrypted();

    // Load encrypted data and reconstruct objects
    void loadAndReconstruct();

    // Load from storage and show decrypted content
    void loadAndShowAll();

    // Search item by name
    void searchByName(const std::string &name) const;

    // Delete item by name
    bool deleteByName(const std::string &name);

    // Destructor cleans owned VaultItem objects
    ~VaultManager();
};

#endif
