#include <iostream>
#include <string>
#include "phonebook.h"
#include "valid.h"

int main() {
    Phonebook book;
    book.load("data.txt");

    while (true) {
        std::cout << "\n=== PHONEBOOK ===\n";
        std::cout << "1. Add contact\n";
        std::cout << "2. Show all contacts\n";
        std::cout << "3. Search contact\n";
        std::cout << "4. Remove contact\n";
        std::cout << "5. Edit contact\n";
        std::cout << "6. Sort by name\n";
        std::cout << "7. Sort by email\n";
        std::cout << "8. Save\n";
        std::cout << "9. Exit\n> ";
        
        int cmd;
        std::cin >> cmd;
        std::cin.ignore();

        switch (cmd) {
            case 1: {
                std::string first = Validation::getValidatedName();
                std::string last = Validation::getValidatedSurname();
                std::string mid = Validation::getValidatedMiddleName();
                std::string adr = Validation::getValidatedAddress();
                std::string email = Validation::getValidatedEmail();
                std::string birth = Validation::getValidatedDate();
                std::cout << "Enter phone numbers (press Enter on empty line to finish):\n";
                std::vector<std::string> phones = Validation::getValidatedPhonenumber();
                Contact c(first, last, mid, adr, email, phones, birth);
                book.addcontact(c);
                break;
            }
            case 2: book.printall(); break;
            case 3: {
                std::string q;
                std::cout << "Enter search query: ";
                std::getline(std::cin, q);
                book.search(q);
                break;
            }
            case 4: {
                int i;
                std::cout << "Enter contact number to remove: ";
                std::cin >> i;
                std::cin.ignore();
                book.removecontact(i);
                break;
            }
            case 5: book.editcontact(); break;
            case 6: book.sortByName(); break;
            case 7: book.sortByEmail(); break;
            case 8: book.save("data.txt"); break;
            case 9: 
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid command.\n";
        }
    }
}
