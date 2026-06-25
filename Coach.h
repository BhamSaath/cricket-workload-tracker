#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include "Player.h" // Include the header file where Player is defined
namespace Coach
{

    class Coach
    {   
        
        public:
        std::string name;
        std::vector<Player::Player> players;

        void getPlayerDetails(Player::Player p);
        void getSessions(Player::Player p);
        void getPlan(Player::Player p);
        void removePlayer(Player::Player p);
        void addPlayer(Player::Player p);
        void managePlan(Player::Player P); 

    };

};