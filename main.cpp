#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <ctime>
#include <set>
#include "options.h"
#include "crypting.h"

auto fillCategoriesSet(std::set<std::string> &categories, const std::string &masterKey, std::fstream &file) -> void;

int main() {
    std::cout << "wybierz:\n1. podaj cala sciezke do pliku z twoimi haslami\n2. wpisz nazwe swojego pliku z haslami\n"
                 "3. stworz nowy plik z haslami" << std::endl;
    int choise;
    std::cin >> choise;
    std::string filePath;
    std::fstream file;
    std::string masterKey;
    std::set<std::string> categories;

    switch (choise) {
        case 1:
            std::cout << "podaj calkowita sciezke do pliku" << std::endl;
            std::cin >> filePath;
            if (!std::filesystem::exists(filePath)) {
                std::cout << "nie znaleziono pliku" << std::endl;
                exit(404);
            } else {
                std::cout << "podaj haslo do pliku" << std::endl;
                std::cin >> masterKey;
                file.open(filePath, std::ios::in);
                fillCategoriesSet(categories, masterKey, file);
                file.close();
            }
            break;
        case 2:
            std::cout << "podaj nazwe swojego pliku z haslami" << std::endl;
            std::cin >> filePath;
            if (!std::filesystem::exists(filePath)) {
                std::cout << "nie znaleziono pliku" << std::endl;
                exit(404);
            } else {
                std::cout << "podaj haslo do pliku" << std::endl;
                std::cin >> masterKey;
                file.open(filePath, std::ios::in);
                fillCategoriesSet(categories, masterKey, file);
                file.close();
            }
            break;
        case 3:
            std::cout << "podaj nazwe dla swojego nowego nowego pliku z haslami" << std::endl;
            std::cin >> filePath;
            file = std::fstream(filePath, std::ios::app | std::ios::out | std::ios::in);
            file.close();
            std::cout << "podaj haslo do pliku" << std::endl;
            std::cin >> masterKey;
            break;
    }

    bool run = true;
    while (run) {
        std::cout << "wybierz:\n1. wyszukaj hasla\n2. wyswietl wszystkie hasla\n3. edytuj haslo\n"
                     "4. dodaj haslo\n5. usun haslo\n""6. dodaj kategorie\n7. usun kategorie\n8. WYJDZ Z PROGRAMU"
                  << std::endl;
        std::cin >> choise;
        switch (choise) {
            case 1: {
                std::string parameter;
                std::cout<< "wpisz dowolny jeden parametr podany podczas tworzenia hasla czyli: \n(twoj opis)\n\tlub\n"
                           "(twoje""haslo)\n\tlub\n(twoja kategoria)\n\tlub\n(twoja strona)\n\tlub\n(twoj login)"
                           << std::endl;
                std::cin >> parameter;

                file.open(filePath, std::ios::in);
                options::findPassword(parameter, masterKey, file);
                file.close();
            }
                break;
            case 2: {
                file.open(filePath, std::ios::in);
                options::showPasswords(masterKey, file, filePath);
                file.close();
            }
                break;
            case 3: {
                std::cout << "istniejace hasla:" << std::endl;
                std::cout << "NAME  PSWR  CTGR  WEB  LOG\n" << std::endl;
                file = std::fstream(filePath, std::ios::in);
                for (auto line = std::string(); std::getline(file, line);) {
                    auto decryptedLine = std::string();
                    auto word = std::string();
                    auto strStream = std::stringstream(line);
                    while (strStream >> word) {
                        decryptedLine += crypting::decryptPassword(word, masterKey) + " ";
                    }
                    std::cout << decryptedLine << std::endl;
                }
                file.close();

                std::cout << "wpisz haslo, ktore chcesz zedytowac:" << std::endl;
                std::string passwordToEdit;
                std::cin >> passwordToEdit;
                file = std::fstream(filePath, std::ios::app | std::ios::out | std::ios::in);
                options::deletePassword(passwordToEdit, masterKey, file, filePath);
                std::cout << "zmien dane do hasla:" << std::endl;
            }

            case 4: {
                std::string autoPassword = "";
                std::string name, password, category, website, login;
                std::cout << "podaj opis (BEZ SPACJI):" << std::endl;
                std::cin >> name;
                std::cout << "czy wygenerowac haslo automatycznie?\n1. TAK\n2. NIE" << std::endl;
                std::cin >> choise;
                if (choise == 2) {
                    std::cout << "podaj haslo:" << std::endl;
                    std::cin >> password;
                    int upperCase = 0;
                    int specialChars = 0;
                    int charCount = 0;
                    int numbers = 0;
                    for (char c: password) {
                        charCount++;
                        if (c >= 48 && c <= 57) {
                            numbers++;
                        } else if (c >= 65 && c <= 90) {
                            upperCase++;
                        } else if (c >= 127 && c <= 255) {
                            specialChars++;
                        }
                    }
                    if (charCount < 5) {
                        std::cout << "liczba znakow hasla: " << charCount << std::endl;
                        std::cout << "HASLO NIEBEZPIECZNE! zaleca sie usuniecie hasla i stworzenie dluzszego"
                                  << std::endl;
                    } else if (upperCase == 0 && numbers == 0 && specialChars == 0) {
                        std::cout
                                << "HASLO NIEBEZPIECZNE! zaleca sie usuniecie hasla i stworzenie kolejnego zawierajacego "
                                   "duze litery, cyfry lub znaki specjalne, aby twoje haslo bylo bardziej bezpieczne"
                                << std::endl;
                    } else if ((upperCase > 0 && numbers == 0 && specialChars == 0) ||
                               (upperCase == 0 && numbers > 0 && specialChars == 0) ||
                               (upperCase == 0 && numbers == 0 && specialChars > 0)) {
                        std::cout << "SILA HASLA: WYSTARCZAJACE" << std::endl;
                    } else if ((upperCase > 0 && numbers > 0 && specialChars == 0) ||
                               (upperCase > 0 && numbers == 0 && specialChars > 0) ||
                               (upperCase == 0 && numbers > 0 && specialChars > 0)) {
                        std::cout << "SILA HASLA: DOBRE" << std::endl;
                    } else if (upperCase > 0 && numbers > 0 && specialChars > 0) {
                        std::cout << "SILA HASLA: TURBO BEZPIECZNE" << std::endl;
                    }
                } else if (choise == 1) {
                    auto charCount = 0;
                    auto upperLowerCase = 0;
                    auto specialChars = 0;
                    std::cout << "z ilu znakow ma skladac sie twoje haslo?" << std::endl;
                    std::cin >> charCount;
                    std::cout << "czy twoje haslo ma skladac sie z duzych i malych liter?\n1. TAK\n2. NIE" << std::endl;
                    std::cin >> upperLowerCase;
                    if (upperLowerCase != 1 && upperLowerCase != 2) {
                        std::cout << "ERROR     nie ma takiej opcji" << std::endl;
                        break;
                    }
                    std::cout << "czy twoje haslo ma zawierac znaki specialne?\n1. TAK\n2. NIE" << std::endl;
                    std::cin >> specialChars;
                    if (specialChars != 1 && specialChars != 2) {
                        std::cout << "ERROR     nie ma takiej opcji" << std::endl;
                        break;
                    }
                    std::srand(std::time(nullptr));
                    for (int i = 0; i < charCount; ++i) {
                        if (i % 2) {
                            if (upperLowerCase == 1) {
                                int randomNumber = std::rand() % 1;
                                if (randomNumber == 0) {
                                    char randomLetter = std::rand() % 31 + 60;
                                    autoPassword += randomLetter;
                                } else {
                                    char randomLetter = std::rand() % 26 + 97;
                                    autoPassword += randomLetter;
                                }
                            }
                        } else if (i % 3) {
                            if (specialChars == 1) {
                                int randomLetter = std::rand() % 129 + 126;
                                autoPassword += randomLetter;
                            } else {
                                continue;
                            }
                        } else {
                            char randomLetter = std::rand() % 31 + 60;
                            autoPassword += randomLetter;
                        }
                    }
                    password = autoPassword;
                } else {
                    std::cout << "ERROR     nie ma takiej opcji" << std::endl;
                    break;
                }

                std::cout << "podaj kategorie:" << std::endl;
                std::cin >> category;
                bool inCategories = false;
                for (std::string s: categories) {
                    if (category == s) {
                        inCategories = true;
                        break;
                    }
                }
                if (inCategories == false) {
                    std::cout << "podana kategoria nie istenie\nczy chcesz ja utworzyc?\n1. TAK\n2. NIE" << std::endl;
                    int decision;
                    std::cin >> decision;
                    if (decision == 1) {
                        categories.insert(category);
                    } else if (decision == 2) {
                        std::cout << "nie mozesz dodac hasla nie wybierajac lub tworzac nowej kategorii" << std::endl;
                        break;
                    } else {
                        std::cout << "nie ma takiej opcji" << std::endl;
                    }
                }
                std::cout << "podaj strone:     |     wpisz: skip aby pominac ten krok" << std::endl;
                std::cin >> website;
                std::cout << "podaj login:      |     wpisz: skip aby pominac ten krok" << std::endl;
                std::cin >> login;

                file.open(filePath, std::ios::in);
                std::string word;

                bool isInFile = false;
                while (file >> word) {
                    if (crypting::decryptPassword(word, masterKey) == password) {
                        file.close();
                        std::cout << "podane haslo juz istnieje, nie mozesz dodac hasla, ktore juz istnieje"
                                  << std::endl;
                        isInFile = true;
                        break;
                    }
                }
                file.close();

                file.open(filePath, std::ios::app | std::ios::out);
                if (website != "skip" && login != "skip" && !isInFile) {
                    options::addPassword(name, password, category, website,
                                         login, masterKey, file);
                    std::cout << "haslo zostalo pomyslnie utworzone" << std::endl;
                } else if (website == "skip" && login == "skip" && !isInFile) {
                    options::addPassword(name, password, category, masterKey, file);
                    std::cout << "haslo zostalo pomyslnie utworzone" << std::endl;
                }
                file.close();
            }
                break;
            case 5: {
                file = std::fstream(filePath, std::ios::in);
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
                file.close();

                std::vector<std::string> passwordsToDelete;
                bool deleting = true;
                while (deleting) {
                    std::cout << "\nwpisz haslo ktore chcesz usunac\njezeli chcesz przestac wpisz: stop" << std::endl;
                    std::string password;
                    std::cin >> password;
                    if (password == "stop") {
                        deleting = false;
                    } else {
                        passwordsToDelete.push_back(password);
                    }
                }

                int decision;
                if (passwordsToDelete.size() > 1) {
                    std::cout << "UWAGA USUWASZ KILKA HASEL\nCZY NAPEWNO CHCESZ KONTYNNUOWAC?\n1. TAK\n2. NIE\n"
                                 "3. COFNIJ WPISANIE OSTATNIEGO HASLA I KONTYNNUUJ" << std::endl;
                    std::cin >> decision;
                    if (decision == 1) {
                        for (int i = 0; i < passwordsToDelete.size(); ++i) {
                            file = std::fstream(filePath, std::ios::app | std::ios::out | std::ios::in);
                            options::deletePassword(passwordsToDelete[i], masterKey, file, filePath);
                        }
                    } else if (decision == 2) {
                        break;
                    } else if (decision == 3) {
                        passwordsToDelete.pop_back();
                        for (int i = 0; i < passwordsToDelete.size(); ++i) {
                            file = std::fstream(filePath, std::ios::app | std::ios::out | std::ios::in);
                            options::deletePassword(passwordsToDelete[i], masterKey, file, filePath);
                        }
                    } else {
                        std::cout << "nie ma takiej opcji" << std::endl;
                        break;
                    }
                } else if (passwordsToDelete.size() == 1) {
                    std::cout << "CZY NAPEWNO CHCESZ USUNAC HASLO?\n1. TAK\n2. NIE" << std::endl;
                    std::cin >> decision;
                    if (decision == 1) {
                        file = std::fstream(filePath, std::ios::app | std::ios::out | std::ios::in);
                        options::deletePassword(passwordsToDelete[0], masterKey, file, filePath);
                    } else {
                        std::cout << "nie podales zadnego hasla" << std::endl;
                        break;
                    }
                }
                std::cout << "haslo zostalo pomyslnie usuniete" << std::endl;
            }
                break;
            case 6: {
                std::cout << "oto istniejace kategorie:" << std::endl;
                for (std::string s: categories) {
                    std::cout << s << std::endl;
                }
                std::cout << "wprowadz kategorie, ktora chcesz dodac" << std::endl;
                std::string newCategory;
                std::cin >> newCategory;
                categories.insert(newCategory);
                file = std::fstream(filePath, std::ios::app | std::ios::out | std::ios::in);
                options::addCategory(newCategory, masterKey, file);
                file.close();
            }
                break;
            case 7: {
                std::cout << "oto istniejace kategorie:" << std::endl;
                for (std::string s: categories) {
                    std::cout << s << std::endl;
                }
                std::cout << "\nwprowadz kategorie, ktora chcesz usunac:" << std::endl;
                std::string categoryToDelete;
                std::cin >> categoryToDelete;
                categories.erase(categoryToDelete);
                file = std::fstream(filePath, std::ios::app | std::ios::out | std::ios::in);
                options::deleteCategory(categoryToDelete, masterKey, file, filePath);
                file.close();
            }
                break;
            case 8:
                run = false;
                break;
            default:
                std::cout << "nie ma takiej opcji" << std::endl;
        }
    }

}

auto fillCategoriesSet(std::set<std::string> &categories, const std::string &masterKey, std::fstream &file) -> void {
    for (auto line = std::string(); std::getline(file, line);) {
        auto foundCategory = std::string();
        auto word = std::string();
        auto strStream = std::stringstream(line);
        int wordPosition = 1;

        while (strStream >> word) {
            if (wordPosition == 3) {
                categories.insert(crypting::decryptPassword(word, masterKey));
                break;
            }
            wordPosition++;
        }
    }
}



