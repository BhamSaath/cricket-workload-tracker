
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include "User.h"
#include "Player.h"
#include <iostream>
namespace Player
{
    
    void Player::addSession(Session s)
    {
        sessions.push_back(s);

    }
    std::string Player::viewSessions()
    {
        for(size_t i = 0; i < sessions.size(); i++)
        {
            std::cout << "Session " << i+1 << ": " << sessions[i].date << ", " << sessions[i].duration << ", " << static_cast<int>(sessions[i].type) << ", " << sessions[i].notes << std::endl;
        }
    }
    std::string Player::viewPlan()
    {
        std::cout<< trainingPlan.name<< ": " << trainingPlan.description<< "\n"<< std::endl;
        for(size_t i = 0; i < trainingPlan.drills.size(); i++)
        {
            std::cout << "Drill " << i+1 << ": " << trainingPlan.drills[i] << "\n" <<std::endl;
            std::cout << "Exercises " << i+1 << ": " << trainingPlan.exercises[i] << "\n" <<std::endl;
            std::cout << "Mathches " << i+1 << ": " << trainingPlan.matches[i] << "\n" <<std::endl;
        }
    }
    void Player::reportInjury(Injury i)
    {
        injuries.push_back(i);
    }
};