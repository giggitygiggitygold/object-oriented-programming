#include "contact.h"
#include <iostream>

Contact::Contact(){}

Contact::Contact(const std::string& first, const std::string& last, const std::string& middle, const std::string& adr, const std::string& mail, const std::vector<std::string>& phones, const std::string& birthdate){
    name = first;
    surname = last;
    middlename = middle;
    address = adr;
    email = mail;
    phonenumber = phones;
    dateofbirth = birthdate;
}

void Contact::setfirstname(const std::string& s){
    name = s;
}
void Contact::setsurname(const std::string& s){
    surname = s;
}
void Contact::setmiddlename(const std::string& s){
    middlename = s;
}
void Contact::setaddress(const std::string& s){
    address = s;
}
void Contact::setdateofbirth(const std::string& s){
    dateofbirth = s;
}
void Contact::setemail(const std::string& s){
    email = s;
}
void Contact::setphonenumber(const std::vector<std::string>& p){
    phonenumber = p;
}

std::string Contact::getfirstname() const{
    return name;
}
std::string Contact::getsurname() const{
    return surname;
}
std::string Contact::getmiddlename() const{
    return middlename;
}
std::string Contact::getaddress() const{
    return address;
}
std::string Contact::getdateofbirth() const{
    return dateofbirth;
}
std::string Contact::getemail() const{
    return email;
}
std::vector<std::string> Contact::getphonenumber() const{
    return phonenumber;
}

std::string Contact::tostring() const{
    std::stringstream ss;
    ss << name << ";"
       << surname << ";"
       << middlename << ";"
       << address << ";"
       << dateofbirth << ";"
       << email << ";";

    for (size_t i = 0; i < phonenumber.size(); ++i) {
        ss << phonenumber[i];
        if (i + 1 < phonenumber.size()) ss << ",";
    }

    return ss.str();
}

Contact Contact::fromstring(const std::string& line){
    std::stringstream ss(line);
    std::string fname, sname, mname, adr, mail, birthdate, phoneline;

    std::getline(ss, fname, ';');
    std::getline(ss, sname, ';');
    std::getline(ss, mname, ';');
    std::getline(ss, adr, ';');
    std::getline(ss, mail, ';');
    std::getline(ss, birthdate, ';');
    std::getline(ss, phoneline, ';');

    std::vector<std::string> phones;
    if (!phoneline.empty()) {
        std::stringstream ps(phoneline);
        std::string p;
        while (std::getline(ps, p, ',')) {
            p.erase(0, p.find_first_not_of(" \t\r\n"));
            p.erase(p.find_last_not_of(" \t\r\n") + 1);
            if (!p.empty()) phones.push_back(p);
        }
    }

    Contact c;
    c.setfirstname(fname);
    c.setsurname(sname);
    c.setmiddlename(mname);
    c.setaddress(adr);
    c.setdateofbirth(birthdate);
    c.setemail(mail);
    c.setphonenumber(phones);

    return c;
}

std::ostream& operator<<(std::ostream& os, const Contact& c){
    os << c.surname << " " << c.name << " " << c.middlename << " " << c.address << " " << c.email << " " << c.dateofbirth << " ";

    if (c.phonenumber.empty()) {
    os << "No phonenumbers";
    } else {
    os << "Phonenumbers: ";
    for (size_t i = 0; i < c.phonenumber.size(); i++) {
        os << c.phonenumber[i];
        if (i + 1 < c.phonenumber.size()) os << ", ";
        }
    }
    os << "\n";

    return os; 

} 