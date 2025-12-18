#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <string>

class Encryptor {
public:
    virtual std::string encrypt(const std::string& data) = 0;
    virtual std::string decrypt(const std::string& encrypted) = 0;
    virtual ~Encryptor() {}
};

class XOREncryptor : public Encryptor {
    char key;
public:
    explicit XOREncryptor(char k);
    std::string encrypt(const std::string& data) override;
    std::string decrypt(const std::string& encrypted) override;
};

#endif
