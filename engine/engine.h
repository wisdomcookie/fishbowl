#ifndef ENGINE_H
#define ENGINE_H

#include "../comm_database/database.h"
#include "../groups/group.h"
#include "../profiles/profile.h"

class Engine
{
public:
    Engine();

    ~Engine();

    void update_data();
    void load_data();

    void create_post(Profile *actor, Group *group, QString title, QString content);
    void create_comment(Profile *actor, Post *post, QString content);
    void create_groupchat(Profile *actor, QString name, std::vector<Profile*> participants);
    void create_group(Profile *actor, QString name, std::vector<Profile*> participants, std::vector<Profile*> admin);
    void create_message(Profile *actor, Group *group, QString content);
    void create_fish(Profile *actor, QString name);

    void join_group(Profile *actor, Group *group);
    void join_groupchat(Profile *actor, GroupChat *groupchat);

    void leave_group(Profile *actor, Group *group);
    void leave_groupchat(Profile *actor, GroupChat *groupchat);

    void edit_my_profile(Profile *actor, QString newBio = 0);
    void edit_my_fish(Profile *actor, Fish *fish, QString newContent = 0);
    void edit_my_login(Profile *actor, QString newUsername = 0, QString newPassword = 0);
    void edit_post(Profile *actor, Post *post, QString newContent = 0);
    void edit_comment(Profile *actor, PostComment *comment, QString newContent = 0);

    void remove_from_group(Profile *actor, Group *group, Profile *groupMember);
    void remove_from_groupchat(Profile *actor, GroupChat *groupchat, Profile *groupchatParticipant);

    void delete_post(Profile *actor, Post *post);
    void delete_comment(Profile *actor, PostComment *comment);
    void delete_groupchat(Profile *actor, GroupChat *groupchat);
    void delete_group(Profile *actor, Group *group);

    void ban_user(Profile *actor, Profile *user, Group *group);


private:
    Database *db;

    std::map<int, Profile*> profiles;
    std::map<int, Group*> groups;
    std::map<int, Post*> posts;
    std::map<int, GroupChat*> groupchats;


};

#endif // ENGINE_H
