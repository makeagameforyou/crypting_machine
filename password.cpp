#include <string>
#include "password.h"

Password::Password(const std::string &name, const std::string &password, const std::string &category,
                   const std::string &website, const std::string &login)
        : name_(name), password_(password), category_(category), website_(website), login_(login) {}

Password::Password(const std::string &name, const std::string &password, const std::string &category)
        : name_(name), password_(password), category_(category) {}





