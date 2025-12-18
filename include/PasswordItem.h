#ifndef PASSWORDITEM_H
#define PASSWORDITEM_H

#include <string>
#include "VaultItem.h"

/*
 * Represents a password entry stored in the vault.
 * Stores username and password (password is never displayed in plain text).
 */
class PasswordItem final : public VaultItem {
private:
    std::string username;
    std::string password;

public:
    PasswordItem(int id,
                 std::string name,
                 std::string user,
                 std::string pass,
                 Encryptor& enc);

    std::string toString() const override;

    void showInfo() const override;
};

#endif
