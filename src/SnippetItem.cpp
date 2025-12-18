#include "../include/SnippetItem.h"

#include <iostream>

SnippetItem::SnippetItem(int id,
                         std::string name,
                         std::string lang,
                         std::string codeText,
                         Encryptor& enc)
    : VaultItem(id, name, enc),
      language(lang),
      code(codeText)
{
}

std::string SnippetItem::toString() const {
    return "SnippetItem|" + name + "|" + language + "|" + code;
}

void SnippetItem::showInfo() const {
    VaultItem::showInfo();
    std::cout << "Language: " << language << '\n'
              << "Code: " << code << '\n';
}
