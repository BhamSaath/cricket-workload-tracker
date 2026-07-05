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
        std::string getName() const { return name; }
        std::string getCoachID() const { return coachID; }
        std::vector<Player::Player> getPlayers() const { return players; }
        void setName(std::string n) { name = n; }
        void setCoachID(std::string id) { coachID = id; }
        void setPlayers(std::vector<Player::Player> p) { players = p; }
        void saveToJson();
        void readFromJson();
        void addPlayers();
        Coach(std::string uname, std::string mail, std::string r, std::string n, std::string id)
            : User(uname, mail, r), name(n), coachID(id) {}
        Coach(const std::string& uname) : User(uname)
        {
            setUsername(uname);
            readFromJson(); // Load coach data from JSON when creating a Coach object with just the username
        };
        void getPlayerDetails(const Player::Player& p);
        void getSessions(const Player::Player& p);
        void getPlan(const Player::Player& p);
        void removePlayer(const Player::Player& p); 
        
        void addPlayer(const Player::Player& p);
        void managePlan(Player::Player& p, Player::Plan newPlan); 
        private:
        std::string name;
        std::vector<Player::Player> players;
        std::string coachID;

    };

};