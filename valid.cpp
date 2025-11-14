#include "valid.h"
#include <regex>
#include <iostream>
#include <sstream>
#include <ctime>

std::string Validation::getValidatedName(){
    std::regex nameRegex("^[A-Za-zА-Яа-я]+$");
    std::string input;
    do {
        std::cout << "Enter your Name: ";
        std::getline(std::cin, input);
        if (!std::regex_match(input, nameRegex))
            std::cout << "Incorrect format!\n";
    } while (!std::regex_match(input, nameRegex));
    return input;
}

std::string Validation::getValidatedMiddleName(){
    std::regex nameRegex("^[A-Za-zА-Яа-я]+$");
    std::string input;
    do {
        std::cout << "Enter your MiddleName: ";
        std::getline(std::cin, input);
        if (!std::regex_match(input, nameRegex))
            std::cout << "Incorrect format!\n";
    } while (!std::regex_match(input, nameRegex));
    return input;
}

std::string Validation::getValidatedAddress(){
    std::regex nameRegex("^[A-Za-zА-Яа-я-]+$");
    std::string input;
    do {
        std::cout << "Enter your Address: ";
        std::getline(std::cin, input);
        if (!std::regex_match(input, nameRegex))
            std::cout << "Incorrect format!\n";
    } while (!std::regex_match(input, nameRegex));
    return input;
}

std::string Validation::getValidatedSurname(){
    std::regex nameRegex("^[A-Za-zА-Яа-я]+$");
    std::string input;
    do {
        std::cout << "Enter your Surname: ";
        std::getline(std::cin, input);
        if (!std::regex_match(input, nameRegex))
            std::cout << "Incorrect format!\n";
    } while (!std::regex_match(input, nameRegex));
    return input;
}

std::string Validation::getValidatedEmail(){
    std::regex emailRegex("^[\\w.-]+@[\\w.-]+\\.[A-Za-z]{2,}$");
    std::string input;
    do {
        std::cout << "Enter your Email: ";
        std::getline(std::cin, input);
        if (!std::regex_match(input, emailRegex))
            std::cout << "Incorrect format!\n";
    } while (!std::regex_match(input, emailRegex));
    return input;
}

std::vector<std::string> Validation::getValidatedPhonenumber(){
    std::regex phoneRegex("^\\+?[0-9-]{7,20}$");
    std::vector<std::string> phones;
    std::string input;
    while (true) {
        std::cout << "Phone: ";
        std::getline(std::cin, input);

        if (input.empty()) break;

        if (std::regex_match(input, phoneRegex)) {
            phones.push_back(input);
        } else {
            std::cout << "Incorrect format! Try again.\n";
        }
    }
    return phones;
}

bool Validation::isleapyear(int year){
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int Validation::daysinmonth(int month, int year){
    switch(month){
        case 2: return isleapyear(year) ? 29 : 28;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}

bool Validation::isValidBirthDate(const std::string& dob) {
    int day, month, year;
    char dot1, dot2;

    std::istringstream ss(dob);
    if (!(ss >> day >> dot1 >> month >> dot2 >> year)) return false;
    if (dot1 != '.' || dot2 != '.') return false;

    if (month < 1 || month > 12) return false;

    if (day < 1 || day > daysinmonth(month, year)) return false;

    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int curYear  = now->tm_year + 1900;
    int curMonth = now->tm_mon + 1;
    int curDay   = now->tm_mday;

    if (year > curYear) return false;
    if (year == curYear && month > curMonth) return false;
    if (year == curYear && month == curMonth && day > curDay) return false;

    return true;
}

std::string Validation::getValidatedDate() {
    std::string input;
    do {
        std::cout << "Enter your Date Of Birth: ";
        std::getline(std::cin, input);
        if (!Validation::isValidBirthDate(input))
            std::cout << "Incorrect date!\n";
    } while (!isValidBirthDate(input));
    return input;
}