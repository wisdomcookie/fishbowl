#include "engine.h"
#include "../comm/postcomment.h"
#include "../comm/groupchat.h"

Engine::Engine()
{
    db = new Database();
}


Engine::~Engine(){
    delete db;
}

void Engine::update_data(){

}
void Engine::load_data(){
    std::vector<QString> profileFields = {QString("profile_id"), QString("username"), QString("name"), QString("type"), QString("date_created"), QString("description")};
    std::vector<std::map<QString, QString>> profileData = db->query_select(QString("profiles"), profileFields);

    for(std::map<QString, QString> &row: profileData){
        Profile *profile = new Profile(row);
        profiles[profile->get_id()] = profile;
    } // loading and adding profiles by passing each record as a map of data to constructor

    std::vector<QString> groupFields = {QString("group_id"), QString("name"), QString("size"), QString("date_created"), QString("description")};
    std::vector<std::map<QString, QString>> groupData = db->query_select(QString("groups"), groupFields);

    for(std::map<QString, QString> &row: groupData){
        Group *group = new Group(row);
        groups[group->get_id()] = group;
    } // loading and adding groups by passing each record as a map of data to constructor

    std::vector<QString> groupParticipantFields = {QString("group_id"), QString("profile_id")};
    std::vector<std::map<QString, QString>> groupParticipantData = db->query_select(QString("group_participants"), groupParticipantFields);

    for(std::map<QString, QString> &row: groupParticipantData){
        int groupId = row[QString("group_id")].toInt();
        int profileId = row[QString("profile_id")].toInt();
        groups[groupId]->add_member(profiles[profileId]);
    } // loading and adding group participants by finding the groups and profiles corresponding to the ids of the record

    std::vector<QString> friendsFields = {QString("requestor_id"), QString("requested_id")};
    std::vector<std::map<QString, QString>> friendsData = db->query_select(QString("friends"), friendsFields);

    for(std::map<QString, QString> &row: friendsData){
        int requestorId = row[QString("requestorId")].toInt();
        int requestedId = row[QString("requested_id")].toInt();
        profiles[requestorId]->addFriend(profiles[requestedId]);
        profiles[requestedId]->addFriend(profiles[requestorId]); // two way friending
    } // loading and adding friends by finding the profiles corresponding to the ids in the record

    std::vector<QString> fishFields = {QString("fish_id"), QString("owner_id")};
    std::vector<std::map<QString, QString>> fishData = db->query_select(QString("fish"), fishFields);

    for(std::map<QString, QString> &row: fishData){
        int fishId = row[QString("fish_id")].toInt();
        int ownerId = row[QString("owner_id")].toInt();
        Fish *fish = new Fish(row);
        profiles[ownerId]->add_fish(fish);
    } // loading and adding fish

    std::vector<QString> postFields = {QString("post_id"), QString("poster_id"), QString("date_created"), QString("content"), QString("group_id"), QString("visibility")};
    std::vector<std::map<QString, QString>> postData = db->query_select(QString("posts"), postFields);

    for(std::map<QString, QString> &row: postData){
        int groupId = row[QString("group_id")].toInt();
        int profileId = row[QString("profile_id")].toInt();
        Post *post = new Post(row);
        posts[post->get_id()] = post;
        groups[groupId]->add_post(post);
        profiles[profileId]->add_post(post);
    } // loading and adding posts

    std::vector<QString> commentFields = {QString("comment_id"), QString("post_id"), QString("commenter_id"), QString("parent_comment_id"), QString("date_created"), QString("content")};
    std::vector<std::map<QString, QString>> commentData = db->query_select(QString("post_comments"), postFields);

    for(std::map<QString, QString> &row: commentData){
        int postId = row[QString("profile_id")].toInt();
        PostComment *comment = new PostComment(row);
        posts[postId]->add_comment(comment);
    } // loading and adding post comments

    for(std::pair<int, Post*> p: posts){
        std::map<int, PostComment*> comments = p.second->get_comments();

        for(std::pair<int, PostComment*> c: comments){
            PostComment *comment = c.second;
            PostComment *parentComment = comment->get_parentComment(); //->add_reply(comment);
            parentComment->add_reply(comment);
        }
    } // adding replies to their parent comments

    std::vector<QString> groupchatFields = {QString("groupchat_id"), QString("name"), QString("size"), QString("date_created")};
    std::vector<std::map<QString, QString>> groupchatData = db->query_select(QString("groupchats"), groupchatFields);

    for(std::map<QString, QString> &row: groupchatData){
        GroupChat *groupchat = new GroupChat(row);
        groupchats[groupchat->get_id()] = groupchat;
    } // loading and adding groupchats

    std::vector<QString> groupchatParticipantFields = {QString("groupchat_id"), QString("participant_id")};
    std::vector<std::map<QString, QString>> groupchatParticipantData = db->query_select(QString("groupchat_participants"), groupchatParticipantFields);

    for(std::map<QString, QString> &row: groupchatParticipantData){
        int groupchatId = row[QString("groupchat_id")].toInt();
        int participantId = row[QString("participant_id")].toInt();
        groupchats[groupchatId]->add_participant(profiles[participantId]);
    } // loading and adding participants to the groupchats

    std::vector<QString> messageFields = {QString("message_id"), QString("sender_id"), QString("groupchat_id"), QString("date_created"), QString("content")};
    std::vector<std::map<QString, QString>> messageData = db->query_select(QString("messages"), messageFields);

    for(std::map<QString, QString> &row: messageData){
        int groupchatId = row[QString("groupchat_id")].toInt();
        int senderId = row[QString("sender_id")].toInt();
        Message *message = new Message(row);
        groupchats[groupchatId]->add_message(message);
        //profiles[senderId]->addMessage(message);
    } // loading and adding messages to the groupchats
}

void Engine::create_post(Profile *actor, Group *group, QString title, QString content){

}
void Engine::create_comment(Profile *actor, Post *post, QString content){

}
void Engine::create_groupchat(Profile *actor, QString name, std::vector<Profile*> participants){

}
void Engine::create_group(Profile *actor, QString name, std::vector<Profile*> participants, std::vector<Profile*> admin){

}
void Engine::create_message(Profile *actor, Group *group, QString content){

}
void Engine::create_fish(Profile *actor, QString name){

}

void Engine::join_group(Profile *actor, Group *group){

}
void Engine::join_groupchat(Profile *actor, GroupChat *groupchat){

}

void Engine::leave_group(Profile *actor, Group *group){

}
void Engine::leave_groupchat(Profile *actor, GroupChat *groupchat){

}

void Engine::edit_my_profile(Profile *actor, QString newBio /*= 0*/){

}
void Engine::edit_my_fish(Profile *actor, Fish *fish, QString newContent /*= 0*/){

}
void Engine::edit_my_login(Profile *actor, QString newUsername /*= 0*/, QString newPassword /*= 0*/){

}
void Engine::edit_post(Profile *actor, Post *post, QString newContent /*= 0*/){

}
void Engine::edit_comment(Profile *actor, PostComment *comment, QString newContent /*= 0*/){

}

void Engine::remove_from_group(Profile *actor, Group *group, Profile *groupMember){

}
void Engine::remove_from_groupchat(Profile *actor, GroupChat *groupchat, Profile *groupchatParticipant){

}

void Engine::delete_post(Profile *actor, Post *post){

}
void Engine::delete_comment(Profile *actor, PostComment *comment){

}
void Engine::delete_groupchat(Profile *actor, GroupChat *groupchat){

}
void Engine::delete_group(Profile *actor, Group *group){

}

void Engine::ban_user(Profile *actor, Profile *user, Group *group){

}
