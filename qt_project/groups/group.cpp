#include "group.h"
#include "../profiles/aquarium.h"
#include "../profiles/profile.h"
#include "../comm/post.h"

Group::Group(){

}

Group::Group(int id, Profile *creator, QString name, QDateTime dateCreated, QString description):
    groupId(id), name(name), size(1), dateCreated(dateCreated), description(description){

    members[creator->get_id()] = creator;
    admin[creator->get_id()] = creator;

} // user creates new group


Group::Group(std::map<QString, QString> groupData){

    groupId = groupData[QString("group_id")].toInt();
    name = groupData[QString("name")];
    size = groupData[QString("size")].toInt();

    QString dateString = groupData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

    description = groupData[QString("description")];
} // load from database


Group::~Group(){

}

void Group::add_member(Profile *profile){
    members[profile->get_id()] = profile;
}


void Group::add_admin(Profile *administrator){
    admin[administrator->get_id()] = administrator;
}

void Group::add_post(Post *post){
    posts[post->get_id()] = post;
}


void Group::remove_member(Profile *profile){
    members.erase(profile->get_id());
}


void Group::remove_admin(Profile *administrator){
    admin.erase(administrator->get_id());
}

void Group::remove_post(Post *post){
    posts.erase(post->get_id());
}

void Group::ban_from_group(Profile *profile){
    bannedUsers[profile->get_id()] = profile;
    members.erase(profile->get_id());
}

bool Group::is_admin(Profile *profile){
    return (admin.find(profile->get_id()) != admin.end());
}

bool Group::is_member(Profile *profile){
    return (members.find(profile->get_id()) != members.end());
}

bool Group::is_banned(Profile *profile){
    return (bannedUsers.find(profile->get_id()) != bannedUsers.end());
}



void Group::set_description(QString newDescription){
    description = newDescription;
}

int Group::get_id(){
    return groupId;
}
QString Group::get_name(){
    return name;
}
int Group::get_size(){
    return size;
}
QString Group::get_description(){
    return description;
}
std::vector<Profile*> Group::get_admin(){
    std::vector<Profile*> res;
    for(auto i = admin.begin(); i != admin.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
std::vector<Profile*> Group::get_members(){
    std::vector<Profile*> res;
    for(auto i = members.begin(); i != members.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
std::vector<Post*> Group::get_postHistory(){
    std::vector<Post*> res;
    for(auto i = posts.begin(); i != posts.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
Aquarium *Group::get_aquarium(){
    return aquarium;
}
