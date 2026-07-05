#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Coach.h"
#include "User.h"
#include "json.hpp"
namespace Coach
{
    using json = nlohmann::json;
    void Coach::saveToJson()
    {
        
        json j;
        j["username"] = getUsername();
        j["email"] = getEmail();
        j["role"] = getRole();
        j["name"] = name;
        j["coachID"] = coachID;

        // Save players
        json playersJson = json::array();
        for (const auto& player : players) {
            json playerJson;
            playerJson["username"] = player.getUsername();
            playerJson["email"] = player.getEmail();
            playerJson["role"] = player.getRole();
            playerJson["name"] = player.getName();
            playerJson["age"] = player.getAge();
            playerJson["position"] = player.getPosition();
            playersJson.push_back(playerJson);
        }
        j["players"] = playersJson;
        std::ofstream file(getUsername() + "_coach_data.json");
        if (file.is_open()) {
            file << j.dump(4); // Pretty print with 4 spaces indentation
            file.close();
            std::cout << "Coach data saved to " << getUsername() + "_coach_data.json" << std::endl;
        } else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }


    }
    void  Coach::addPlayer(const Player::Player& p)
    {
        players.push_back(p);
        saveToJson(); // Save the updated coach data to JSON after adding a player
    }
    void Coach::readFromJson()
    {
        std::ifstream file(getUsername() + "_coach_data.json");
        if (file.is_open()) {
            json j;
            file >> j;
            file.close();

            // Load basic coach info
            setUsername(j["username"]);
            setEmail(j["email"]);
            setRole(j["role"]);
            name = j["name"];
            coachID = j["coachID"];

            // Load players
            players.clear();
            for (const auto& playerJson : j["players"]) {
                Player::Player p(playerJson["username"]);
                p.setEmail(playerJson["email"]);
                p.setRole(playerJson["role"]);
                p.setName(playerJson["name"]);
                p.setAge(playerJson["age"]);
                p.setPosition(playerJson["position"]);
                players.push_back(p);
            }
            std::cout << "Coach data loaded from " << getUsername() + "_coach_data.json" << std::endl;
        } else {
            std::cerr << "Unable to open file for reading." << std::endl;
        }
    }
    void Coach::getPlayerDetails( Player::Player p)
    {
        std::cout<< "Player Name: " << p.getName() << "Player Age: " << p.getAge() << "\n" << "Player Role:"<< p.getPosition()<<std::endl;
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
            if(players[i].getUsername() == p.getUsername() &&players[i].getName() == p.getName() && players[i].getAge() == p.getAge() && players[i].getPosition() == p.getPosition())
            {
                players.erase(players.begin() + i);
                saveToJson(); // Save the updated coach data to JSON after removing a player
                break;
            }
        }
    }
    void Coach::addPlayers()
    {
        
        std::ifstream file("credentials.txt");
        std::string line;
        std::string username;
        std::cout << "Enter username for player " << ": ";
        std::cin >> username;
        
        while(std::getline(file, line)) {
            std::stringstream ss(line);
            std::string storedUser, storedPass, storedRole;

            std::getline(ss, storedUser, ':');
            std::getline(ss, storedPass, ':');
            std::getline(ss, storedRole, ':');
                if (existingUsername == username)
                {
                    if(storedRole == "player")
                    {
                        Player::Player p(username);
                        addPlayer(p);
                        std::cout << "Player " << username << " added successfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "Username " << username << " is not a player. Please enter a valid player username." << std::endl;
                        // Decrement i to retry this iteration
                    }
                }
            }
        }
        
    }
    void Coach::managePlan(Player::Player& p, Player::Plan newPlan)
    {
        p.setTrainingPlan(newPlan);
        p.saveToJson(); // Save the updated player data to JSON after managing the plan
    }
};
