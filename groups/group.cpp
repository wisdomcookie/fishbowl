#include "group.h"
#include "../profiles/aquarium.h"
#include "../comm/post.h"

Group::Group(){

}

Group::Group(std::string name): name(name){

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
    postHistory.push_back(post);
}

void Group::remove_post(Post *post){
    for(unsigned int i = 0 ; i < postHistory.size(); i++){
        if (postHistory[i] == post){
            postHistory.erase(postHistory.begin() + i);
        }
    }
}

void Group::set_description(std::string newDescription){
    description = newDescription;
}

std::string Group::get_name(){
    return name;
}
std::string Group::get_description(){
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
