#include "engine.h"
#include "database.h"
#include "../groups/group.h"
#include "../profiles/profile.h"
#include "../profiles/fish.h"
#include "../comm/post.h"
#include "../comm/postcomment.h"
#include "../comm/groupchat.h"
#include "../comm/message.h"

Engine::Engine()
{
    db = new Database();

    dateFormat = QString("yyyy-MM-dd hh:mm:ss");

    profileFields = {
        QString("profile_id"), QString("username"), QString("firstName"), QString("lastName"), QString("age"), QString("location"), QString("date_created"), QString("description")
    };

    fishFields = {
        QString("fish_id"), QString("owner_id"), QString("name"), QString("age"), QString("location"), QString("species"), QString("date_created"), QString("description")
    };

    groupFields = {
        QString("group_id"), QString("name"), QString("size"), QString("date_created"), QString("description")
    };

    groupMemberFields = {
        QString("group_id"), QString("profile_id")
    };
    friendsFields = {
        QString("requestor_id"), QString("requested_id")
    };

    postFields = {
        QString("post_id"), QString("poster_id"), QString("date_created"), QString("content"), QString("group_id"), QString("visibility")
    };
    commentFields = {
        QString("comment_id"), QString("post_id"), QString("commenter_id"), QString("parent_comment_id"), QString("date_created"), QString("content")
    };
    groupchatFields = {
        QString("groupchat_id"), QString("name"), QString("size"), QString("date_created")
    };
    groupchatParticipantFields = {
        QString("groupchat_id"), QString("participant_id")
    };
    messageFields = {
        QString("message_id"), QString("sender_id"), QString("groupchat_id"), QString("date_created"), QString("content")
    };
    adminFields = {
        QString("group_id"), QString("admin_id")
    };

    bannedUserFields = {
        QString("profile_id"), QString("group_id"), QString("ban_date"), QString("reason")
    };

    loginFields = {
        QString("username"), QString("password")
    };


}


Engine::~Engine(){
    delete db;
}

void Engine::update_data(){

}

void Engine::load_data(){

    std::vector<std::map<QString, QString>> profileData = db->query_select(QString("profiles"), profileFields);

    for(std::map<QString, QString> &row: profileData){
        Profile *profile = new Profile(row);
        profiles[profile->get_id()] = profile;
    } // loading and adding profiles by passing each record as a map of data to constructor

    std::vector<std::map<QString, QString>> groupData = db->query_select(QString("groups"), groupFields);

    for(std::map<QString, QString> &row: groupData){
        Group *group = new Group(row);
        groups[group->get_id()] = group;
    } // loading and adding groups by passing each record as a map of data to constructor

    std::vector<std::map<QString, QString>> groupMemberData = db->query_select(QString("group_participants"), groupMemberFields);

    for(std::map<QString, QString> &row: groupMemberData){
        int groupId = row[QString("group_id")].toInt();
        int profileId = row[QString("profile_id")].toInt();
        groups[groupId]->add_member(profiles[profileId]);
    } // loading and adding group participants by finding the groups and profiles corresponding to the ids of the record

    std::vector<std::map<QString, QString>> friendsData = db->query_select(QString("friends"), friendsFields);

    for(std::map<QString, QString> &row: friendsData){
        int requestorId = row[QString("requestorId")].toInt();
        int requestedId = row[QString("requested_id")].toInt();
        profiles[requestorId]->add_friend(profiles[requestedId]);
        profiles[requestedId]->add_friend(profiles[requestorId]); // two way friending
    } // loading and adding friends by finding the profiles corresponding to the ids in the record

    std::vector<std::map<QString, QString>> fishData = db->query_select(QString("fish"), fishFields);

    for(std::map<QString, QString> &row: fishData){ // fix fish loading
        int ownerId = row[QString("owner_id")].toInt();
        Fish *fish = new Fish(row);
        profiles[ownerId]->add_fish(fish);
    } // loading and adding fish

    std::vector<std::map<QString, QString>> postData = db->query_select(QString("posts"), postFields);

    for(std::map<QString, QString> &row: postData){
        int groupId = row[QString("group_id")].toInt();
        int profileId = row[QString("profile_id")].toInt();
        Post *post = new Post(row);
        posts[post->get_id()] = post;
        groups[groupId]->add_post(post);
        profiles[profileId]->add_post(post);
    } // loading and adding posts

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

    std::vector<std::map<QString, QString>> groupchatData = db->query_select(QString("groupchats"), groupchatFields);

    for(std::map<QString, QString> &row: groupchatData){
        GroupChat *groupchat = new GroupChat(row);
        groupchats[groupchat->get_id()] = groupchat;
    } // loading and adding groupchats

    std::vector<std::map<QString, QString>> groupchatParticipantData = db->query_select(QString("groupchat_participants"), groupchatParticipantFields);

    for(std::map<QString, QString> &row: groupchatParticipantData){
        int groupchatId = row[QString("groupchat_id")].toInt();
        int participantId = row[QString("participant_id")].toInt();
        groupchats[groupchatId]->add_participant(profiles[participantId]);
    } // loading and adding participants to the groupchats

    std::vector<std::map<QString, QString>> messageData = db->query_select(QString("messages"), messageFields);

    for(std::map<QString, QString> &row: messageData){
        int groupchatId = row[QString("groupchat_id")].toInt();
        int senderId = row[QString("sender_id")].toInt();
        Message *message = new Message(row);
        groupchats[groupchatId]->add_message(message);
        profiles[senderId]->add_message(message); // profiles keeps messages for admin purposes ?
    } // loading and adding messages to the groupchats
}

