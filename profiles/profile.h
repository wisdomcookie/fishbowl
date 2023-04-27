#ifndef PROFILE_H
#define PROFILE_H

#include <vector>
#include <QString>
#include <QDateTime>

using namespace std;

class Group;
class Post;
class PostComment;
class GroupChat;
class Message;
class Fish;
class Aquarium;

class Profile
{
public:
    Profile();
    // user creates new profile
    Profile(int id, QString username, QString firstName, QString lastName, int age, QString location, QString type, QDateTime dateCreated, QString description);
    Profile(std::map<QString, QString> profileData); // load from database
    ~Profile();

    //    //  -------- Profile information --------  //
    //    Profile(string username, string password);
    //    //Profile owner's legal name
    //    string nameFirst, nameLast;

    //    //Profile owner's username/password
    //    //string username, password;

    //    //Profile information General
    //    string bio;
    //    vector<Group*> adminList;   //list of groups this profile is an admin for
    //    int id;

    //    //Profile attributes -> expand this list
    //    string location, preference, age;

    //    //Friends list
    //    vector<Profile*> friendsList;

    //    //Groups list
    //    vector<Group*> groupsList;

    //    //Post/Message History
    //    vector<Post*> postHistory;
    //    vector<Message*> messageHistory;    //store different chats with other profiles

    //    //Fish owned by profile
    //    vector<Fish*> collection;

    //    //Settings
    //    bool access;    //private or public account

    //  -------- Methods --------  //

    //    void addFriend(Profile* x);
    //    void removeFriend(Profile* x);  //remove friend at profile
    //    void removeFriendForeign(Profile* x);  //remove friend at foreign profile
    //    void changeBio(string x);
    //    void changeUsername(string x);
    //    void changePassword(string x);
    //    //change attributes here
    //    void createFish(string name, string species);
    //    void removeFish(Fish* x);
    //    void changeFishBio(Fish* x, string y);
    //    void changeFishLocation(Fish* x, string y);
    //    void addAdminGroup(Group* g);
    //    void addMessage(Message* m);
    //    void addPost(Post* p);
    //    void addGroup(Group* g);
    //    string getNameFirst();
    //    string getNameLast();
    //    string getUsername();
    //    string getBio();
    //    string getLocation();
    //    string getPreference();
    //    string getAge();


    void add_fish(Fish *fish);
    void add_friend(Profile *profile);
    void add_group(Group *group);
    void add_group_as_admin(Group *g);
    void add_groupchat(GroupChat *groupchat);
    void add_message(Message* m);
    void add_post(Post *p);
    void add_comment(PostComment *comment);

    void edit_profile(QString firstName, QString lastName, int age, QString location, QString description);
    void edit_fish(Fish *fish, QString name, int age, QString location, QString species, QString description);
    void edit_post(Post *post, QString newContent);
    void edit_comment(PostComment *comment, QString newContent);

    void remove_fish(Fish *fish);
    void remove_friend(Profile *profile);
    void leave_group(Group *group);
    void leave_groupchat(GroupChat *groupchat);
    void delete_post(Post *post);
    void delete_comment(PostComment *comment);


    // --- Getter/Setter Methods --- //

    int get_id();
    QString get_username();
    QString get_firstName();
    QString get_lastName();
    int get_age();
    QString get_location();
    QString get_type();
    QDateTime get_dateCreated();
    QString get_description();


private:
    int profileId;
    QString username;
    QString firstName;
    QString lastName;
    int age;
    QString location;
    QString type;
    QDateTime dateCreated;
    QString description;

    std::map<int, GroupChat*> groupchats;
    std::map<int, Group*> groups;
    std::map<int, Profile*> friends;
    std::map<int, Post*> posts;
    std::map<int, PostComment*> comments;
    std::map<int, Message*> messages;

    Aquarium *aquarium;
};

#endif // PROFILE_H
