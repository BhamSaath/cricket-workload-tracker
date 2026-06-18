#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
namespace Coach
{

    class Coach
    {   
        
        public:
        std::string name;
        std::vector<Player> players;

        void getPlayerDetails(Player p);
        void getSessions(Player p);
        void getPlan(Player p);
        void removePlayer(Player p);
        void addPlayer(Player p);
        void managePlan(Player P); 

    }

}