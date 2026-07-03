#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include "Player.h" // Include the header file where Player is defined
#include "User.h"

namespace Coach
{

    class Coach: public User::User
    {   
        
        public:
        std::string name;
        std::vector<Player::Player> players;
        std::string coachID;
        Coach(std::string uname, std::string mail, std::string r, std::string n, std::string id)
            : User(uname, mail, r), name(n), coachID(id) {}
        void getPlayerDetails(Player::Player p);
        void getSessions(Player::Player p);
        void getPlan(Player::Player p);
        void removePlayer(Player::Player p);
        void addPlayer(Player::Player p);
        void managePlan(Player::Player P); 

    };

};