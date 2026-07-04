
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include "User.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include "json.hpp" // Include the JSON library header
 // Define 'json' as an alias for 'nlohmann::json'
namespace Player
{
    
    using json = nlohmann::json;
    Player::Player(const std::string& uname) : User(uname)
    {
        readFromJson(); // Automatically load data from JSON when the object is created
    }
    void Player::saveToJson()
    {
        json j;
        j["username"] = getUsername();
        j["email"] = getEmail();
        j["role"] = getRole();
        j["name"] = name;
        j["age"] = age;
        j["position"] = static_cast<int>(position);
        
        // Save sessions
        for (const auto& session : sessions) {
            json sessionJson;
            sessionJson["date"] = session.date;
            sessionJson["duration"] = session.duration;
            sessionJson["type"] = static_cast<int>(session.type);
            sessionJson["notes"] = session.notes;
            j["sessions"].push_back(sessionJson);
        }

        // Save injuries
        for (const auto& injury : injuries) {
            json injuryJson;
            injuryJson["type"] = injury.type;
            injuryJson["severity"] = static_cast<int>(injury.severity);
            injuryJson["recoveryTime"] = injury.recoveryTime;
            injuryJson["description"] = injury.description;
            j["injuries"].push_back(injuryJson);
        }

        // Save training plan
        j["trainingPlan"]["plan name"] = trainingPlan.name;
        j["trainingPlan"]["description"] = trainingPlan.description;
        j["trainingPlan"]["exercises"] = trainingPlan.exercises;
        j["trainingPlan"]["drills"] = trainingPlan.drills;
        j["trainingPlan"]["matches"] = trainingPlan.matches;

        std::ofstream file(getUsername() + "_data.json");
        if (file.is_open()) {
            file << j.dump(4); // Pretty print with 4 spaces indentation
            file.close();
            std::cout << "Player data saved to " << getUsername() + "_data.json" << std::endl;
        } else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    }
    void Player::readFromJson()
    {
        std::ifstream file(getUsername() + "_data.json");
        if (file.is_open()) {
            json j;
            file >> j;
            file.close();

            // Load basic player info
            setUsername(j["username"]);
            setEmail(j["email"]);
            setRole(j["role"]);
            age = j["age"];
            name = j["name"];
            position = static_cast<PlayerType>(j["position"].get<int>());

            // Load sessions
            sessions.clear();
            for (const auto& sessionJson : j["sessions"]) {
                Session s;
                s.date = sessionJson["date"];
                s.duration = sessionJson["duration"];
                s.type = static_cast<SessionType>(sessionJson["type"].get<int>());
                s.notes = sessionJson["notes"];
                sessions.push_back(s);
            }

            // Load injuries
            injuries.clear();
            for (const auto& injuryJson : j["injuries"]) {
                Injury i;
                i.type = injuryJson["type"];
                i.severity = static_cast<SeverityLevel>(injuryJson["severity"].get<int>());
                i.recoveryTime = injuryJson["recoveryTime"];
                i.description = injuryJson["description"];
                injuries.push_back(i);
            }

            // Load training plan
            trainingPlan.name = j["trainingPlan"]["plan name"];
            trainingPlan.description = j["trainingPlan"]["description"];
            trainingPlan.exercises = j["trainingPlan"]["exercises"].get<std::vector<std::string>>();
            trainingPlan.drills = j["trainingPlan"]["drills"].get<std::vector<std::string>>();
            trainingPlan.matches = j["trainingPlan"]["matches"].get<std::vector<std::string>>();

            std::cout << "Player data loaded from " << getUsername() + "_data.json" << std::endl;
        } else {
            std::cerr << "Unable to open file for reading." << std::endl;
        }
    }
    void Player::addSession(Session s)
    {
        sessions.push_back(s);
        saveToJson(); // Save the updated player data to JSON after adding a session

    }
    void Player::viewSessions()
    {
        for(size_t i = 0; i < sessions.size(); i++)
        {
            std::cout << "Session " << i+1 << ": " << sessions[i].date << ", " << sessions[i].duration << ", " << static_cast<int>(sessions[i].type) << ", " << sessions[i].notes << std::endl;
        }
    }
    
    void Player::viewPlan()
    {
        std::cout<< trainingPlan.name<< ": " << trainingPlan.description<< "\n"<< std::endl;
        for(size_t i = 0; i < trainingPlan.drills.size(); i++)
        {
            std::cout << "Drill " << i+1 << ": " << trainingPlan.drills[i] << "\n" <<std::endl;
            
        }
        for(size_t i = 0; i < trainingPlan.exercises.size(); i++)
        {
            std::cout << "Exercise " << i+1 << ": " << trainingPlan.exercises[i] << "\n" <<std::endl;
            
        }
        for(size_t i = 0; i < trainingPlan.matches.size(); i++)
        {
            std::cout << "Match " << i+1 << ": " << trainingPlan.matches[i] << "\n" <<std::endl;
            
        }
    }
    void Player::viewInjuries()
    {
        for(size_t i = 0; i < injuries.size(); i++)
        {
            std::cout << "Injury " << i+1 << ": " << injuries[i].type << ", Severity: " << static_cast<int>(injuries[i].severity) << ", Recovery Time: " << injuries[i].recoveryTime << ", Description: " << injuries[i].description <<"\n"<< std::endl;
        }
    }
    void Player::reportInjury(Injury i)
    {
        injuries.push_back(i);
        saveToJson(); // Save the updated player data to JSON after reporting an injury
    }
};