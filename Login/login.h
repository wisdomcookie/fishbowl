#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include "../comm_database/database.h"

using namespace std;

class login
{
public:
    login();
    ~login();

    bool performLogin(string username, string password);

    Database d;
};

#endif // LOGIN_H
