#include <iostream>
#include <regex>
#include "phonebook.h"
#include "valid.h"

int main() {
    Phonebook book;
    book.load("data.txt");

    while (true) {
        std::cout << "\n1. Add contact\n2. Show all contact\n3. Remove contact\n4. Edit contact\n5. Save\n6. Exit\n> ";
        int cmd;
        std::cin >> cmd;
        std::cin.ignore();

        if (cmd == 1) {
            std::string first = Validation::getValidatedName();
            std::string last  = Validation::getValidatedSurname();
            std::string email = Validation::getValidatedEmail();
            std::vector<std::string> phones = Validation::getValidatedPhonenumber();
            std::string datebirth = Validation::getValidatedDate();
            std::string mid = Validation::getValidatedMiddleName();
            std::string adr = Validation::getValidatedAddress();
            Contact c(first, last, mid, adr, email, phones, datebirth);
            book.addcontact(c);
        }
        else if (cmd == 2) {
            book.printall();
        }
        else if (cmd == 3) {
            int i;
            std::cout << "Contact's number: ";
            std::cin >> i;
            std::cin.ignore();
            book.removecontact(i);
        }
        else if (cmd == 4){
            book.editcontact(book);
        }
        else if (cmd == 5) {
            book.save("data.txt");
        }
        else if (cmd == 6) break;
    }
}
