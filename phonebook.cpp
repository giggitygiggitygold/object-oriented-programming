#include <iostream>
#include "phonebook.h"
#include <fstream>
#include "valid.h"
#include <string>

void Phonebook::addcontact(const Contact& c){
    contacts.push_back(c);
}

void Phonebook::removecontact(int index){
    if (index >= 0 && index < contacts.size()){
        contacts.erase(contacts.begin() + index);
    }
}

void Phonebook::editcontact(Phonebook& book){
    book.printall();
    int index;
    std::cout << "Choose a contact id to edit: ";
    std::cin >> index;

    if (index < 0 || index >= book.size()){
        return;
    }

    Contact& c = contacts[index];
    bool editing = true;

    while (editing){
        std::cout << "Choose a field to edit:\n";
        std::cout << "1. Name\n2. Surname\n3. Middle name\n4. Address\n 5. Email\n6. Phonenumber\n7. Date Of Birth\n8. Exit editing\n";
        int num;
        std::cin >> num;
        switch (num)
        {
            case 1:{
                c.setfirstname(Validation::getValidatedName());
                break;
            }
            case 2:{
                c.setsurname(Validation::getValidatedSurname());
                break;
            }
            case 3:{
                c.setmiddlename(Validation::getValidatedMiddleName());
                break;
            }
            case 4:{
                c.setaddress(Validation::getValidatedAddress());
            }
            case 5:{
                c.setemail(Validation::getValidatedEmail());
                break;
            }
            case 6:{
                std::vector<std::string> phone = Validation::getValidatedPhonenumber();
                std::vector<std::string> phones = { phone };
                c.setphonenumber(phones);
                break;
            }
            case 7:{
                c.setdateofbirth(Validation::getValidatedDate());
                break;
            }
            case 8:{
                editing = false;
                break;
            }
        }
    }
    std::cout << "Contact is edited!!";
}

void Phonebook::save(const std::string& filename){
    std::ofstream file(filename);
    for (auto& c : contacts){
        file << c.tostring() << "\n";
    }
}

void Phonebook::load(const std::string& filename){
    contacts.clear();
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)){
        contacts.push_back(Contact::fromstring(line));
    }
}

void Phonebook::printall() const {
    for (const Contact& c : contacts) {
        std::cout << c << "\n";
    }
}

int Phonebook::size() const{
    return contacts.size();
}