#ifndef LOGIN_H
#define LOGIN_H
#include "../engine/engine.h"

using namespace std;

class Login
{
public:
    Login();
    ~Login();


    bool performLogin(QString username, QString password);

private:

    Engine* e;
};

#endif // LOGIN_H
