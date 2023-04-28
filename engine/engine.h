#ifndef ENGINE_H
#define ENGINE_H

#include <QDateTime>

class Profile;
class Fish;
class Group;
class Post;
class PostComment;
class GroupChat;
class Message;
class Database;

class Engine
{
public:
    Engine();

    ~Engine();

    void update_data();
    void load_data();

    // Regular user

    void create_profile(QString username, QString password, QString firstName, QString lastName, int age, QString location, QDateTime dateCreated, QString description);
    void create_post(Profile *actor, Group *group, QDateTime dateCreated, QString title, QString content);
    void create_comment(Profile *actor, Post *post, QDateTime dateCreated, QString content);
    void create_comment_reply(Profile *actor, Post *post, PostComment *parentComment, QDateTime dateCreated, QString content);
    void create_groupchat(Profile *actor, QString name, QDateTime dateCreated, std::vector<Profile*> participants);
    void create_group(Profile *actor, QString name, QDateTime dateCreated, QString description);
    void create_message(Profile *actor, GroupChat *groupchat, QDateTime dateCreated, QString content);
    void create_fish(Profile *actor, QString name, int age, QString location, QString species, QDateTime dateCreated, QString description);

    void join_group(Profile *actor, Group *group);
    void join_groupchat(Profile *actor, GroupChat *groupchat);

    void unfriend(Profile *actor, Profile *friendProfile);
    void leave_group(Profile *actor, Group *group);
    void leave_groupchat(Profile *actor, GroupChat *groupchat);

    void edit_profile(Profile *actor, QString firstName, QString lastName, int age, QString location, QString description);
    void edit_fish(Profile *actor, Fish *fish, QString name, int age, QString location, QString species, QString description);
    void edit_password(Profile *actor, QString newPassword);
    void edit_post(Profile *actor, Post *post, QString newContent);
    void edit_comment(Profile *actor, PostComment *comment, QString newContent);

    void delete_my_fish(Profile *actor, Fish *fish);
    void delete_my_post(Profile *actor, Post *post);
    void delete_my_comment(Profile *actor, PostComment *comment);
    void delete_groupchat(Profile *actor, GroupChat *groupchat);

    // Admin

    void edit_group_description(Profile *actor, Group *group, QString newDescription);
    void remove_from_group(Profile *actor, Group *group, Profile *groupMember);
    void delete_group(Profile *actor, Group *group);
    void delete_post(Profile *actor, Post *post);
    void delete_comment(Profile *actor, PostComment *comment);
    void ban_user(Profile *actor, Profile *user, Group *group, QDateTime banDate, QString reason);

    // Login
    Profile* loginEngine(QString username, QString password);

    // Getters
    std::vector<Profile*> get_profileList();
    std::vector<Group*> get_groupList();
    std::vector<Post*> get_postList();
    std::vector<GroupChat*> get_groupchatList();


private:
    Database *db;
    QString dateFormat;

    std::map<int, Profile*> profiles;
    std::map<int, Group*> groups;
    std::map<int, Post*> posts;
    std::map<int, GroupChat*> groupchats;

    std::vector<QString> profileFields;
    std::vector<QString> fishFields;
    std::vector<QString> groupFields;
    std::vector<QString> groupMemberFields;
    std::vector<QString> friendsFields;

    std::vector<QString> postFields;
    std::vector<QString> commentFields;
    std::vector<QString> groupchatFields;
    std::vector<QString> groupchatParticipantFields;
    std::vector<QString> messageFields;

    std::vector<QString> adminFields;
    std::vector<QString> bannedUserFields;
    std::vector<QString> loginFields;

};

#endif // ENGINE_H
