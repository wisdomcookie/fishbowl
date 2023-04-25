#include "profile.h"

Profile::Profile() {
}

Profile::Profile(string username, string password) {
    this->username = username;
    this->password = password;
    //Database d;
    //d.query_exec("select * from Profiles");  //make sure name of table is correct
    //id = d.query_size() + 1;
}

Profile::~Profile() {
    delete this;
}

/**
 * Add a friend to your friends list. Your new friend will need to add you back
 * for the friending process to be completed.
 * @brief Profile::addFriend
 * @param x
 */
void Profile::addFriend(Profile* x) {
    friendsList.push_back(x);
}

/**
 * Remove a friend from your friends list. This does not require a signal from
 * the target Profile to take effect. This method will call the addendum method
 * removeFriendForeign that will remove you from the ex-friend's friend list
 * without their permission.
 * @brief Profile::removeFriend
 * @param x
 */
void Profile::removeFriend(Profile* x) {
    for (unsigned long i=0; i<friendsList.size(); i++) {
        if (friendsList.at(i) == x) {
            friendsList.erase(friendsList.begin() + i);
        }
    }
    removeFriendForeign(this);
}

/**
 * Refer to description in removeFriend method.
 * @brief Profile::removeFriendForeign
 * @param x
 */
void Profile::removeFriendForeign(Profile* x) {
    for (unsigned long i=0; i<x->friendsList.size(); i++) {
        if (x->friendsList.at(i) == this) {
            x->friendsList.erase(friendsList.begin() + i);
        }
    }
}

/**
 * This method and changeUsername & changePassword are simple edit
 * methods available to the user to change their Profile info.
 */
void Profile::changeBio(string x) {
    bio = x;
}
void Profile::changeUsername(string x) {
    username = x;
}
void Profile::changePassword(string x) {
    password = x;
}

/**
 * The following method will add a Fish with the specified name
 * to the Profile's collection of Fish.
 * @brief Profile::createFish
 * @param name
 */
Fish* Profile::createFish(string name, string species, string bio) {
    Fish* x = new Fish(name, species, bio);
    collection.push_back(x);
    x->location = this->location;
    return x;
}

/**
 * Will remove a Fish from the Profile's collection.
 * @brief Profile::removeFish
 * @param x
 */
void Profile::removeFish(Fish* x) {
    for (unsigned long i=0; i<collection.size(); i++) {
        if (collection.at(i) == x) {
            collection.erase(collection.begin() + i);
        }
    }
}

/**
 * Change bio of particular Fish in collection.
 * @brief Profile::changeFishBio
 * @param x
 * @param y
 */
void Profile::changeFishBio(Fish* x, string y) {
    x->bio = y;
}

/**
 * The Fish's location will be set to the Profile's current
 * location when created. This method will allow that to be
 * changed at any time, at the discretion of the user.
 * @brief Profile::changeFishLocation
 * @param x
 * @param y
 */
void Profile::changeFishLocation(Fish* x, string y) {
    x->location = y;
}

/**
 * Add group to the adminlist.
 * @brief Profile::addAdminGroup
 * @param g
 */
void Profile::addAdminGroup(Group* g) {
    adminList.push_back(g);
}

/**
 * Add a message to the Profile's history of messages.
 * @brief Profile::addMessage
 * @param m
 */
void Profile::addMessage(Message* m) {
    messageHistory.push_back(m);
}

/**
 * Add a post to the Profile's history of posts.
 * @brief Profile::addPost
 * @param p
 */
void Profile::addPost(Post* p) {
    postHistory.push_back(p);
}

/**
 * Add a group to the Profile's list of groups.
 * @brief Profile::addGroup
 * @param g
 */
void Profile::addGroup(Group* g) {
    groupsList.push_back(g);
}


//Getter and setter methods
int Profile::get_id(){
    return id;
}

string Profile::getNameFirst() {
    return nameFirst;
}
string Profile::getNameLast() {
    return nameLast;
}
string Profile::getUsername() {
    return username;
}
string Profile::getBio() {
    return bio;
}
string Profile::getLocation() {
    return location;
}
string Profile::getPreference() {
    return preference;
}
string Profile::getAge() {
    return age;
}
