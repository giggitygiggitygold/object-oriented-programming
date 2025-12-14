#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>
#include "phonebook.h"
#include "valid.h"

void Phonebook::addcontact(const Contact& c) {
    contacts.push_back(c);
}

void Phonebook::removecontact(int index) {
    if (index < 1 || index > static_cast<int>(contacts.size())) {
        std::cout << "Invalid index!\n";
        return;
    }
    contacts.erase(contacts.begin() + index - 1);
    std::cout << "Contact removed.\n";
}

void Phonebook::editcontact() {
    if (contacts.empty()) {
        std::cout << "No contacts to edit.\n";
        return;
    }
    printall();
    int index;
    std::cout << "Choose contact number to edit (1-" << contacts.size() << "): ";
    std::cin >> index;
    std::cin.ignore();

    if (index < 1 || index > static_cast<int>(contacts.size())) {
        std::cout << "Invalid index!\n";
        return;
    }

    Contact& c = contacts[index - 1]; // ИСПРАВЛЕНО: было index+1!
    bool editing = true;

    while (editing) {
        std::cout << "\nEditing: " << c.getfirstname() << " " << c.getsurname() << "\n";
        std::cout << "1. Name\n2. Surname\n3. Middle name\n4. Address\n"
                     "5. Email\n6. Phone numbers\n7. Date of Birth\n8. Finish editing\n> ";
        int num;
        std::cin >> num;
        std::cin.ignore();

        switch (num) {
            case 1: c.setfirstname(Validation::getValidatedName()); break;
            case 2: c.setsurname(Validation::getValidatedSurname()); break;
            case 3: c.setmiddlename(Validation::getValidatedMiddleName()); break;
            case 4: c.setaddress(Validation::getValidatedAddress()); break;
            case 5: c.setemail(Validation::getValidatedEmail()); break;
            case 6: {
                std::cout << "Enter new phone numbers (press Enter on empty line to finish):\n";
                std::vector<std::string> phones = Validation::getValidatedPhonenumber();
                c.setphonenumber(phones);
                break;
            }
            case 7: c.setdateofbirth(Validation::getValidatedDate()); break;
            case 8: editing = false; break;
            default: std::cout << "Invalid option.\n";
        }
    }
    std::cout << "Contact updated!\n";
}

void Phonebook::save(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Cannot open file for saving!\n";
        return;
    }
    for (const auto& c : contacts) {
        file << c.tostring() << "\n";
    }
    file.close();
    std::cout << "Saved to " << filename << "\n";
}

void Phonebook::load(const std::string& filename) {
    contacts.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "File " << filename << " not found (will be created on save).\n";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            contacts.push_back(Contact::fromstring(line));
        }
    }
    file.close();
    std::cout << "Loaded " << contacts.size() << " contacts.\n";
}

void Phonebook::printall() const {
    if (contacts.empty()) {
        std::cout << "No contacts.\n";
        return;
    }
    for (size_t i = 0; i < contacts.size(); ++i) {
        std::cout << (i + 1) << ". " << contacts[i] << "\n";
    }
}

int Phonebook::size() const {
    return static_cast<int>(contacts.size());
}

// Вспомогательная функция: привести строку к нижнему регистру
std::string toLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

// Вспомогательная функция: разбить строку на слова
std::vector<std::string> splitWords(const std::string& s) {
    std::istringstream iss(s);
    std::vector<std:: string> words;
    std::string word;
    while (iss >> word) {
        words.push_back(toLower(word));
    }
    return words;
}

void Phonebook::search(const std::string& query) const {
    if (contacts.empty()) {
        std::cout << "No contacts to search.\n";
        return;
    }
    if (query.empty()) {
        std::cout << "Empty search query.\n";
        return;
    }

    std::vector<std::string> keywords = splitWords(query);
    if (keywords.empty()) {
        std::cout << "No valid search terms.\n";
        return;
    }

    bool found = false;
    for (size_t i = 0; i < contacts.size(); ++i) {
        const Contact& c = contacts[i];

        // Собираем все поля в одну строку для поиска
        std::string fullText = 
            c.getfirstname() + " " +
            c.getsurname() + " " +
            c.getmiddlename() + " " +
            c.getaddress() + " " +
            c.getemail() + " " +
            c.getdateofbirth();

        for (const auto& phone : c.getphonenumber()) {
            fullText += " " + phone;
        }

        std::string fullLower = toLower(fullText);

        // Проверяем, что ВСЕ ключевые слова присутствуют
        bool matchesAll = true;
        for (const auto& kw : keywords) {
            if (fullLower.find(kw) == std::string::npos) {
                matchesAll = false;
                break;
            }
        }

        if (matchesAll) {
            std::cout << (i + 1) << ". " << c << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No contacts match the query: \"" << query << "\"\n";
    }
}

void Phonebook::sortByName() {
    std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.getfirstname() < b.getfirstname();
    });
    std::cout << "Sorted by first name.\n";
}

void Phonebook::sortByEmail() {
    std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.getemail() < b.getemail();
    });
    std::cout << "Sorted by email.\n";
}
