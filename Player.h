#pragma once
#include <string> 
#include <cmath> 
#include <vector> 
#include <array> 
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
    class Injury
    {
        public:
        std::string type;
        SeverityLevel severity;
        std::string recoveryTime;
        std::string description;

        void getInjuryDetails();
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
    class Player
    {
        public:
        std::string name;
        int age;
        std::string position;
        std::vector<Session> sessions;
        std::vector<Injury> injuries;
        
        
        void addSession(Session s);
        std::string viewSessions(); 
        std::string viewPlan();
        void reportInjury(Injury i);
    };
    
};