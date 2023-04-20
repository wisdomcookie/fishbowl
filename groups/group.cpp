#include "group.h"



Group::Group(){

}
Group::Group(std::string name): name(name){

}

Group::~Group(){

}
/*
void Group::add_member(Person *person){
    members.insert(person);
}

bool Group::remove_member(Person *person){
    return members.erase(person);
}
void Group::add_admin(Administrator *administrator){
    admin.insert(administrator);
}
bool Group::remove_admin(Administrator *administrator){
    return admin.erase(administrator);
}
void Group::add_post(Post *post){
    postHistory.push_back(post);
}
*/
bool Group::remove_post(Post *post){

    for(unsigned int i = 0 ; i < postHistory.size(); i++){
        if(postHistory[i] == post){
            postHistory.erase(postHistory.begin() + i);
            return true;
        }
    }
    return false;
}

void Group::set_description(std::string newDescription){
    description = newDescription;
}

std::string Group::get_name(){
    return name;
}
std::string Group::get_description(){
    return description;
}/*
std::set<Administrator*> Group::get_admin(){
    return admin;
}
std::set<Person*> Group::get_members(){
    return members;
}*/
Aquarium Group::get_aquarium(){
    return aquarium;
}
