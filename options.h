/**
 * @file options.cpp
 * @brief This file contains implementation of methods used in main.cpp
 */
#pragma once
#include <string>
#include <set>

namespace options {
    /**
     * @brief finding password from file .txt
     * @param parameter variable used to make criterion what to find
     * @param masterKey variable used to decrypt encrypted data in file
     * @param file variable used to open file .txt which contains encrypted data
     */
    auto findPassword(const std::string &parameter, const std::string &masterKey, std::fstream &file) -> void;

    /**
     * @brief printing whole passwords
     * @param masterKey variable used to decrypt encrypted data in file
     * @param file variable used to open file .txt which contains encrypted data
     * @param filePath variable which contains path or name of file .txt
     */
    auto showPasswords(const std::string &masterKey, std::fstream &file, const std::string &filePath) -> void;

    /**
     * @brief writing new password that contains 5 parameters in file .txt
     * @param newName variable which contains description of password
     * @param newPassword variable which represents password of the password record
     * @param newCategory variable which contains information of category
     * @param newWebsite variable which contains information of website
     * @param newLogin variable which contains information of login for website
     * @param masterKey variable used to encrypt data
     * @param file variable that stores a file to open
     */
    auto addPassword(std::string newName, std::string newPassword, std::string newCategory, std::string newWebsite,
                     std::string newLogin, const std::string &masterKey, std::fstream &file) -> void;

    /**
     * @brief writing new password that contains 3 parameters in file .txt
     * @param newName variable which contains description of password
     * @param newPassword variable which represents password of the password record
     * @param newCategory variable which contains information of category
     * @param masterKey variable used to encrypt data
     * @param file variable that stores a file to open
     */
    auto addPassword(std::string newName, std::string newPassword, std::string newCategory, const std::string &masterKey,
                     std::fstream &file) -> void;

    /**
     * @brief deleting password from file .txt
     * @param passwordToDelete variable that stores information which password is for deleting
     * @param masterKey variable used to decrypt data
     * @param file variable that stores a file to open
     * @param filePath variable which contains path or name of file .txt
     */
    auto deletePassword(const std::string &passwordToDelete, const std::string &masterKey, std::fstream &file, const std::string &filePath) -> void;

    /**
     * @brief adding new category for passwords
     * @param newCategory variable which contains information of category to create
     * @param masterKey variable used to encrypt data
     * @param file variable that stores a file to open
     */
    auto addCategory(std::string newCategory, const std::string &masterKey, std::fstream &file) -> void;

    /**
     * @brief deleting category
     * @param categoryToDelete variable that stores information which category is for deleting
     * @param masterKey variable used to deccrypt data
     * @param file variable that stores a file to open
     * @param filePath variable which contains path or name of file .txt
     */
    auto deleteCategory(const std::string &categoryToDelete, const std::string &masterKey, std::fstream &file, const std::string &filePath) -> void;

}