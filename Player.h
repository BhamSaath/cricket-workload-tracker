#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include "User.h"
#include "json.hpp"
namespace Player 
{
    enum class SeverityLevel
    {
        Mild,
        Moderate,
        Severe
    };
    enum class SessionType
    {
        Training,
        Match,
        Recovery
    };
    enum class PlayerType
    {
        FastBowler,
        Spinner,
        Batsman,
        WicketKeeper,
        FastAllRounder,
        SpinAllRounder
    };
    class Plan
    {
        public:
        std::string name;
        std::string description;
        std::vector<std::string> exercises;
        std::vector<std::string> drills;
        std::vector<std::string> matches;

    };
    class Injury
    {
        public:
        std::string type;
        SeverityLevel severity;
        std::string recoveryTime;
        std::string description;

        void viewPlan();
        void updateInjuryStatus(std::string newStatus);
    };
    class Session
    {
        public:
        std::string date;
        std::string duration;
        SessionType type;
        std::string notes;
        

        void getSessionDetails();
        void updateSessionNotes(std::string newNotes);
    };
    class Player: public User::User
    {
        public:
        
        Player(std::string uname, std::string mail, std::string r, std::string n, int a, PlayerType pos)
            : User(uname, mail, r), name(n), age(a), position(pos) {}
        Player(const std::string& uname) : User(uname)
        {
            setUsername(uname);
            readFromJson(); // Load player data from JSON when creating a Player object with just the username
        };

        void addSession(Session s);
        std::string getName() const { return name; }
        std::string getPosition() const { 
            switch(position) {
                case PlayerType::FastBowler: return "Fast Bowler";
                case PlayerType::Spinner: return "Spinner";
                case PlayerType::Batsman: return "Batsman";
                case PlayerType::WicketKeeper: return "Wicket Keeper";
                case PlayerType::FastAllRounder: return "Fast All Rounder";
                case PlayerType::SpinAllRounder: return "Spin All Rounder";
                default: return "Unknown Position";
            }
        }
        void setAge(int a) { age = a; }
        void setName(std::string n) { name = n; }
        void setPosition(int pos)
        {
            switch(pos) {
                case 0: position = PlayerType::FastBowler; break;
                case 1: position = PlayerType::Spinner; break;
                case 2: position = PlayerType::Batsman; break;
                case 3: position = PlayerType::WicketKeeper; break;
                case 4: position = PlayerType::FastAllRounder; break;
                case 5: position = PlayerType::SpinAllRounder; break;
                default: std::cerr << "Invalid position value. Position not set." << std::endl; break;
            }
        }
        int getAge() const { return age; }
        void setTrainingPlan(Plan p) { trainingPlan = p; }
        void viewSessions(); 
        void saveToJson();
        void readFromJson();
        void viewPlan();
        void reportInjury(Injury i);
        void viewInjuries();

        private:
        std::string name;
        int age;
        PlayerType position;
        std::vector<Session> sessions;
        std::vector<Injury> injuries;
        Plan trainingPlan;
    };
    
};