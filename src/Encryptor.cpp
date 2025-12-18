#include "../include/Encryptor.h"

XOREncryptor::XOREncryptor(char k) : key(k) {}

std::string XOREncryptor::encrypt(const std::string& data) {
    std::string res = data;
    for (char& c : res) {
        c ^= key;
    }
    return res;
}

std::string XOREncryptor::decrypt(const std::string& encrypted) {
    return encrypt(encrypted);
}
