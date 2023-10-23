/**
 * @brief This file contains implementation of variables that can be used in other source files
 */
#pragma once
#include <fstream>
#include <string>

/**
 * @brief This variable stores a file which is initialized in main.cpp file
 */
extern std::fstream file;

/**
 * @brief This variable stores a password which can be used to decrypt words in files type .txt. It is initialized in main.cpp file
 */
extern std::string masterKey;

/**
 * @brief This variable stores a name or path of file which user can open during a program. It is initialized in main.cpp file
 */
extern std::string filePath;
