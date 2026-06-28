#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
#include "User.h"
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
        std::string name;
        int age;
        PlayerType position;
        std::vector<Session> sessions;
        std::vector<Injury> injuries;
        Plan trainingPlan;
        
        
        void addSession(Session s);
        std::string viewSessions(); 
        std::string viewPlan();
        void reportInjury(Injury i);
    };
    
};