void Engine::create_profile(QString username, QString password, QString firstName, QString lastName, int age, QString location, QDateTime dateCreated, QString description){

    int nextId = db->get_next_id(QString("profiles"));
    Profile *profile = new Profile(nextId, username, password, firstName, lastName, age, location, dateCreated, description);

    std::vector<QVariant> profileData =
        {username, firstName, lastName, age, location, dateCreated.toString(dateFormat), description};

    profiles[profile->get_id()] = profile; // inserts profile into profile map
    db->query_insert(QString("profiles"), profileFields, profileData); // inserts profile into database

    std::vector<QVariant> loginData = {
        username, password
    };
    db->query_insert(QString("login"), loginFields, loginData);
}

void Engine::create_post(Profile *actor, Group *group, QDateTime dateCreated, QString title, QString content){

    int nextId = db->get_next_id(QString("posts"));
    Post *post = new Post(nextId, actor, group, dateCreated, title, content);

    std::vector<QVariant> postData = {
        post->get_id(), actor->get_id(), group->get_id(), dateCreated.toString(dateFormat), title, content, post->get_visibility()
    };

    posts[post->get_id()] = post; // inserts post into post map
    actor->add_post(post); // adds post to poster
    group->add_post(post);  // adds post to group
    db->query_insert(QString("posts"), postFields, postData);  // inserts post into database
}

void Engine::create_comment(Profile *actor, Post *post, QDateTime dateCreated, QString content){

    int nextId = db->get_next_id(QString("comments"));
    PostComment *comment = new PostComment(nextId, actor, post, dateCreated, content);

    std::vector<QVariant> commentData = {
        comment->get_id(), post->get_id(), actor->get_id(), 0, dateCreated.toString(dateFormat), comment->get_visibility()
    }; // comments that are not replies are stored as replies to a placeholder comment with id 0

    post->add_comment(comment); // adds comment to post
    actor->add_comment(comment); // adds comment to commenter
    db->query_insert(QString("comments"), commentFields, commentData);
}

