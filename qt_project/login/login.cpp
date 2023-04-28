#include "login.h"

Login::Login() {
}
Login::~Login() {
    delete e;
}

bool Login::performLogin(QString username, QString password) {
    bool var = false;
    e = new Engine();
    if (e->login(username, password)){
        var = true;
    }
    return var;
}





















