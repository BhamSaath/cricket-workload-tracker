#include <iostream>
#include <string> 
#include <fstream>
#include "auth.h"
#include "Player.h"
#include "Coach.h"


std::vector<std::string> createAccount()
{
    std::string username, password, role;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter role (admin/coach/player): ";
    std::cin >> role;

    // Store the credentials in a file
    std::ofstream file("credentials.txt", std::ios::app);
    if (file.is_open())
    {
        file << username << ":" << password << ":" << role << "\n";
        file.close();
        std::cout << "Account created successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
    return {role, username};
}
int playerDashboard()
{
    int actionChoice = 0; 
    std::cout << "Welcome to the Player Dashboard!" << std::endl;
    std::cout<< "What do you want to do?\n 1. View Sessions\n 2. Add Sessions\n 3. View Plan\n 4.Report Injury\n " << std::endl;
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
        
    }
    else if(actionChoice == 2)
    {
        
    }
    else if(actionChoice == 3)
    {

    }
    else if(actionChoice == 4)
    {

    }
    else
    {
        std::cout << "Invalid choice. Exiting." << std::endl;
        playerDashboard();
    }
    // Here you can add logic to show the player dashboard
    return 0;
}
int coachDashboard()
{
    std::cout << "Welcome to the Coach Dashboard!" << std::endl;
    // Here you can add logic to show the coach dashboard
    return 0;
}
int adminDashboard()
{
    std::cout << "Welcome to the Admin Dashboard!" << std::endl;
    // Here you can add logic to show the admin dashboard
    return 0;
}
int main() {
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
                std::string name;
                std::cout << "What is your name?" << std::endl;
                std::cin >> name;

                int age;
                std::cout << "What is your age?" << std::endl;
                std::cin >> age;

                std::string position;
                std::cout << "What is your position? (FastBowler, Spinner, Batsman, WicketKeeper, FastAllRounder, SpinAllRounder)" << std::endl;
                std::cin >> position;

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

                playerDashboard();
                // Here you can add logic to show the player dashboard
            }
        else if(role == "coach")
            {
                std::string name;
                std::cout << "What is your name?" << std::endl;
                std::cin >> name;

                std::string coachID = "C" + std::to_string(rand() % 10000); // Generate a random coach ID

                Coach::Coach c = Coach::Coach(username, username + "@example.com", role, name, coachID);
                c.saveToJson();
                
                coachDashboard();
                

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
                playerDashboard();
                // Here you can add logic to show the player dashboard
            }
            else if(role == "coach" )
            {
                std::cout << "Directing to Coach Dashboard..." << std::endl;
                coachDashboard();
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
        main();
    }
    return 0;
}