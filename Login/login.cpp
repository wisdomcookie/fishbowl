#include "login.h"

login::login() {
}
login::~login() {
    delete e;
}

Profile* login::performLogin(string username, string password) {
    e = new Engine();
    if (e->login(QString::fromStdString(username), QString::fromStdString(password))) {

    }

}





















