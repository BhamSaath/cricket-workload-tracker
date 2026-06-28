#pragma once
#include <string>

namespace Auth
{
    class Auth
    {
        public:
            std::string authenticateUser(std::string username, std::string password);
    };
};