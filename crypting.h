/**
 * @file crypting.cpp
 * @brief This file contains the implementation of methods that encrypt and decrypt some data
 */
#pragma once
#include <string>

namespace crypting {
    /**
     * @brief encrypts inserted data
     * @param data variable to encrypt
     * @param masterKey variable used to encrypt data
     * @return
     */
    auto encryptPassword(std::string data, const std::string &masterKey) -> std::string;
    /**
     * @brief decrypts inserted data
     * @param encryptedData variable to decrypt
     * @param masterKey variable used to decrypt data
     * @return
     */
    auto decryptPassword(std::string encryptedData, const std::string &masterKey) -> std::string;
}
