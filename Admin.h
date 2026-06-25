#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include "Coach.h"

namespace Admin
{
    class Admin
    {
         public:
            
            void onboardCoach(Coach::Coach c);
            void removeCoach(Coach::Coach c);
            void manageAPIKeys();
            void manageAPIKeys(); 
            void triggerDatabaseBackup(); 
    };
};