#ifndef PROFILE_H
#define PROFILE_H

#include <vector>
#include <QString>
#include <QDateTime>
#include "fish.h"
#include "aquarium.h"
#include "../groups/group.h"
#include "../comm/post.h"
#include "../comm/postcomment.h"
#include "../comm/groupchat.h"
#include "../comm/message.h"

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
    //Profile(int id, QString username, QString password, QString firstName, QString lastName, int age, QString location, QDateTime dateCreated, QString description);
    Profile(int id, QString username, QString firstName, QString lastName, int age, QString location, QDateTime dateCreated, QString description);
    Profile(std::map<QString, QString> profileData); // load from database
    ~Profile();

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

    bool is_friend(Profile *friendProfile);


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

    std::vector<Fish*> get_fishList();
    std::vector<Profile*> get_friendList();
    std::vector<Group*> get_groupList();
    std::vector<Post*> get_postHistory();
    std::vector<GroupChat*> get_groupchats();
    std::vector<Message*> get_messageHistory();

    QString get_password();
;

private:
    int profileId;
    QString username;
    QString password;
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

    std::map<int, Fish*> fishList;

    Aquarium *aquarium;
};

#endif // PROFILE_H
