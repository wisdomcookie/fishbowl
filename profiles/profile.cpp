#include "profile.h"

profile::profile() {
}

profile::profile(string username, string password, string nameFirst, string nameLast) {
    this->username = username;
    this->password = password;
    this->nameFirst = nameFirst;
    this->nameLast = nameLast;
    Database d;
    d.query_exec("select * from profiles");
    id = d.query_size() + 1;
}

profile::~profile() {
    delete this;
}

/**
 * Add a friend to your friends list. Your new friend will need to add you back
 * for the friending process to be completed.
 * @brief profile::addFriend
 * @param x
 */
void profile::addFriend(profile* x) {
    friendsList.push_back(x);
}

/**
 * Remove a friend from your friends list. This does not require a signal from
 * the target profile to take effect. This method will call the addendum method
 * removeFriendForeign that will remove you from the ex-friend's friend list
 * without their permission.
 * @brief profile::removeFriend
 * @param x
 */
void profile::removeFriend(profile* x) {
    for (unsigned long i=0; i<friendsList.size(); i++) {
        if (friendsList.at(i) == x) {
            friendsList.erase(friendsList.begin() + i);
        }
    }
    removeFriendForeign(this);
}

/**
 * Refer to description in removeFriend method.
 * @brief profile::removeFriendForeign
 * @param x
 */
void profile::removeFriendForeign(profile* x) {
    for (unsigned long i=0; i<x->friendsList.size(); i++) {
        if (x->friendsList.at(i) == this) {
            x->friendsList.erase(friendsList.begin() + i);
        }
    }
}

/**
 * This method and changeUsername & changePassword are simple edit
 * methods available to the user to change their profile info.
 */
void profile::changeBio(string x) {
    bio = x;
}
void profile::changeUsername(string x) {
    username = x;
}
void profile::changePassword(string x) {
    password = x;
}

/**
 * The following method will add a fish with the specified name
 * to the profile's collection of fish.
 * @brief profile::createFish
 * @param name
 */
fish* profile::createFish(string name, string species, string bio) {
    fish* x = new fish(name, species, bio);
    collection.push_back(x);
    x->location = this->location;
    x->owner = this;
    return x;
}

/**
 * Will remove a fish from the profile's collection.
 * @brief profile::removeFish
 * @param x
 */
void profile::removeFish(fish* x) {
    for (unsigned long i=0; i<collection.size(); i++) {
        if (collection.at(i) == x) {
            collection.erase(collection.begin() + i);
        }
    }
}

/**
 * Change bio of particular fish in collection.
 * @brief profile::changeFishBio
 * @param x
 * @param y
 */
void profile::changeFishBio(fish* x, string y) {
    x->bio = y;
}

/**
 * The fish's location will be set to the profile's current
 * location when created. This method will allow that to be
 * changed at any time, at the discretion of the user.
 * @brief profile::changeFishLocation
 * @param x
 * @param y
 */
void profile::changeFishLocation(fish* x, string y) {
    x->location = y;
}

/**
 * Add group to the adminlist.
 * @brief profile::addAdminGroup
 * @param g
 */
void profile::addAdminGroup(Group* g) {
    adminList.push_back(g);
}

/**
 * Add a message to the profile's history of messages.
 * @brief profile::addMessage
 * @param m
 */
void profile::addMessage(Message* m) {
    messageHistory.push_back(m);
}

/**
 * Add a post to the profile's history of posts.
 * @brief profile::addPost
 * @param p
 */
void profile::addPost(Post* p) {
    postHistory.push_back(p);
}

/**
 * Add a group to the profile's list of groups.
 * @brief profile::addGroup
 * @param g
 */
void profile::addGroup(Group* g) {
    groupsList.push_back(g);
}

/**
 * Create a new group, will automatically make this profile
 * the sole member and admin of said group.
 * @brief profile::createGroup
 * @param name
 */
void profile::createGroup(string name) {
    Group* g = new Group(name);
    addGroup(g);
    addAdminGroup(g);
    g->add_member(this);
    g->add_admin(this);
}


//Getter and setter methods
string profile::getNameFirst() {
    return nameFirst;
}
string profile::getNameLast() {
    return nameLast;
}
string profile::getUsername() {
    return username;
}
string profile::getBio() {
    return bio;
}
string profile::getLocation() {
    return location;
}
string profile::getPreference() {
    return preference;
}
string profile::getAge() {
    return age;
}









