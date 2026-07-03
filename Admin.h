#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include "Coach.h"
#include "User.h"

namespace Admin
{
    class Admin: public User::User
    {
         public:
            std::vector<Coach::Coach> coaches;
            Admin(std::string uname, std::string mail, std::string r)
                : User(uname, mail, r) {}
            void onboardCoach(Coach::Coach c);
            void removeCoach(Coach::Coach c);
            void manageAPIKeys(); 
            void triggerDatabaseBackup(); 
    };
};