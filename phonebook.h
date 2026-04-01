#pragma once

#include "contact.h"
#include <vector>
#include <string>

class Phonebook {
private:
    std::vector<Contact> contacts;

public:
    void addcontact(const Contact& c);
    void removecontact(int index);
    void editcontact();

    void save(const std::string& filename);
    void load(const std::string& filename);

    void printall() const;
    void search(const std::string& query) const;
    void sortByName();
    void sortByEmail();

    int size() const;
};
