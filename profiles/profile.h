#ifndef PROFILE_H
#define PROFILE_H
#include <vector>
#include "../comm/post.h"
#include "../comm/message.h"

using namespace std;

class Group;
#include "../groups/group.h"

class fish;
#include "fish.h"

class Profile
{
public:
    profile();
    profile(string username, string password);
    ~profile();

    //  -------- Profile information --------  //

    //Profile owner's legal name
    string nameFirst, nameLast;

    //Profile owner's username/password
    string username, password;

    //Profile information General
    string bio;
    int id, admin;  //admin int = the id of the group for which the profile is an admin


    //Profile attributes -> expand this list
    string location, preference, age;

    //Friends list
    vector<profile*> friendsList;
    vector<profile*> pendingFriendsList;

    //Groups list
    vector<Group*> groupsList;

    //Post/Message History
    vector<Post*> postHistory;
    vector<Message*> messageHistory;

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

    void createFish(string name, string species);
    void removeFish(fish* x);
    void changeFishBio(fish* x, string y);
    void changeFishLocation(fish* x, string y);
};

#endif // PROFILE_H