void Engine::create_comment_reply(Profile *actor, Post *post, PostComment *parentComment, QDateTime dateCreated, QString content){

    int nextId = db->get_next_id(QString("comments"));
    PostComment *comment = new PostComment(nextId, actor, post, dateCreated, content);

    std::vector<QVariant> commentData = {
        comment->get_id(), post->get_id(), actor->get_id(), parentComment->get_id(), dateCreated.toString(dateFormat), comment->get_visibility()
    };

    post->add_comment(comment); // adds comment to post
    parentComment->add_reply(comment); // adds comment to parent comment
    actor->add_comment(comment); // adds comment to commenter
    db->query_insert(QString("comments"), commentFields, commentData);

}
void Engine::create_groupchat(Profile *actor, QString name, QDateTime dateCreated, std::vector<Profile*> participants){

    int nextId = db->get_next_id(QString("groupchats"));
    GroupChat *groupchat = new GroupChat(nextId, actor, name, dateCreated, participants);

    std::vector<QVariant> groupchatData = {
        groupchat->get_id(), actor->get_id(), name, groupchat->get_size(), dateCreated.toString(dateFormat)
    };

    groupchats[groupchat->get_id()] = groupchat; // inserts groupchat into groupchat map
    db->query_insert(QString("groupchats"), groupchatFields, groupchatData); // inserts groupchat into database

    for(Profile *participant: participants){
        std::vector<QVariant> groupchatParticipantData = {groupchat->get_id(), participant->get_id()};
        participant->add_groupchat(groupchat); // adds groupchat to participant
        db->query_insert(QString("groupchat_participants"), groupchatParticipantFields, groupchatParticipantData); // inserts participant into database
    }

}
void Engine::create_group(Profile *actor, QString name, QDateTime dateCreated, QString description){

    int nextId = db->get_next_id(QString("groups"));
    Group *group = new Group(nextId, actor, name, dateCreated, description);

    std::vector<QVariant> groupData = {
        group->get_id(), name, group->get_size(), dateCreated.toString(dateFormat), description
    };

    groups[group->get_id()] = group; // inserts group into groups map
    db->query_insert(QString("groups"), groupFields, groupData); // inserts group into database
    actor->add_group_as_admin(group);   // adds group to admin

    std::vector<QVariant> groupMemberData = {group->get_id(), actor->get_id()};
    db->query_insert(QString("group_members"), groupMemberFields, groupMemberData); // adds creator as group member to database

    std::vector<QVariant> adminData = {group->get_id(), actor->get_id()};
    db->query_insert(QString("admins"), adminFields, adminData); // adds creator as group admin to database

}
void Engine::create_message(Profile *actor, GroupChat *groupchat, QDateTime dateCreated, QString content){

    int nextId = db->get_next_id(QString("groups"));
    Message *message = new Message(nextId, actor, groupchat, dateCreated, content);

    std::vector<QVariant> messageData = {
        message->get_id(), actor->get_id(), groupchat->get_id(), dateCreated.toString(dateFormat), content
    };

    groupchat->add_message(message); // adds message to groupchat
    db->query_insert(QString("messages"), messageFields, messageData); // inserts group into database
    actor->add_message(message);   // adds message to sender

}
void Engine::create_fish(Profile *actor, QString name, int age, QString location, QString species, QDateTime dateCreated, QString description){

    int nextId = db->get_next_id(QString("fish"));
    Fish *fish = new Fish(nextId, actor, name, age, location, species, dateCreated, description);

    std::vector<QVariant> fishData = {
        fish->get_id(), actor->get_id(), name, age, location, species, dateCreated.toString(dateFormat), description
    };

    actor->add_fish(fish); // adds fish to owner
    db->query_insert(QString("fish"), fishFields, fishData); // inserts fish into database
}

void Engine::join_group(Profile *actor, Group *group){

    if(group->is_banned(actor)){
        throw "User banned from group";
    }

    std::vector<QVariant> groupMemberData = {actor->get_id(), group->get_id()};

    group->add_member(actor); // adds member to group
    db->query_insert(QString("group_members"), groupMemberFields, groupMemberData);

}
void Engine::join_groupchat(Profile *actor, GroupChat *groupchat){

    std::vector<QVariant> groupchatParticipantData = {actor->get_id(), groupchat->get_id()};

    groupchat->add_participant(actor); // add member to groupchat
    actor->add_groupchat(groupchat); // add groupchat to member
    db->query_insert(QString("group_members"), groupchatParticipantFields, groupchatParticipantData);

}

void Engine::unfriend(Profile *actor, Profile *friendProfile){

    QString profileId1 = QString::number(actor->get_id());
    QString profileId2 = QString::number(friendProfile->get_id());

    actor->remove_friend(friendProfile);
    friendProfile->remove_friend(actor);

    db->query_exec(QString("delete from friends where (requestor_id=" + profileId1 + " and requested_id=" + profileId2 + ") or "
                                                     "(requestor_id=" + profileId2 + " and requested_id=" + profileId1 + ");"));

}

