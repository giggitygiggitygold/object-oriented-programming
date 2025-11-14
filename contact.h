#pragma once

#include <vector>
#include <string>
#include <sstream>

class Contact{
    private:
        std::string name;
        std::string surname;
        std::string middlename;
        std::string address;
        std::string dateofbirth;
        std::string email;
        std::vector<std::string> phonenumber;
    
    public:
        Contact();
        Contact(const std::string& first, const std::string& last, const std::string& middle, const std::string& adr, const std::string& mail, const std::vector<std::string>& phones, const std::string& birthdate);

        std::string getfirstname() const;
        std::string getsurname() const;
        std::string getmiddlename() const;
        std::string getaddress() const;
        std::string getdateofbirth() const;
        std::string getemail() const;
        std::vector<std::string> getphonenumber() const;

        void setfirstname(const std::string& s);
        void setsurname(const std::string& s);
        void setmiddlename(const std::string& s);
        void setaddress(const std::string& s);
        void setdateofbirth(const std::string& s);
        void setemail(const std::string& s);
        void setphonenumber(const std::vector<std::string>& p);
        
        std::string tostring() const;
        static Contact fromstring(const std::string& line);

        friend std::ostream& operator<<(std::ostream& os, const Contact& c);
};