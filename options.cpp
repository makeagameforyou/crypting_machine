#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include "options.h"
#include "password.h"
#include "crypting.h"

auto options::findPassword(const std::string &parameter, const std::string &masterKey, std::fstream &file) -> void {

    std::cout << "hasla pasujace do podanego parametru: " << std::endl;
    for (auto line = std::string(); std::getline(file, line);) {
        auto decryptedLine = std::string();
        auto word = std::string();
        auto strStream = std::stringstream(line);
        while (strStream >> word) {
            if (crypting::decryptPassword(word, masterKey) == parameter) {
                auto strStream2 = std::stringstream(line);
                while (strStream2 >> word) {
                    decryptedLine += crypting::decryptPassword(word, masterKey) + " ";
                }
            }
        }
        if (!decryptedLine.empty()) {
            std::cout << decryptedLine << std::endl;
        }
    }
}

auto options::showPasswords(const std::string &masterKey, std::fstream &file, const std::string &filePath) -> void {

    std::cout << "istniejace hasla: " << std::endl;
    for (auto line = std::string(); std::getline(file, line);) {
        auto foundPassword = std::string();
        auto word = std::string();
        auto strStream = std::stringstream(line);
        int wordPosition = 1;

        while (strStream >> word) {
            if (wordPosition == 2) {
                std::cout << crypting::decryptPassword(word, masterKey) << std::endl;
            }
            wordPosition++;
        }
    }
}

auto options::addPassword(std::string newName, std::string newPassword, std::string newCategory, std::string newWebsite,
                          std::string newLogin, const std::string &masterKey, std::fstream &file) -> void {

    auto password = new Password(crypting::encryptPassword(newName, masterKey),
                                 crypting::encryptPassword(newPassword, masterKey),
                                 crypting::encryptPassword(newCategory, masterKey),
                                 crypting::encryptPassword(newWebsite, masterKey),
                                 crypting::encryptPassword(newLogin, masterKey));

    file << password->getName() + " " + password->getPassword() + " " + password->getCategory() +
            " " + password->getWebsite() + " " + password->getLogin() + "\n";
}

auto options::addPassword(std::string newName, std::string newPassword, std::string newCategory,
                          const std::string &masterKey, std::fstream &file) -> void {

    auto password = new Password(crypting::encryptPassword(newName, masterKey),
                                 crypting::encryptPassword(newPassword, masterKey),
                                 crypting::encryptPassword(newCategory, masterKey));

    file << password->getName() + " " + password->getPassword() + " " + password->getCategory() + "\n";
}

auto options::deletePassword(const std::string &passwordToDelete, const std::string &masterKey,
                             std::fstream &file, const std::string &filePath) -> void {

    std::fstream tempFile("tmp.txt", std::ios::app | std::ios::out);
    for (auto line = std::string(); std::getline(file, line);) {
        auto foundPassword = std::string();
        auto word = std::string();
        auto strStream = std::stringstream(line);
        int wordPosition = 1;

        while (strStream >> word) {
            if (wordPosition == 2) {
                if (crypting::decryptPassword(word, masterKey) != passwordToDelete) {
                    tempFile << line << std::endl;
                }
                break;
            }
            wordPosition++;
        }
    }

    file.close();
    tempFile.close();

    std::remove(filePath.c_str());
    std::rename("tmp.txt", filePath.c_str());
}

auto options::addCategory(std::string newCategory, const std::string &masterKey, std::fstream &file) -> void {
    options::addPassword("-----", "-----", crypting::encryptPassword(newCategory, masterKey), "-----", "-----", masterKey, file);
}

auto options::deleteCategory(const std::string &categoryToDelete, const std::string &masterKey, std::fstream &file, const std::string &filePath) -> void {
    std::fstream tempFile("tmp.txt", std::ios::app | std::ios::out);
    for (auto line = std::string(); std::getline(file, line);) {
        auto foundPassword = std::string();
        auto word = std::string();
        auto strStream = std::stringstream(line);
        int wordPosition = 1;

        while (strStream >> word) {
            if (wordPosition == 3) {
                if (crypting::decryptPassword(word, masterKey) != categoryToDelete) {
                    tempFile << line << std::endl;
                }
                break;
            }
            wordPosition++;
        }
    }

    file.close();
    tempFile.close();

    std::remove(filePath.c_str());
    std::rename("tmp.txt", filePath.c_str());
}
