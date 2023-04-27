#include "login.h"

login::login() {
}
login::~login() {
    delete e;
}

bool login::performLogin(string username, string password) {
    bool var = false;
    e = new Engine();
    if (e->login(QString::fromStdString(username), QString::fromStdString(password))) {
        var = true;
    }
    return var;
}





















