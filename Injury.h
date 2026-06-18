#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 

namespace Injury
{
    enum class SeverityLevel
    {
        Mild,
        Moderate,
        Severe
    };
    class Injury
    {
        public:
        std::string type;
        SeverityLevel severity;
        std::string recoveryTime;
        std::string description;

        void getInjuryDetails();
        void updateInjuryStatus(std::string newStatus);
    };
}ss