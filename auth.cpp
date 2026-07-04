#include <string>
#include <fstream>
#include <sstream>
#include "auth.h"

namespace Auth
{
    
    std::string Auth::authenticateUser(std::string username, std::string password)
    {
        std::ifstream file("credentials.txt");
        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string storedUser, storedPass, storedRole;
            std::string storedUsername, storedPassword;

            std::getline(ss, storedUser, ':');
            std::getline(ss, storedPass, ':');
            std::getline(ss, storedRole, ':');
            
            if(storedUser == username && storedPass == password)
            {
                return storedRole; // Return the role if authentication is successful
            }
        }
        return "Invalid Username or Password"; // Return an error message if authentication fails
    }
}
