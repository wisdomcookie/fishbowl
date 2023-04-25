#include "group.h"
#include "../profiles/aquarium.h"
#include "../comm/post.h"

Group::Group(){

}

Group::Group(QString name): name(name){

}

Group::Group(int id, QString name, int size, QDateTime dateCreated, QString description):
    groupId(id), name(name), size(size), dateCreated(dateCreated), description(description){


}

Group::Group(std::map<QString, QString> groupData){

    groupId = groupData[QString("group_id")].toInt();
    name = groupData[QString("name")];
    size = groupData[QString("size")].toInt();

    QString dateString = groupData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

    description = groupData[QString("description")];
}

Group::~Group(){

}

void Group::add_member(Profile *person){
    members.insert(person);
}

void Group::remove_member(Profile *person){
    members.erase(person);
}

void Group::add_admin(Profile *administrator){
    admin.insert(administrator);
}

void Group::remove_admin(Profile *administrator){
    admin.erase(administrator);
}

void Group::add_post(Post *post){
    posts.push_back(post);
}

void Group::remove_post(Post *post){
    for(unsigned int i = 0 ; i < posts.size(); i++){
        if (posts[i] == post){
            posts.erase(posts.begin() + i);
        }
    }
}

void Group::set_description(QString newDescription){
    description = newDescription;
}

void Group::set_members(std::set<Profile *> newMembers){
    members = newMembers;
}
void Group::set_admin(std::set<Profile*> newAdmin){
    admin = newAdmin;
}
void Group::set_posts(std::vector<Post*> newPosts){
    posts = newPosts;
}

int Group::get_id(){
    return groupId;
}
QString Group::get_name(){
    return name;
}
QString Group::get_description(){
    return description;
}
std::set<Profile*> Group::get_admin(){
    return admin;
}
std::set<Profile*> Group::get_members(){
    return members;
}
Aquarium Group::get_aquarium(){
    return aquarium;
}
