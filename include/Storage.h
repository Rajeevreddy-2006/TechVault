#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>

#include "Logger.h"
#include "VaultItem.h"

/*
 * Abstract storage interface.
 * Handles saving and loading encrypted vault data.
 */
class Storage {
protected:
    Logger* logger;   // non-owning pointer (used for logging only)

public:
    explicit Storage(Logger* logger);

    // Save encrypted data of a vault item
    virtual void saveData(const VaultItem& item) = 0;

    // Load encrypted data as raw strings
    virtual std::vector<std::string> loadData() = 0;

    virtual ~Storage() {}
};

// Local file-based storage
class LocalStorage : public Storage {
public:
    explicit LocalStorage(Logger* logger);

    void saveData(const VaultItem& item) override;
    std::vector<std::string> loadData() override;
};

// Simulated cloud storage
class CloudStorage : public Storage {
public:
    explicit CloudStorage(Logger* logger);

    void saveData(const VaultItem& item) override;
    std::vector<std::string> loadData() override;
};

#endif
