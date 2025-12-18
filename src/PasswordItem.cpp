#include "../include/PasswordItem.h"

#include <iostream>

PasswordItem::PasswordItem(int id,
                           std::string name,
                           std::string user,
                           std::string pass,
                           Encryptor& enc)
    : VaultItem(id, std::move(name), enc),
      username(std::move(user)),
      password(std::move(pass))
{
}

std::string PasswordItem::toString() const {
    return "PasswordItem|" + name + "|" + username + "|" + password;
}

void PasswordItem::showInfo() const {
    VaultItem::showInfo();
    std::cout << "Username: " << username << '\n'
              << "Password: [HIDDEN]\n";
}
