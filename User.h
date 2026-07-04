#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include "json.hpp"
namespace User
{
    using json = nlohmann::json;
    class User
    {
        public:
            
            User(std::string uname, std::string mail, std::string r, json data = {})
                : username(uname), email(mail), role(r) {}
            User()
                : username(""), email(""), role(""), profileData("") {}
            User(std::string uname)
                : username(uname), email(""), role(""), profileData("") {}
            std::string getUsername() const { return username; }
            std::string getEmail() const { return email; }
            std::string getRole() const { return role; }
            void setUsername(std::string uname) { username = uname; }
            void setEmail(std::string mail) { email = mail; }
            void setRole(std::string r) { role = r; }
            void logout();
        private:
            std::string username;
            std::string email;
            std::string role; // e.g., "admin", "coach", "player"
            json profileData; // Store additional profile data in JSON format

    };
};