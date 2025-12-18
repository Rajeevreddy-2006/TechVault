#ifndef SNIPPETITEM_H
#define SNIPPETITEM_H

#include <string>
#include "VaultItem.h"

/*
 * Represents a code snippet stored in the vault.
 * Stores programming language and the actual code.
 */
class SnippetItem final : public VaultItem {
private:
    std::string language;
    std::string code;

public:
    SnippetItem(int id,
                std::string name,
                std::string lang,
                std::string codeText,
                Encryptor& enc);


    std::string toString() const override;

    void showInfo() const override;
};

#endif
