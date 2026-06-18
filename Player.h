#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
namespace Player 
{
    class Player
    {
        public:
        std::string name;
        int age;
        std::string position;
        std::vector<Session> sessions;
        std::vector<Injury> injuries;
        
        
        void addSession(Session s);
        std::string viewSessions(); 
        std::string viewPlan();
        void reportInjury(Injury i);
    }

}