#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
namespace User
{
    
    class User
    {
        public:
            std::string username;
            std::string passwordHash;
            std::string email;
            std::string role; // e.g., "admin", "coach", "player"
            

            User(std::string uname, std::string pwd, std::string mail, std::string r)
                : username(uname), passwordHash(pwd), email(mail), role(r) {}
            virtual void displayProfile() = 0; // Pure virtual function
            void login();
            void logout();
            void updateProfile(std::string newEmail, std::string newPassword);
    };
};