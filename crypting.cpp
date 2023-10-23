#include "crypting.h"
#include "string"

namespace crypting {

    auto encryptPassword(std::string data, const std::string &masterKey) -> std::string {
        std::string result = "";
        int dataLength = data.length();
        int keyLength = masterKey.length();
        for (int i = 0; i < dataLength; ++i) {
            char encryptedChar = data[i] + masterKey[i % keyLength];
            result += encryptedChar;
        }
        return result;
    }

    auto decryptPassword(std::string encryptedData, const std::string &masterKey) -> std::string {
        std::string result = "";
        int encryptedLength = encryptedData.length();
        int keyLength = masterKey.length();
        for (int i = 0; i < encryptedLength; ++i) {
            char decryptedChar = encryptedData[i] - masterKey[i % keyLength];
            result += decryptedChar;
        }
        return result;
    }
}
