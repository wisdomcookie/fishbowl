#ifndef PROFILE_H
#define PROFILE_H
#include <vector>

#include "../comm/post.h"
#include "../comm/message.h"
#include "../comm_database/database.h"

using namespace std;

//class Group;
#include "../groups/group.h"

//class Fish;
#include "fish.h"

class Profile
{
public:
    Profile();
    Profile(string username, string password);
    Profile(std::map<QString, QString> profileData); // load from database
    ~Profile();

    //  -------- Profile information --------  //

    //Profile owner's legal name
    string nameFirst, nameLast;

    //Profile owner's username/password
    //string username, password;

    //Profile information General
    string bio;
    vector<Group*> adminList;   //list of groups this profile is an admin for
    int id;

    //Profile attributes -> expand this list
    string location, preference, age;

    //Friends list
    vector<Profile*> friendsList;

    //Groups list
    vector<Group*> groupsList;

    //Post/Message History
    vector<Post*> postHistory;
    vector<Message*> messageHistory;    //store different chats with other profiles

    //Fish owned by profile
    vector<Fish*> collection;

    //Settings
    bool access;    //private or public account

    //  -------- Methods --------  //

    void addFriend(Profile* x);
    void removeFriend(Profile* x);  //remove friend at profile
    void removeFriendForeign(Profile* x);  //remove friend at foreign profile

    void changeBio(string x);
    void changeUsername(string x);
    void changePassword(string x);
    //change attributes here

    void add_fish(Fish *fish);
    void createFish(string name, string species);
    void removeFish(Fish* x);
    void changeFishBio(Fish* x, string y);
    void changeFishLocation(Fish* x, string y);

    void addAdminGroup(Group* g);

    void addMessage(Message* m);
    void add_post(Post *p);
    void addPost(Post* p);
    void addGroup(Group* g);

    // --- Getter/Setter Methods --- //

    int get_id();
    string getNameFirst();
    string getNameLast();
    string getUsername();
    string getBio();
    string getLocation();
    string getPreference();
    string getAge();

private:
    int profileId;
    QString username;
    QString name;
    QString type;
    QDateTime dateCreated;
    QString description;

};

#endif // PROFILE_H
