#include "group.h"
#include "../profiles/aquarium.h"
#include "../profiles/profile.h"
#include "../comm/post.h"

/**
 * @brief Group::Group
 */
Group::Group(){

}

/**
 * Constructor used when a new group is created
 * @brief Group::Group
 * @param id
 * @param creator
 * @param name
 * @param dateCreated
 * @param description
 */
Group::Group(int id, Profile *creator, QString name, QDateTime dateCreated, QString description):
    groupId(id), name(name), size(1), dateCreated(dateCreated), description(description){

    members[creator->get_id()] = creator;
    admin[creator->get_id()] = creator;

} // user creates new group

/**
 * Constructor used to populate the website from the database
 * @brief Group::Group
 * @param groupData
 */
Group::Group(std::map<QString, QString> groupData){

    groupId = groupData[QString("group_id")].toInt();
    name = groupData[QString("name")];
    size = groupData[QString("size")].toInt();

    QString dateString = groupData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

    description = groupData[QString("description")];
} // load from database

/**
 * @brief Group::~Group
 */
Group::~Group(){

}

/**
 * Adds a user to group's list of members
 * @brief Group::add_member
 * @param profile
 */
void Group::add_member(Profile *profile){
    members[profile->get_id()] = profile;
}
/**
 * Make a user an administrator of this group and add them to the list of admins
 * @brief Group::add_admin
 * @param administrator
 */
void Group::add_admin(Profile *administrator){
    admin[administrator->get_id()] = administrator;
}
/**
 * Add a post to the group's post list
 * @brief Group::add_post
 * @param post
 */
void Group::add_post(Post *post){
    posts[post->get_id()] = post;
}

/**
 * Removes a user from the group
 * @brief Group::remove_member
 * @param profile
 */
void Group::remove_member(Profile *profile){
    members.erase(profile->get_id());
}

/**
 * Removes an administrator from the group
 * @brief Group::remove_admin
 * @param administrator
 */
void Group::remove_admin(Profile *administrator){
    admin.erase(administrator->get_id());
}
/**
 * Removes a post from the group's list of posts
 * @brief Group::remove_post
 * @param post
 */
void Group::remove_post(Post *post){
    posts.erase(post->get_id());
}
/**
 * Adds a user to the banned users list and removes them from the group
 * @brief Group::ban_from_group
 * @param profile
 */
void Group::ban_from_group(Profile *profile){
    bannedUsers[profile->get_id()] = profile;
    members.erase(profile->get_id());
}
/**
 * Checks if a member is an admin of this group
 * @brief Group::is_admin
 * @param profile
 * @return true if they are an admin
 */
bool Group::is_admin(Profile *profile){
    return (admin.find(profile->get_id()) != admin.end());
}
/**
 * Checks if a user is a member of this group
 * @brief Group::is_member
 * @param profile
 * @return true if they are a member
 */
bool Group::is_member(Profile *profile){
    return (members.find(profile->get_id()) != members.end());
}
/**
 * Checks if a user is banned from this group
 * @brief Group::is_banned
 * @param profile
 * @return true if they are banned
 */
bool Group::is_banned(Profile *profile){
    return (bannedUsers.find(profile->get_id()) != bannedUsers.end());
}

//********SETTER AND GETTER METHODS********/////////

/**
 * Sets group's description
 * @brief Group::set_description
 * @param newDescription
 */
void Group::set_description(QString newDescription){
    description = newDescription;
}
/**
 * @brief Group::get_id
 * @return id of this group
 */
int Group::get_id(){
    return groupId;
}
/**
 * @brief Group::get_name
 * @return name of this group
 */
QString Group::get_name(){
    return name;
}
/**
 * @brief Group::get_size
 * @return number of members in this group
 */
int Group::get_size(){
    return size;
}
/**
 * @brief Group::get_description
 * @return decription of this group
 */
QString Group::get_description(){
    return description;
}
/**
 * @brief Group::get_admin
 * @return list of administrators for this group
 */
std::vector<Profile*> Group::get_admin(){
    std::vector<Profile*> res;
    for(auto i = admin.begin(); i != admin.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
/**
 * @brief Group::get_members
 * @return list of members of this group
 */
std::vector<Profile*> Group::get_members(){
    std::vector<Profile*> res;
    for(auto i = members.begin(); i != members.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
/**
 * @brief Group::get_postHistory
 * @return list of posts in this group
 */
std::vector<Post*> Group::get_postHistory(){
    std::vector<Post*> res;
    for(auto i = posts.begin(); i != posts.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
/**
 * @brief Group::get_aquarium
 * @return this group's aquarium
 */
Aquarium *Group::get_aquarium(){
    return aquarium;
}
