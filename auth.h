#pragma once
#include <string>
#include "bcrypt.h"
#include "node_blf.h"
#include "openbsd.h"
namespace Auth
{
    class Auth
    {
        public:
            std::string authenticateUser(std::string username, std::string password);
    };
};