void Engine::leave_group(Profile *actor, Group *group){

    QString memberId = QString::number(actor->get_id());
    QString groupId = QString::number(group->get_id());

    if(group->is_admin(actor)){
        group->remove_admin(actor);
    }
    else{
        group->remove_member(actor);
    }
    actor->leave_group(group);
    db->query_exec(QString("delete from group_members where group_id=" + groupId + " and profile_id=" + memberId + ";"));
}

void Engine::leave_groupchat(Profile *actor, GroupChat *groupchat){

    QString participantId = QString::number(actor->get_id());
    QString groupchatId = QString::number(groupchat->get_id());

    groupchat->remove_participant(actor);
    actor->leave_groupchat(groupchat);
    db->query_exec(QString("delete from groupchat_participants where groupchat_id=" + groupchatId + " and participant_id=" + participantId + ";"));

}

void Engine::edit_profile(Profile *actor, QString firstName, QString lastName, int age, QString location, QString description){

    actor->edit_profile(firstName, lastName, age, location, description);

    std::vector<QString> editFields = {
        QString("first_name"), QString("last_name"), QString("age"), QString("location"), QString("description")
    };
    std::vector<QVariant> profileData = {
        firstName, lastName, age, location, description
    };

    db->query_update_by_rowid(QString("profiles"), actor->get_id(), editFields, profileData); // inserts profile into database
}

void Engine::edit_fish(Profile *actor, Fish *fish, QString name, int age, QString location, QString species, QString description){

    actor->edit_fish(fish, name, age, location, species, description);

    std::vector<QString> editFields = {
        QString("first_name"), QString("last_name"), QString("age"), QString("location"), QString("description")
    };
    std::vector<QVariant> fishData = {
        name, age, location, species, description
    };

    db->query_update_by_rowid(QString("fish"), fish->get_id(), editFields, fishData); // inserts profile into database
}

void Engine::edit_password(Profile *actor, QString newPassword){

    db->query_exec("update login set password = '" + newPassword + "' where username = '" + actor->get_username() + "';");
}

void Engine::edit_post(Profile *actor, Post *post, QString newContent){

    if(post->get_creator()!=actor){
        throw "User does not own this post";
    }
    post->set_content(newContent);
    db->query_exec("update posts set content = '" + newContent + "' where post_id = " + QString::number(post->get_id()) + ";");
}

void Engine::edit_comment(Profile *actor, PostComment *comment, QString newContent){

    if(comment->get_creator()!=actor){
        throw "User does not own this comment";
    }
    comment->set_content(newContent);
    db->query_exec("update comments set content = '" + newContent + "' where comment_id = " + QString::number(comment->get_id()) + ";");
}


//void Engine::remove_from_groupchat(Profile *actor, GroupChat *groupchat, Profile *groupchatParticipant){
//    QString participantId = QString::number(actor->get_id());
//    QString groupchatId = QString::number(groupchat->get_id());

//    groupchat->remove_participant(groupchatParticipant);
//    actor->leave_groupchat(groupchat);
//    db->query_exec(QString("delete from groupchat_participants where groupchat_id=" + groupchatId + " and participant_id=" + participantId + ";"));

//}

void Engine::delete_my_fish(Profile *actor, Fish *fish){

    if(fish->is_owner(actor)){
        throw "User doesnt own this fish";
    }
    actor->remove_fish(fish);
    db->query_delete_by_rowid(QString("fish"), fish->get_id());
    delete fish;
}

void Engine::delete_my_post(Profile *actor, Post *post){

    if(post->get_creator() != actor){
        throw "Action not permitted for user";
    }
    posts.erase(post->get_id()); // remove from posts container
    post->get_sourceGroup()->remove_post(post); // remove from source group
    actor->delete_post(post); // remove from poster's post history

    db->query_delete_by_rowid(QString("posts"), post->get_id()); // remove from database
    delete post; // deallocate pointer

}
void Engine::delete_my_comment(Profile *actor, PostComment *comment){

    if(comment->get_creator() != actor){
        throw "Action not permitted for user";
    }
    comment->get_post()->remove_comment(comment); // remove from source post
    actor->delete_comment(comment); // remove from poster's comment history

    db->query_delete_by_rowid(QString("comments"), comment->get_id()); // remove from database
    delete comment; // deallocate pointer
}

