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
        Player(const std::string& uname);

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
        void setPosition(std::string pos)
        {
            if(pos == "Fast Bowler")
            {
                position = PlayerType::FastBowler;
            }
            else if(pos == "Spinner")
            {
                position = PlayerType::Spinner;
            }
            else if(pos == "Batsman")
            {
                position = PlayerType::Batsman;
            }
            else if(pos == "Wicket Keeper")
            {
                position = PlayerType::WicketKeeper;
            }
            else if(pos == "Fast All Rounder")
            {
                position = PlayerType::FastAllRounder;
            }
            else if(pos == "Spin All Rounder")
            {
                position = PlayerType::SpinAllRounder;
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