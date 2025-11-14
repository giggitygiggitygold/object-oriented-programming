#pragma once

#include "contact.h"
#include <vector>

class Phonebook{
    private:
        std::vector<Contact> contacts;
    
    public:
        void addcontact(const Contact& c);
        void removecontact(int index);
        void editcontact(Phonebook& book);

        void save(const std::string& filename);
        void load(const std::string& filename);

        void printall() const;
        int size() const;
};