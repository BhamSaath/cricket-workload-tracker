#include <iostream>
#include <string> 
#include <fstream>
#include "auth.h"
#include "Player.h"
#include "Coach.h"
#include <iomanip>
#include <sstream>
#include <sstream>
#include "bcrypt.h"
#include "node_blf.h"
#include "openbsd.h"

std::vector<std::string> createAccount()
{
    std::string username, password, role;
    std::cout << "Enter username: ";
    std::cin >> username;
    if(std::ofstream("credentials.txt", std::ios::app).tellp() != 0) // Check if the file is not empty
    {
        std::ifstream file("credentials.txt");
        std::string line;
        while (std::getline(file, line))
        {
            size_t pos = line.find(':');
            if (pos != std::string::npos)
            {
                std::string existingUsername = line.substr(0, pos);
                if (existingUsername == username)
                {
                    std::cout << "Username already exists. Please choose a different username." << std::endl;
                    while(true)
                    {
                        std::cout << "Enter username: ";
                        std::cin >> username;
                        file.clear(); // Clear the EOF flag
                        file.seekg(0); // Go back to the beginning of the file
                        bool exists = false;
                        while (std::getline(file, line))
                        {
                            size_t pos = line.find(':');
                            if (pos != std::string::npos)
                            {
                                std::string existingUsername = line.substr(0, pos);
                                if (existingUsername == username)
                                {
                                    exists = true;
                                    break;
                                }
                            }
                        }
                        if(!exists)
                        {
                            break; // Exit the loop if the username does not exist
                        }
                        else
                        {
                            std::cout << "Username already exists. Please choose a different username." << std::endl;
                        }
                    } // Recursively call createAccount to try again
                }
            }
        }
    }
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter role (admin/coach/player): ";
    std::cin >> role;

    // Store the credentials in a file
    std::ofstream file("credentials.txt", std::ios::app);
    if (file.is_open())
    {
                file << username << ":" << bcrypt::generateHash(password) << ":" << role << "\n";
        file.close();
        std::cout << "Account created successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
    return {role, username};
}
int playerDashboard(Player::Player& p)
{
    bool backToMainMenu = false;
    while(!backToMainMenu) {
    int actionChoice = 0; 
    std::cout << "Welcome to the Player Dashboard!" << std::endl;
    std::cout<< "What do you want to do?\n 1. View Sessions\n 2. Add Sessions\n 3. View Plan\n 4.Report Injury\n 5.View Injuries 6.See Profile" << std::endl;
    while (true) {
        std::cin >> actionChoice;
        if (std::cin.fail()) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Please enter an integer: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any remaining input
            break; // valid input, exit the loop
        }
    }

    if(actionChoice == 1)
    {
        p.viewSessions();
        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;
        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else if(actionChoice == 2)
    {
        Player::Session s;
        std::cout << "Enter session date (YYYY-MM-DD): ";
        std::cin >> s.date;
        std::cout << "Enter session duration (e.g., 2 hours): ";
        std::cin >> s.duration;
        int sessionTypeChoice;
        std::cout << "Enter session type (0: Training, 1: Match, 2: Recovery): ";
        while (true) {
            std::cin >> sessionTypeChoice;
            if (std::cin.fail() || sessionTypeChoice < 0 || sessionTypeChoice > 2) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid input. Please enter 0, 1, or 2: ";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any remaining input
                break; // valid input, exit the loop
            }
        }
        s.type = static_cast<Player::SessionType>(sessionTypeChoice);
        std::cout << "Enter session notes: ";
        std::getline(std::cin, s.notes);
        p.addSession(s);
        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;
        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else if(actionChoice == 3)
    {
        p.viewPlan();
        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;

        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else if(actionChoice == 4)
    {
        Player::Injury i;
        std::cout << "Enter injury type: ";
        std::cin >> i.type;
        int severityChoice;
        std::cout << "Enter injury severity (0: Mild, 1: Moderate, 2: Severe): ";
        while (true) {
            std::cin >> severityChoice;
            if (std::cin.fail() || severityChoice < 0 || severityChoice > 2) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid input. Please enter 0, 1, or 2: ";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any remaining input
                break; // valid input, exit the loop
            }
        }
        i.severity = static_cast<Player::SeverityLevel>(severityChoice);
        std::cout << "Enter expected recovery time (e.g., 2 weeks): ";  
        std::cin >> i.recoveryTime;
        std::cout << "Enter injury description: ";
        std::cin.ignore(); // Clear the newline character from the input buffer
        std::getline(std::cin, i.description);
        p.reportInjury(i);

        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;

        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else if(actionChoice == 5)
    {
        p.viewInjuries();
        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;
        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else if(actionChoice == 6)
    {
        std::cout<< "Player Name: " << p.getName() << "\n" << "Player Age: "<< p.getAge()<<"\n"<<"Player Position: "<< p.getPosition()<<std::endl;
        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;
        }   
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else
    {
        std::cout << "Invalid choice. Exiting." << std::endl;
        playerDashboard(p);
        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;
        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    }

    // Here you can add logic to show the player dashboard
    return 0;
}
int coachDashboard(Coach::Coach& c)
{
    bool backToMainMenu = false;
    while(!backToMainMenu) {
    std::cout << "Welcome to the Coach Dashboard!" << std::endl;
    // Here you can add logic to show the coach dashboard
    int choice;
    std::cout<< "What do you want to do?\n 1. View Player Details\n 2. View Player Sessions\n 3. View Player Plan\n 4. Mangage Player Plan 5. Remove Player" << std::endl;
    std::cin >> choice;
    if(choice == 1)
    {
        std::cout<< "Which Player do you want to view?";
        for(size_t i = 0; i < c.getPlayers().size(); i++)
        {
            std::cout << i+1 << ". " << c.getPlayers()[i].getName() << std::endl;
        }
        int playerChoice;
        while (true) {
            std::cin >> playerChoice;
            if (std::cin.fail() || playerChoice < 1 || playerChoice > c.getPlayers().size()) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid input. Please enter a valid player number: ";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any remaining input
                break; // valid input, exit the loop
            }
        }
        Player::Player selectedPlayer = c.getPlayers()[playerChoice - 1];
        c.getPlayerDetails(selectedPlayer);

        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;
        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else if(choice == 2)
    {
        if(c.getPlayers().empty())
        {
            std::cout << "No players available. Please add players first." << std::endl;
            backToMainMenu = false;
            break;
        }
        std::cout<< "Which Player's Sessions do you want to view?";
        for(size_t i = 0; i < c.getPlayers().size(); i++)
        {
            std::cout << i+1 << ". " << c.getPlayers()[i].getName() << std::endl;
        }
        int playerChoice;
        while (true) {
            std::cin >> playerChoice;
            if (std::cin.fail() || playerChoice < 1 || playerChoice > c.getPlayers().size()) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid input. Please enter a valid player number: ";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any remaining input
                break; // valid input, exit the loop
            }
        }
        Player::Player selectedPlayer = c.getPlayers()[playerChoice - 1];
        c.getSessions(selectedPlayer);
        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;
        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else if(choice == 3)
    {
        if(c.getPlayers().empty())
        {
            std::cout << "No players available. Please add players first." << std::endl;
            backToMainMenu = false;
            break;
        }
        std::cout<< "Which Player's Plan do you want to view?";
        for(size_t i = 0; i < c.getPlayers().size(); i++)
        {
            std::cout << i+1 << ". " << c.getPlayers()[i].getName() << std::endl;
        }
        int playerChoice;
        while (true) {
            std::cin >> playerChoice;
            if (std::cin.fail() || playerChoice < 1 || playerChoice > c.getPlayers().size()) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid input. Please enter a valid player number: ";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any remaining input
                break; // valid input, exit the loop
            }
        }
        Player::Player selectedPlayer = c.getPlayers()[playerChoice - 1];
        c.getPlan(selectedPlayer);
        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;

        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else if(choice == 4)
    {
        if(c.getPlayers().empty())
        {
            std::cout << "No players available. Please add players first." << std::endl;
            backToMainMenu = false;
            break;
        }
        std::cout<< "Which Player's Plan do you want to manage?";
        for(size_t i = 0; i < c.getPlayers().size(); i++)
        {
            std::cout << i+1 << ". " << c.getPlayers()[i].getName() << std::endl;
        }
        int playerChoice;
        while (true) {
            std::cin >> playerChoice;
            if (std::cin.fail() || playerChoice < 1 || playerChoice > c.getPlayers().size()) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid input. Please enter a valid player number: ";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any remaining input
                break; // valid input, exit the loop
            }
        }
        Player::Player selectedPlayer = c.getPlayers()[playerChoice - 1];
        Player::Plan newPlan;
        std::cout << "Enter new plan name: ";
        std::cin >> newPlan.name;
        std::cout << "Enter new plan description: ";
        std::cin >> newPlan.description;
        int numExercises;
        std::cout << "Enter number of exercises: ";
        std::cin >> numExercises;
        for(int i = 0; i < numExercises; i++)
        {
            std::string exercise;
            std::cout << "Enter exercise " << i+1 << ": ";
            std::cin >> exercise;
            newPlan.exercises.push_back(exercise);
        }
        int numDrills;
        std::cout << "Enter number of drills: ";
        std::cin >> numDrills;
        for(int i = 0; i < numDrills; i++)
        {
            std::string drill;
            std::cout << "Enter drill " << i+1 << ": ";
            std::cin >> drill;
            newPlan.drills.push_back(drill);
        }
        int numMatches;
        std::cout << "Enter number of matches: ";
        std::cin >> numMatches;
        for(int i = 0; i < numMatches; i++)
        {
            std::string match;
            std::cout << "Enter match " << i+1 << ": ";
            std::cin >> match;
            newPlan.matches.push_back(match);
        }
        c.managePlan(selectedPlayer, newPlan);
        selectedPlayer.saveToJson(); // Save the updated player data to JSON after managing the plan
        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;

        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }

    }
    else if(choice == 5)
    {
        if(c.getPlayers().empty())
        {
            std::cout << "No players available. Please add players first." << std::endl;
            backToMainMenu = false;
            break;
        }
        std::cout<< "Which Player do you want to remove?";
        for(size_t i = 0; i < c.getPlayers().size(); i++)
        {
            std::cout << i+1 << ". " << c.getPlayers()[i].getName() << std::endl;
        }
        int playerChoice;
        while (true) {
            std::cin >> playerChoice;
            if (std::cin.fail() || playerChoice < 1 || playerChoice > c.getPlayers().size()) {
                std::cin.clear(); // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                std::cout << "Invalid input. Please enter a valid player number: ";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any remaining input
                break; // valid input, exit the loop
            }
        }
        Player::Player selectedPlayer = c.getPlayers()[playerChoice - 1];
        c.removePlayer(selectedPlayer);

        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;

        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else if(choice == 6)
    {
        c.addPlayers();
        int exitChoice;
        std::cout<< "Do you to continue or exit?\n 1. Continue\n 2. Exit" << std::endl;
        std::cin >> exitChoice;
        if(exitChoice == 1)
        {
            backToMainMenu = false;

        }
        else if(exitChoice == 2)
        {
            std::cout<< "Exiting..." << std::endl;
            return 0;
        }
    }
    else
    {
        std::cout << "Invalid choice. Exiting." << std::endl;
        return 0;
    }
    }
    backToMainMenu = false; // Reset the flag for the next iteration
    return 0;
}
int main() 
{
    bool exitProgram = false;
    while(!exitProgram)
    {
    int choice;
    std::cout << "Hello, Cricket Workload Tracker!" << std::endl;
    std::cout << "1. Create Account\n2. Login\n" << std::endl;
    std::cin >> choice;

    if(choice == 1)
    {
        std::vector<std::string> accountDetails = createAccount();
        std::string role = accountDetails[0];
        std::string username = accountDetails[1];
        if(role == "player" )
            {
                std::cin.ignore();
                std::string name;
                std::cout << "What is your name?" << std::endl;
                std::getline(std::cin,name);
                while(true)
                {
                    if(name.empty())
                    {
                        std::cout << "Name cannot be empty. Please enter your name: ";
                        std::getline(std::cin,name);
                    }
                    else
                    {
                        break;
                    }
                }

                int age;
                std::cout << "What is your age?" << std::endl;
                std::cin >> age;
                while(true)
                {
                    if(std::cin.fail() || age <= 0)
                    {
                        std::cin.clear(); // clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                        std::cout << "Invalid input. Please enter a valid age: ";
                        std::cin >> age;
                    }
                    else
                    {
                        break; // valid input, exit the loop
                    }
                }

                std::string position;
                std::cout << "What is your position? (FastBowler, Spinner, Batsman, WicketKeeper, FastAllRounder, SpinAllRounder)" << std::endl;
                std::cin >> position;
                while(true)
                {
                    if(position != "FastBowler" && position != "Spinner" && position != "Batsman" && position != "WicketKeeper" && position != "FastAllRounder" && position != "SpinAllRounder")
                    {
                        std::cout << "Invalid position. Please enter a valid position: ";
                        std::cin >> position;
                    }
                    else
                    {
                        break; // valid input, exit the loop
                    }
                }

                Player::PlayerType playerPosition;
                if(position == "FastBowler")
                {
                    playerPosition = Player::PlayerType::FastBowler;
                }
                else if(position == "Spinner")
                {
                    playerPosition = Player::PlayerType::Spinner;
                }
                else if(position == "Batsman")
                {
                    playerPosition = Player::PlayerType::Batsman;
                }
                else if(position == "WicketKeeper")
                {
                    playerPosition = Player::PlayerType::WicketKeeper;
                }
                else if(position == "FastAllRounder")
                {
                    playerPosition = Player::PlayerType::FastAllRounder;
                }
                else if(position == "SpinAllRounder")
                {
                    playerPosition = Player::PlayerType::SpinAllRounder;
                }
                else
                {
                    std::cout << "Invalid position. Exiting." << std::endl;
                    return 0;
                }
                Player::Player p =  Player::Player(username, username + "@example.com", role, name, age, playerPosition);
                p.saveToJson();

                return playerDashboard(p);
                // Here you can add logic to show the player dashboard
            }
        else if(role == "coach")
            {
                std::cin.ignore();
                std::string name;
                std::cout << "What is your name?" << std::endl;
                std::getline(std::cin,name);

                std::string coachID = "C" + std::to_string(rand() % 10000); // Generate a random coach ID

                Coach::Coach c = Coach::Coach(username, username + "@example.com", role, name, coachID);
                c.saveToJson();
                
                return coachDashboard(c);
                

                // Here you can add logic to show the coach dashboard
            }
            else
            {
                std::cout << "Invalid role. Exiting." << std::endl;
                return 0;
            }
    }
    else if(choice == 2)
    {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        Auth::Auth auth;
        std::string role = auth.authenticateUser(username, password);
        if(role == "Invalid Username or Password")
        {
            std::cout << role << std::endl;
        }
        else
        {
            std::cout << "Login successful! Role: " << role << std::endl;

            if(role == "player" )
            {
                std::cout << "Directing to Player Dashboard..." << std::endl;
                Player::Player p = Player::Player(username);
                return playerDashboard(p);
                // Here you can add logic to show the player dashboard
            }
            else if(role == "coach" )
            {
                std::cout << "Directing to Coach Dashboard..." << std::endl;
                Coach::Coach c = Coach::Coach(username);
                return coachDashboard(c);
                // Here you can add logic to show the coach dashboard
            }
            else
            {
                std::cout << "Unknown role. Exiting." << std::endl;
            }
            
        }
    }
    else
    {
        std::cout << "Invalid choice. Exiting." << std::endl;
        exitProgram = true;
    }
    }
    return 0;
}
