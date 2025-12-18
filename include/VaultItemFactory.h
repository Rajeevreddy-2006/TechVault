#ifndef VAULTITEMFACTORY_H
#define VAULTITEMFACTORY_H

#include "VaultItem.h"
#include "Encryptor.h"

class VaultItemFactory { // Factory class for creating VaultItems
public:
    // Creates a VaultItem based on user choice
    static VaultItem* create(int choice, Encryptor& encryptor);
};

#endif
