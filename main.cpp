#include <iostream>
#include <string> 
#include <fstream>
#include "auth.h"
void createAccount()
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
}
int main() {
    int choice;
    std::cout << "Hello, Cricket Workload Tracker!" << std::endl;
    std::cout << "1. Create Account\n2. Login\n" << std::endl;
    std::cin >> choice;
    if(choice == 1)
    {
        createAccount();
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
            // Here you can add logic to redirect the user based on their role
            // For example, if role is "admin", show admin dashboard, etc.
        }
    }
    else
    {
        std::cout << "Invalid choice. Exiting." << std::endl;
    }
    return 0;
}