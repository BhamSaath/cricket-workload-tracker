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
            std::string username;
            std::string email;
            std::string role; // e.g., "admin", "coach", "player"
            json profileData; // Store additional profile data in JSON format
            User(std::string uname, std::string mail, std::string r, json data = {})
                : username(uname), email(mail), role(r) {}
            void logout();
            void updateProfile(std::string newEmail);
            
    };
};