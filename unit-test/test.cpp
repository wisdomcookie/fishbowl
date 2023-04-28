#include "test.h"

using namespace std;

test::test() {
}

void test::run() {
    Database* d = new Database();
    Engine* e = new Engine();
    d->open();

    QString cmd[] = {"profiles", "groups", "posts", "friends", "group_participants", "banned_users",
                     "login", "messages", "post_comments", "fish", "admins", "reports"};

    //COMM_DATABASE
    cout << "----------------------------------" << endl;
    cout << "TEST get_next_id(QString table)" << endl;
    for (int i=0; i<12; i++) {
        int x = d->get_next_id(cmd[i]);
        if (x != 0) {
            cout << cmd[i].toStdString() + " test passed!" << endl;
        } else {
            cout << cmd[i].toStdString() + " test failed!" << endl;
        }
    }


    //ENGINE
    cout << "----------------------------------" << endl;
    cout << "TEST load_data()" << endl;
    vector<Profile*> profList;
    vector<Group*> grpList;
    vector<Post*> postList;
    e->load_data();
    for (int i=0; i<3; i++) {
        if ((int)e->get_profileList().size() == d->get_next_id(cmd[i]) - 1) {
            cout << cmd[i].toStdString() + "List Test Passed!" << endl;
        } else {
            cout << "Test Failed: " + cmd[i].toStdString() + "List not being populated with "
                                                             "database entries!" << endl;
        }
    }
}
