#ifndef PROFILE_H
#define PROFILE_H
#include <vector>
#include "../comm/post.h"
#include "../comm/message.h"
#include "../comm_database/database.h"

using namespace std;

class Group;
#include "../groups/group.h"

class fish;
#include "fish.h"

class Engine;
#include "../engine/engine.h"

class profile
{
public:
    profile();
    profile(string username, string password, string nameFirst, string nameLast);
    ~profile();

    Database d;
    Engine* e;

    //  -------- Profile information --------  //

    //Profile owner's legal name
    string nameFirst, nameLast;

    //Profile owner's username/password
    string username, password;

    //Profile information General
    string bio;
    vector<Group*> adminList;   //list of groups this profile is an admin for
    int id;

    //Profile attributes -> expand this list
    string location, preference, age;

    //Friends list
    vector<profile*> friendsList;

    //Groups list
    vector<Group*> groupsList;

    //Post/Message History
    vector<Post*> postHistory;
    vector<Message*> messageHistory;    //store different chats with other profiles

    //Fish owned by profile
    vector<fish*> collection;

    //Settings
    bool access;    //private or public account

    //  -------- Methods --------  //

    void addFriend(profile* x);
    void removeFriend(profile* x);  //remove friend at profile
    void removeFriendForeign(profile* x);  //remove friend at foreign profile

    void changeBio(string x);
    void changeUsername(string x);
    void changePassword(string x);
    //change attributes here

    fish* createFish(string name, string species, string bio);
    void removeFish(fish* x);
    void changeFishBio(fish* x, string y);
    void changeFishLocation(fish* x, string y);

    void addAdminGroup(Group* g);

    void addMessage(Message* m);
    void addPost(Post* p);
    void addGroup(Group* g);

    void createGroup(string name); //not to be confused with addGroup

    // --- Getter Methods --- //

    string getNameFirst();
    string getNameLast();
    string getUsername();
    string getPassword();
    string getBio();
    string getLocation();
    string getPreference();
    string getAge();

};

#endif // PROFILE_H
