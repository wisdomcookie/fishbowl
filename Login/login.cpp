#include "login.h"

login::login() {
}
login::~login() {
}

bool login::performLogin(string username, string password) {
    bool var = false;
    d.query_exec("select * from profiles:");
    vector<vector<QString>> star;
    star = d.query_vector();

    for (unsigned long i=0; i<star.size(); i++) {
        for (unsigned long j=0; j<star.at(i).size(); j++) {
            string match = star.at(i).at(j).toStdString();
            if (match == username) {
                // if (password is correct) { ...
            }
        }
    }
    return var;
}





















