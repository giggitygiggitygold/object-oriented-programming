#pragma once
#include <string>
#include <iostream>
#include <regex>

class Validation{
    public:
        static std::string getValidatedName();
        static std::string getValidatedEmail();
        static std::string getValidatedMiddleName();
        static std::string getValidatedAddress();
        static std::vector<std::string> getValidatedPhonenumber();
        static std::string getValidatedSurname();
        static bool isleapyear(int year);
        static int daysinmonth(int month, int year);
        static bool isValidBirthDate(const std::string& dob);
        static std::string getValidatedDate();
};