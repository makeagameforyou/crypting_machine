/**
 * @file password.cpp
 * @brief This file contains the implementation of the Password class
 */
#pragma once
#include <string>

/**
 * @class Password
 * @brief this class stores all data of user's passwords which are wrote to file
 */
class Password {
    /**
     * @brief This variable stores description of the password
     */
    std::string name_;
    /**
     * @brief This variable stores word which represents password of the password record
     */
    std::string password_;
    /**
     * @brief This variable stores information of the category
     */
    std::string category_;
    /**
     * @brief This variable stores information of the website
     */
    std::string website_;
    /**
     * @brief This variable stores information of the login for some website
     */
    std::string login_;

public:
    /**
     * @brief first constructor which contains 5 parameters
     * @param name name to create
     * @param password password to create
     * @param category category to create
     * @param website website to create
     * @param login login to create
     */
    Password(const std::string &name, const std::string &password, const std::string &category,
             const std::string &website, const std::string &login);
    /**
     * @brief second constructor which contains 3 parameters
     * @param name name to create
     * @param password password to create
     * @param category category to create
     */
    Password(const std::string &name, const std::string &password, const std::string &category);
    /**
     * @brief destructor of the Password object
     */
    ~Password(){}

    const std::string &getName() const {
        return name_;
    }

    const std::string &getPassword() const {
        return password_;
    }

    const std::string &getCategory() const {
        return category_;
    }

    const std::string &getWebsite() const {
        return website_;
    }

    const std::string &getLogin() const {
        return login_;
    }
};

