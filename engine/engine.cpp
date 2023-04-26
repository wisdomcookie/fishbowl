#include "engine.h"
#include "../comm/postcomment.h"
#include "../comm/groupchat.h"

Engine::Engine()
{
    db = new Database();

    dateFormat = QString("yyyy-MM-dd hh:mm:ss");

    profileFields = {
        QString("profile_id"), QString("username"), QString("firstName"), QString("lastName"), QString("age"), QString("type"), QString("location"), QString("date_created"), QString("description")
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
        profiles[requestorId]->addFriend(profiles[requestedId]);
        profiles[requestedId]->addFriend(profiles[requestorId]); // two way friending
    } // loading and adding friends by finding the profiles corresponding to the ids in the record

    std::vector<std::map<QString, QString>> fishData = db->query_select(QString("fish"), fishFields);

    for(std::map<QString, QString> &row: fishData){ // fix fish loading
        int fishId = row[QString("fish_id")].toInt();
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

void Engine::create_profile(QString username, QString firstName, QString lastName, int age, QString location, QString type, QDateTime dateCreated, QString description){

    int nextId = db->get_next_id(QString("profiles"));
    Profile *profile = new Profile(nextId, username, firstName, lastName, age, location, type, dateCreated, description);

    std::vector<QVariant> profileData =
        {username, firstName, lastName, age, location, type, dateCreated.toString(dateFormat), description};

    profiles[profile->get_id()] = profile; // inserts profile into profile map
    db->query_insert(QString("profiles"), profileFields, profileData); // inserts profile into database
}

void Engine::create_post(Profile *actor, Group *group, QDateTime dateCreated, QString title, QString content){

    int nextId = db->get_next_id(QString("posts"));
    Post *post = new Post(nextId, actor, group, dateCreated, title, content);

    std::vector<QVariant> postData = {
                                      post->get_id(), actor->get_id(), group->get_id(), post->get_dateCreated().toString(dateFormat), title, content, post->get_visibility()
    };

    posts[post->get_id()] = post; // inserts post into post map
    actor->add_post(post); // adds post to poster
    group->add_post(post);  // adds post to group
    db->query_insert(QString("posts"), postFields, postData);  // inserts post into database
}

void Engine::create_comment(Profile *actor, Post *post, QString content){

    int nextId = db->get_next_id(QString("comments"));
    PostComment *comment = new PostComment(nextId, actor, post, content);

    QString commentId = QString::number(comment->get_id());
    QString postId = QString::number(post->get_id());
    QString commenterId = QString::number(actor->get_id());
    QString parentCommentId = QString::number(0); // comments that are not replies are replies to a placeholder comment with id 0
    QString dateCreated = post->get_dateCreated().toString(dateFormat);
    QString visibility = QString::number(comment->get_visibility());

    std::vector<QVariant> commentData = {
        comment->get_id(), post->get_id(), actor->get_id(), parentCommentId, dateCreated, visibility
    };

    post->add_comment(comment); // adds comment to post
    actor->add_comment(comment); // adds comment to commenter
    db->query_insert(QString("comments"), commentFields, commentData);
}

void Engine::create_comment_reply(Profile *actor, Post *post, PostComment *parentComment, QString content){

    int nextId = db->get_next_id(QString("comments"));
    PostComment *comment = new PostComment(nextId, actor, post, content);

    QString commentId = QString::number(comment->get_id());
    QString postId = QString::number(post->get_id());
    QString commenterId = QString::number(actor->get_id());
    QString parentCommentId = QString::number(parentComment->get_id());
    QString dateCreated = post->get_dateCreated().toString(dateFormat);
    QString visibility = QString::number(comment->get_visibility());

    std::vector<QString> commentData = {
        commentId, postId, commenterId, parentCommentId, dateCreated, visibility
    };

    post->add_comment(comment); // adds comment to post
    parentComment->add_reply(comment); // adds comment to parent comment
    actor->add_comment(comment); // adds comment to commenter
    db->query_insert(QString("comments"), commentFields, commentData);

}
void Engine::create_groupchat(Profile *actor, QString name, std::vector<Profile*> participants){

    int nextId = db->get_next_id(QString("groupchats"));
    GroupChat *groupchat = new GroupChat(nextId, actor, name, participants);

    QString groupchatId = QString::number(groupchat->get_id());
    QString ownerId = QString::number(actor->get_id());
    QString size = QString::number(groupchat->get_size());
    QString dateCreated = groupchat->get_dateCreated().toString(dateFormat);

    std::vector<QString> groupchatData = {
        groupchatId, ownerId, name, size, dateCreated
    };

    groupchats[groupchat->get_id()] = groupchat; // inserts groupchat into groupchat map
    db->query_insert(QString("groupchats"), groupchatFields, groupchatData); // inserts groupchat into database

    for(Profile *participant: participants){
        QString participantId = QString::number(participant->get_id());
        std::vector<QString> groupchatParticipantData = {groupchatId, participantId};
        participant->add_groupchat(groupchat); // adds groupchat to participant
        db->query_insert(QString("groupchat_participants"), groupchatParticipantFields, groupchatParticipantData); // inserts participant into database
    }

}
void Engine::create_group(Profile *actor, QString name, QString description){

    int nextId = db->get_next_id(QString("groups"));
    Group *group = new Group(nextId, actor, name, description);

    QString groupId = QString::number(group->get_id());
    QString size = QString::number(group->get_size());
    QString dateCreated = group->get_dateCreated().toString(dateFormat);

    std::vector<QString> groupData = {
        groupId, name, size, dateCreated, description
    };

    groups[group->get_id()] = group; // inserts group into groups map
    db->query_insert(QString("groups"), groupFields, groupData); // inserts group into database
    actor->add_admin_group(group);   // adds group to admin

    QString profileId = QString::number(actor->get_id());
    std::vector<QString> groupMemberData = {groupId, profileId};
    db->query_insert(QString("group_members"), groupMemberFields, groupMemberData); // adds creator as group member to database

    QString adminId = profileId;
    std::vector<QString> adminData = {groupId, adminId};
    db->query_insert(QString("admins"), adminFields, adminData); // adds creator as group admin to database

}
void Engine::create_message(Profile *actor, GroupChat *groupchat, QString content){

    int nextId = db->get_next_id(QString("groups"));
    Message *message = new Message(nextId, actor, groupchat, content);

    QString messageId = QString::number(message->get_id());
    QString senderId = QString::number(actor->get_id());
    QString groupchatId = QString::number(groupchat->get_id());
    QString dateCreated = message->get_dateCreated().toString(dateFormat);

    std::vector<QString> messageData = {
        messageId, senderId, groupchatId, dateCreated, content
    };

    groupchat->add_message(message); // adds message to groupchat
    db->query_insert(QString("messages"), messageFields, messageData); // inserts group into database
    actor->add_message(message);   // adds message to sender

}
void Engine::create_fish(Profile *actor, QString name, int age, QString location, QString species, QString description){

    int nextId = db->get_next_id(QString("fish"));
    Fish *fish = new Fish(nextId, actor, name, age, location, species, description);

    QString fishId = QString::number(fish->get_id());
    QString ownerId = QString::number(actor->get_id());
    QString dateCreated = fish->get_dateCreated().toString(dateFormat);

    std::vector<QString> fishData = {
        fishId, ownerId, name, QString::number(age), location, species, dateCreated, description
    };

    actor->add_fish(fish) // adds fish to owner
    db->query_insert(QString("fish"), fishFields, fishData); // inserts fish into database
}

void Engine::join_group(Profile *actor, Group *group){

    QString profileId = QString::number(actor->get_id());
    QString groupId = QString::number(group->get_id());

    std::vector<QString> groupMemberData = {profileId, groupId};

    group->add_member(actor); // adds member to group
    db->query_insert(QString("group_members"), groupMemberData, groupMemberFields);

}
void Engine::join_groupchat(Profile *actor, GroupChat *groupchat){

    QString profileId = QString::number(actor->get_id());
    QString groupchatId = QString::number(groupchat->get_id());

    std::vector<QString> groupchatParticipantData = {profileId, groupchatId};

    groupchat->add_participant(actor); // add member to groupchat
    actor->add_groupchat(groupchat); // add groupchat to member
    db->query_insert(QString("group_members"), groupchatParticipantData, groupchatParticipantFields);

}

void Engine::leave_group(Profile *actor, Group *group){

    QString memberId = QString::number(actor->get_id());
    QString groupId = QString::number(group->get_id());

    if(actor->is_admin(group)){
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
