#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include "Player.h"
namespace Coach
{
    void Coach::getPlayerDetails(Player::Player p)
    {
        std::cout<< "Player Name: " << p.name << "Player Age: " << p.age << "\n" << "Player Role:"<< p.position<<std::endl;
    }
    void Coach::getSessions(Player::Player p)
    {
        p.viewSessions();
    }
    void Coach::getPlan(Player::Player p)
    {
        p.viewPlan();
    }
    void Coach::removePlayer(Player::Player p)
    {
        for(size_t i = 0; i < players.size(); i++)
        {
            if(players[i].name == p.name && players[i].age == p.age && players[i].position == p.position)
            {
                players.erase(players.begin() + i);
                break;
            }
        }
    }
    void Coach::addPlayer(Player::Player p)
    {
        players.push_back(p);
    }
    void Coach::managePlan(Player::Player p, Player::Plan newPlan)
    {
        p.plan = newPlan;
    }
};