void Engine::delete_groupchat(Profile *actor, GroupChat *groupchat){

    if(groupchat->get_owner() != actor){
        throw "Action not permitted for user";
    }
    groupchats.erase(groupchat->get_id());// remove from groupchats container

    for(std::pair<int, Profile*> profile: groupchat->get_participants()){
        profile.second->leave_groupchat(groupchat); // remove from participants
    }

    db->query_delete_by_rowid(QString("groupchats"), groupchat->get_id()); // emove from database entry for the groupchat
    db->query_exec("delete from groupchat_participants where groupchat_id=" + QString::number(groupchat->get_id())); // remove the groupchat participant database entries
    delete groupchat; // deallocate pointer

}


// Admin


void Engine::edit_group_description(Profile *actor, Group *group, QString newDescription){

    if(!group->is_admin(actor)){
        throw "Non admin cant edit";
    }
    group->set_description(newDescription);
}

void Engine::remove_from_group(Profile *actor, Group *group, Profile *groupMember){

    if(!group->is_admin(actor)){
        throw "Action not permitted for user";
    }
    group->remove_member(groupMember);
    groupMember->leave_group(group);

    QString memberId = QString::number(actor->get_id());
    QString groupId = QString::number(group->get_id());
    db->query_exec(QString("delete from group_members where group_id=" + groupId + " and profile_id=" + memberId + ";"));
}


void Engine::delete_group(Profile *actor, Group *group){

    if(!group->is_admin(actor)){
        throw "Action not permitted for user";
    }
    groups.erase(group->get_id());// remove from groupchats container

    for(std::pair<int, Profile*> profile: group->get_members()){
        profile.second->leave_group(group); // remove from participants
    }

    db->query_delete_by_rowid(QString("groups"), group->get_id()); // remove from database entry for the group
    db->query_exec("delete from group_members where group_id=" + QString::number(group->get_id())); // remove the group member database entries
    delete group; // deallocate pointer
}

void Engine::delete_post(Profile *actor, Post *post){

    if(!post->get_sourceGroup()->is_admin(actor)){
        throw "Actor is not admin of the group the post is in";
    }

    posts.erase(post->get_id()); // remove from posts container
    post->get_sourceGroup()->remove_post(post); // remove from source group
    post->get_creator()->delete_post(post);; // remove from poster's post history

    db->query_delete_by_rowid(QString("posts"), post->get_id()); // remove from database
    delete post; // deallocate pointer

}

void Engine::delete_comment(Profile *actor, PostComment *comment){

    if(comment->get_creator() != actor){
        throw "Actor is not admin of the group the post is in";
    }
    comment->get_post()->remove_comment(comment); // remove from source post
    comment->get_creator()->delete_comment(comment); // remove from poster's comment history

    db->query_delete_by_rowid(QString("comments"), comment->get_id()); // remove from database
    delete comment; // deallocate pointer
}

void Engine::ban_user(Profile *actor, Profile *user, Group *group, QDateTime banDate, QString reason){

    group->ban_from_group(user);
    user->leave_group(group);

    std::vector<QVariant> bannedUserData = {
        user->get_id(), group->get_id(), actor->get_id(), banDate.toString(dateFormat), reason
    };
    db->query_insert(QString("banned_users"), bannedUserFields , bannedUserData);

}

Profile* Engine::loginEngine(QString username, QString password) {
    std::vector<Profile*> v;
    v = get_profileList();
    for (unsigned long i=0; i<v.size(); i++) {
        if (username == v.at(i)->get_username()) {
            if (password == v.at(i)->get_password()) {
                return v.at(i);
            }
        }
    }
    return NULL;
}

std::vector<Profile*> Engine::get_profileList(){
    std::vector<Profile*> res;
    for(auto i = profiles.begin(); i != profiles.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
std::vector<Group*> Engine::get_groupList(){
    std::vector<Group*> res;
    for(auto i = groups.begin(); i != groups.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
std::vector<Post*> Engine::get_postList(){
    std::vector<Post*> res;
    for(auto i = posts.begin(); i != posts.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
std::vector<GroupChat*> Engine::get_groupchatList(){
    std::vector<GroupChat*> res;
    for(auto i = groupchats.begin(); i != groupchats.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
